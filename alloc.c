// alloc.c
#include "alloc.h"
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>
#define PAGE_SIZE 4096
#define ALIGNMENT 8

// Structure to represent a free or used chunk of memory
typedef struct {
size_t offset;    // Offset inside the mmap-ed memory page
size_t size;     // Size of chunk
int used;  //0 free, 1 allocated
} Chunk;

// Maximum number of chunks manageable
#define MAX_CHUNKS 64

// Metadata stored in static arrays (no malloc)
static Chunk chunks[MAX_CHUNKS];
static size_t chunk_count = 0;
static void* mem_page = NULL;

// Aligns size to 8 bytes
static size_t align8(size_t size) {
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

int init_alloc() {

if (mem_page != NULL) return 1; // Already initialized

mem_page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

if (mem_page == MAP_FAILED) return 2;

// Initialize one big free chunk covering entire page
chunk_count = 1;
chunks[0].offset = 0;
chunks[0].size = PAGE_SIZE;
chunks[0].used = 0;

return 0;
}

// Cleans up memory page back to OS
int cleanup() {

if (!mem_page) return 1;

munmap(mem_page, PAGE_SIZE);
mem_page = NULL;
chunk_count = 0;

return 0;
}

// Split a free chunk when allocating smaller size
static void split_chunk(size_t idx, size_t size) {
     if (chunk_count + 1 > MAX_CHUNKS)     return; // No space for new chunk

Chunk* c = &chunks[idx];

if(c->size > size) {

// Create new chunk for leftover space
for(size_t i = chunk_count; i > idx + 1; i--) {
     chunks [i] = chunks [i-1];
}
chunk_count++;

chunks [idx + 1].offset = c->offset + size;
chunks [idx + 1].size = c->size - size;
chunks [idx + 1].used = 0;
c->size = size;

}

}

// Merge adjacent free chunks
static void merge_free() {
size_t i = 0;
while(i + 1 < chunk_count) {
Chunk* c1 = &chunks[i];
Chunk* c2 = &chunks[i+1];

if(!c1->used && !c2->used && (c1->offset + c1->size == c2->offset)) {
c1->size += c2->size;

// Move all chunks left
for(size_t j = i + 1; j + 1 < chunk_count; j++) {
    chunks[j] = chunks[j + 1];
}
chunk_count--;
} else {

i++;

}
}
}

char* alloc(int size) {
if(size <= 0 || (size % ALIGNMENT) != 0 || !mem_page) return NULL;
size = align8(size);

for(size_t i = 0; i < chunk_count; i++) {
if(!chunks[i].used && chunks[i].size >= (size_t)size) {
split_chunk(i, size);
chunks [i].used = 1;
return (char*) mem_page + chunks[i].offset;
}
}
return NULL;
}

int dealloc(char* ptr) {
if(!ptr || !mem_page) return 1;
size_t offset = (char*)ptr - (char*)mem_page;
if(offset >= PAGE_SIZE) return 2;
for(size_t i=0; i < chunk_count; i++) {
if(chunks[i].offset == offset) {
if(!chunks [i].used) return 3; // Already free
chunks [i].used = 0;
merge_free();

return 0;

}

}

return 4; // Pointer not found

}