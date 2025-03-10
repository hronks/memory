#ifndef MEMORY
#define MEMORY

#include<stdio.h> // used for printroot

struct MemorySpaceHeader {

    void *data;
    void *next;

    struct MemoryBlock *root[32];
    struct MemoryBlock *current[32];
};

struct MemoryBlock {

    unsigned char order;
    void *next;
    void *previous;
    unsigned int size;
    void *data;
};


void prime_MemorySpace(void *root);
void print_MemorySpace(void *root);
void *allocate_MemorySpace(void *root, unsigned char order);

#endif
