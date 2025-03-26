#ifndef MEMORY
#define MEMORY

struct MemorySpaceHeader {

    unsigned size;
    unsigned usage;
    struct MemoryBlockHeader *frontier;
    struct MemoryBlockHeader *free[32];
};

struct MemoryBlockHeader {

    struct MemorySpaceHeader *root;
    unsigned char order;
    struct MemoryBlockHeader *next;
};

int prime_MemorySpace(void *root, unsigned size);
void *allocate_MemorySpace(void *space, unsigned char order);
void free_MemorySpace(void *root);
void *reallocate_MemorySpace(void *root, unsigned char order);
void *reallocate_truncated_MemorySpace(void *root, unsigned char order, unsigned trunc_limit);

#endif
