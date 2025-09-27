#ifndef EALLOC H

#define EALLOC H

int init_alloc();

int cleanup();

char* alloc(int size);

int dealloc(char* ptr);

#endif