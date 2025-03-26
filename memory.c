#include "memory.h"

int prime_MemorySpace(void *root, unsigned size) {

    struct MemorySpaceHeader *msh_ptr = (struct MemorySpaceHeader *) root;
    msh_ptr->size = size;
    for(unsigned char i = 0; i < 32; ++i) {
        msh_ptr->free[i] = 0;
    }
    msh_ptr->usage = sizeof(struct MemorySpaceHeader);
    msh_ptr->frontier = (void *) (msh_ptr + 1);
    return 1;
}

void *allocate_MemorySpace(void *space, unsigned char order) {

    struct MemorySpaceHeader *msh_ptr = (struct MemorySpaceHeader *) space;
    struct MemoryBlockHeader *mbh_ptr; 

    if(msh_ptr->free[order]) {
        mbh_ptr = msh_ptr->free[order];
        msh_ptr->free[order] = mbh_ptr->next;
        return (void *) (mbh_ptr + 1);
    }

    if(msh_ptr->frontier) {
        unsigned usage = sizeof(struct MemoryBlockHeader) + (1 << order);
        if(usage + msh_ptr->usage > msh_ptr->size) return 0;
        mbh_ptr = msh_ptr->frontier++;
        mbh_ptr->order = order;
        mbh_ptr->root = msh_ptr;
        msh_ptr->frontier = (struct MemoryBlockHeader *) (((char *) msh_ptr->frontier) + (1 << order));
        msh_ptr->usage += usage;
        return (void *) (mbh_ptr + 1);
    }
    
    return 0;
}

void free_MemorySpace(void *root) {

    struct MemoryBlockHeader *mbh_ptr = ((struct MemoryBlockHeader *) root) - 1;
    struct MemorySpaceHeader *msh_ptr = mbh_ptr->root;
    unsigned order = mbh_ptr->order;
    mbh_ptr->next = msh_ptr->free[order];
    msh_ptr->free[order] = mbh_ptr;
    return;
}

/*

void *allocate_MemorySpace(void *space, unsigned char order) {

    struct MemorySpaceHeader *msh_ptr = space;
    struct MemoryBlock *mb_ptr;

    // need to check if there is a free

    if(msh_ptr->free[order]) {

        mb_ptr = msh_ptr->free[order];
        msh_ptr->allocated[order] = mb_ptr;
        msh_ptr->free[order] = mb_ptr->next;

        return mb_ptr->data;
    }

    // otherwise need to reserve more space, so do a memory check

    if(msh_ptr->usage + sizeof(struct MemoryBlock) + (1 << order) > msh_ptr->size)
        return 0;
    else
        msh_ptr->usage += sizeof(struct MemoryBlock) + (1 << order);
    

    if(msh_ptr->frontier) {
        mb_ptr = msh_ptr->frontier;

        // roll forward the next pointer
        // MEMORY CHECK

        msh_ptr->frontier = (struct MemoryBlock *) (((char *) msh_ptr->frontier) + sizeof(struct MemoryBlock) + (1 << order));
        
    }
    else return 0;

    // link the output to the chain

    mb_ptr->previous = msh_ptr->allocated[order];
    if(msh_ptr->allocated[order])
        msh_ptr->allocated[order]->next = mb_ptr;
    msh_ptr->allocated[order] = mb_ptr;

    // define the output

    mb_ptr->root = msh_ptr;
    mb_ptr->order = order;
    mb_ptr->next = 0;
    mb_ptr->size = 1 << order;
    mb_ptr->data = (void *) (mb_ptr + 1);

    return mb_ptr->data;
}

int free_MemorySpace(void *root) {

    char *data_ptr = root;
    struct MemoryBlock *mb_ptr = (struct MemoryBlock *) (data_ptr - sizeof(struct MemoryBlock));
    struct MemorySpaceHeader *msh_ptr = mb_ptr->root;
    unsigned char order = mb_ptr->order;

    // if current need to move current back one and return
    
    if(mb_ptr == msh_ptr->allocated[order]) {
        msh_ptr->free[order] = msh_ptr->allocated[order];
        msh_ptr->allocated[order] = msh_ptr->allocated[order]->previous;
        return 1;
    }

    // detach from chain

    if(mb_ptr->previous)
        mb_ptr->previous->next = mb_ptr->next;
    if(mb_ptr->next)
        mb_ptr->next->previous = mb_ptr->previous;

    // attach between current and free next

    mb_ptr->next = msh_ptr->free[order];
    if(msh_ptr->free[order])
        msh_ptr->free[order]->previous = mb_ptr;
    mb_ptr->previous = msh_ptr->allocated[order];
    msh_ptr->allocated[order]->next = mb_ptr;

    msh_ptr->free[order] = mb_ptr;

    return 1;
}

void *reallocate_MemorySpace(void *root, unsigned char order) {

    char *data_ptr = root, *out_ptr;
    struct MemoryBlock *mb_ptr = (struct MemoryBlock *) (data_ptr - sizeof(struct MemoryBlock));
    struct MemorySpaceHeader *msh_ptr = mb_ptr->root;

    if(msh_ptr->usage + sizeof(struct MemoryBlock) + (1 << order) > msh_ptr->size)
        return 0;

    out_ptr = (char *) allocate_MemorySpace(msh_ptr, order);

    for(unsigned int i = 0; i < mb_ptr->size; ++i) {
        out_ptr[i] = data_ptr[i];
    }

    free_MemorySpace(root);
    return out_ptr;
}

void *reallocate_truncated_MemorySpace(void *root, unsigned char order, unsigned int trunc_limit) {

    char *data_ptr = root, *out_ptr;
    struct MemoryBlock *mb_ptr = (struct MemoryBlock *) (data_ptr - sizeof(struct MemoryBlock));
    struct MemorySpaceHeader *msh_ptr = mb_ptr->root;
    
    if(msh_ptr->usage + sizeof(struct MemoryBlock) + (1 << order) > msh_ptr->size)
        return 0;

    out_ptr = (char *) allocate_MemorySpace(msh_ptr, order);

    for(unsigned int i = 0; i < trunc_limit; ++i) {
        out_ptr[i] = data_ptr[i];
    }

    free_MemorySpace(root);
    return out_ptr;
}

*/