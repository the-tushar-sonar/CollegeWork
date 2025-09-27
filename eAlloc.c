// ealloc.c

#include "ealloc.h"

#include <sys/mman.h>

#include <stddef.h>

#define PAGE SIZE 4096

#define ALIGNMENT 256

#define MAX PAGES 4

typedef struct {

size t offset;

// Offset inside page

size t size;

// Size of chunk

int used;

//0 if free, 1 if allocated

} Chunk;

typedef struct {

void* page_addr;

// Address of the mmap-ed page

size t chunk_count;

// Number of chunks in this page

Chunk chunks [64];

// Fixed size array of chunks metadata

} Page;

static Page pages [MAX_PAGES];

static size t page_count = 0;

static size t align256(size t size) {

return (size + ALIGNMENT 1) & (ALIGNMENT 1);

}

int init_alloc() {

page_count = 0;

// No pages allocated initially

for (size ti = 0; i < MAX PAGES; i++) {

pages[i].page_addr = NULL;

pages[i].chunk count = 0;

}

return 0;

}

int cleanup() {

// According to spe spec, do not munmap pages here

return 0;

}

// Split a chunk into allocated and leftover free chunk

static void split_chunk(Page *p, size_t idx, size_t size) {

Chunk c = &p->chunks [idx];

if (c->size > size) {

// Shift chunks for new split chunk

for (size ti p->chunk_count; i > idx+1; i--) {
}

}

for (size tip->chunk_count; i > idx+1; i--) {

p->chunks [i] = p->chunks [i-1];

}

p->chunk_count++;

p->chunks [idx + 1].offset = c->offset + size;

p->chunks [idx + 1].size = c->size size;

p->chunks [idx + 1].used = 0;

c->size = size;

// Merge adjacent free chunks

static void merge_free (Page *p) {

size ti=0;

while (i + 1 p->chunk count) {

Chunk c1 = &p->chunks[i];

Chunk c2 = &p->chunks [i+1];

if (!c1->used && !c2->used && (cl->offset + cl->size == c2->offset)) {

cl->size += c2->size;

for (size tj=i+1; j + 1 p->chunk_count; j++) {

}

p->chunks[j] = p->chunks [j+1];

p->chunk_count--;

} else {

i++;

}

}

}

char* alloc(int size) {

if (size <= 0 || (size % ALIGNMENT) != 0 || size > PAGE SIZE) return NULL;

size align256(size);

// Search for free chunk among existing pages

for (size t i = 0; i < page_count; i++) {

Page *p=&pages[i];

for (size tj = 0; j < p->chunk_count; j++) {

if (!p->chunks[j].used && p->chunks[j].size >= (size_t)size) {

split_chunk(p, j, size);

p->chunks[j].used = 1;

return (char*)p->page_addr + p->chunks[j].offset;

}

}

}

// No free chunk found: map a new page if available
if (page_count >= MAX_PAGES) return NULL;

void* new_page mmap (NULL, PAGE SIZE, PROT_READ | PROT_WRITE, ΜΑΡ ΑΝΟΝ | ΜΑAP_PRIVATE, -1, 0);

if (new_page == MAP_FAILED) return NULL;

// Initialize page data

Page new_p=&pages [page_count++);

new_p->page_addr = new page;

new_p->chunk_count = 1;

new_p->chunks[0].offset = 0;

new_p->chunks[0].size = PAGE_SIZE;

new_p->chunks[0].used = 0;

// Allocate in the new page

split chunk(new p, 0, size);

new_p->chunks[0].used = 1;

return (char*)new_p->page_addr + new_p->chunks[0].offset;

int dealloc(char* ptr) {

if (!ptr) return 1;

// Find which page owns this pointer

for (size_t i=0; i < page_count; i++) {

Page* p&pages[i];

if (ptr >= (char*)p->page_addr && ptr < (char*)p->page_addr + PAGE_SIZE) {

size t offset ptr (char*)p->page_addr;

for (size t j = 0; j < p->chunk_count; j++) { if (p->chunks[j].offset == offset) {

if (!p->chunks[j].used) return 2; // Already free

p->chunks[j].used = 0;

merge_free(p);

return 0;

}

}

return 3; // Pointer not found at this offset

}

}

return 4; // Pointer not in any known page

}