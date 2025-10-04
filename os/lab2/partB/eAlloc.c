// eAlloc.c
#include "eAlloc.h"
#include <sys/mman.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define PAGE_SIZE 4096
#define ALIGNMENT 256
#define MAX_PAGES 4
#define MAX_CHUNKS 64

typedef struct {
    size_t offset;   // Offset inside page
    size_t size;     // Size of chunk
    int used;        // 0 if free, 1 if allocated
} Chunk;

typedef struct {
    void* page_addr;        // Address of the mmap-ed page
    size_t chunk_count;     // Number of chunks in this page
    Chunk chunks[MAX_CHUNKS];
} Page;

static Page pages[MAX_PAGES];
static size_t page_count = 0;

/* Round up to next multiple of ALIGNMENT */
static size_t align256(size_t size) {
    if (size == 0) return 0;
    size_t mask = ALIGNMENT - 1;
    return (size + mask) & ~mask;
}

/* Initialize allocator state */
int init_alloc(void) {
    page_count = 0;
    for (size_t i = 0; i < MAX_PAGES; i++) {
        pages[i].page_addr = NULL;
        pages[i].chunk_count = 0;
    }
    return 0;
}

/* Cleanup: unmap any mapped pages (returns 0 on success). 
   If you prefer not to munmap according to some spec, change this. */
int cleanup(void) {
    for (size_t i = 0; i < page_count; ++i) {
        if (pages[i].page_addr != NULL) {
            munmap(pages[i].page_addr, PAGE_SIZE);
            pages[i].page_addr = NULL;
            pages[i].chunk_count = 0;
        }
    }
    page_count = 0;
    return 0;
}

/* Merge adjacent free chunks in a page */
static void merge_free(Page *p) {
    if (!p) return;
    size_t i = 0;
    while (i + 1 < p->chunk_count) {
        Chunk *c1 = &p->chunks[i];
        Chunk *c2 = &p->chunks[i + 1];
        if (!c1->used && !c2->used && (c1->offset + c1->size == c2->offset)) {
            // merge c2 into c1
            c1->size += c2->size;
            // shift left the remaining chunks
            for (size_t j = i + 1; j + 1 < p->chunk_count; ++j) {
                p->chunks[j] = p->chunks[j + 1];
            }
            p->chunk_count--;
            // do not increment i, try merging the new adjacent pair again
        } else {
            ++i;
        }
    }
}

/* Split chunk at index idx in page p into an allocated chunk of 'size'
   and a leftover free chunk (if leftover > 0). */
static void split_chunk(Page *p, size_t idx, size_t size) {
    Chunk *c = &p->chunks[idx];
    if (size == 0 || idx >= p->chunk_count) return;

    if (c->size < size) return; // can't split, caller should check

    if (c->size == size) {
        // exact fit, no split required
        return;
    }

    // Need to create a new chunk after idx
    if (p->chunk_count + 1 > MAX_CHUNKS) {
        // cannot split because metadata limit reached; keep as is (caller may fail)
        return;
    }

    // shift right chunks from the end to make room
    for (size_t j = p->chunk_count; j > idx + 1; --j) {
        p->chunks[j] = p->chunks[j - 1];
    }
    // setup new chunk
    p->chunks[idx + 1].offset = c->offset + size;
    p->chunks[idx + 1].size   = c->size - size;
    p->chunks[idx + 1].used   = 0;

    c->size = size;
    // increase chunk count
    p->chunk_count++;
}

/* Allocate a block of memory with alignment enforcement.
   Returns pointer into a page, or NULL on failure. */
void *alloc(size_t size) {
    if (size == 0) return NULL;
    size_t asize = align256(size);
    if (asize == 0 || asize > PAGE_SIZE) return NULL;

    /* First search existing pages for a free chunk */
    for (size_t i = 0; i < page_count; i++) {
        Page *p = &pages[i];
        for (size_t j = 0; j < p->chunk_count; j++) {
            if (!p->chunks[j].used && p->chunks[j].size >= asize) {
                // split if necessary and mark used
                split_chunk(p, j, asize);
                p->chunks[j].used = 1;
                return (char *)p->page_addr + p->chunks[j].offset;
            }
        }
    }

    /* No free chunk found; allocate a new page if we have capacity */
    if (page_count >= MAX_PAGES) return NULL;

    void *new_page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                          MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new_page == MAP_FAILED) {
        return NULL;
    }

    Page *np = &pages[page_count++];
    np->page_addr = new_page;
    np->chunk_count = 1;
    np->chunks[0].offset = 0;
    np->chunks[0].size   = PAGE_SIZE;
    np->chunks[0].used   = 0;

    /* allocate from the new page */
    split_chunk(np, 0, asize);
    np->chunks[0].used = 1;
    return (char *)np->page_addr + np->chunks[0].offset;
}

/* Deallocate a previously allocated pointer.
   Returns 0 on success, non-zero error codes for different failures:
   1 - null pointer; 2 - already free; 3 - pointer offset not found; 4 - pointer not in any page
*/
int dealloc(void *ptr) {
    if (!ptr) return 1;

    for (size_t i = 0; i < page_count; ++i) {
        Page *p = &pages[i];
        if (p->page_addr == NULL) continue;
        char *base = (char *)p->page_addr;
        if ((char *)ptr >= base && (char *)ptr < base + PAGE_SIZE) {
            size_t offset = (size_t)((char *)ptr - base);
            // find matching chunk by offset
            for (size_t j = 0; j < p->chunk_count; ++j) {
                if (p->chunks[j].offset == offset) {
                    if (!p->chunks[j].used) return 2; // already free
                    p->chunks[j].used = 0;
                    merge_free(p);
                    return 0;
                }
            }
            return 3; // pointer not found at any chunk offset inside page
        }
    }
    return 4; // pointer not in any known page
}