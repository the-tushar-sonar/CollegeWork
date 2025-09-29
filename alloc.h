// alloc.h
#ifndef ALLOC_H
#define ALLOC_H

int init_alloc();
int cleanup();
char* alloc(int size);
int dealloc(char* ptr);

#endif