// alloc.h
#ifndef ALLOC H
#define ALLOC H

int init alloc();
int cleanup();
char* alloc(int size);
int dealloc(char* ptr);

#endif