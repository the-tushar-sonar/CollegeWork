#ifndef EALLOC_H
#define EALLOC_H

int init_alloc();
int cleanup();
char* alloc(int size);
int dealloc(char* ptr);

#endif