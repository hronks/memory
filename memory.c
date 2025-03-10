#include "memory.h"

void prime_MemorySpace(void *root) {

    // MSH, MB, MB ...

    void *ptr = root;
    struct MemorySpaceHeader *msh_ptr;
    msh_ptr = (struct MemorySpaceHeader *) ptr;
    
    for(unsigned char i = 0; i <32; ++i) {
        msh_ptr->root[i] = 0;
        msh_ptr->current[i] = 0;
    }
    msh_ptr->data = msh_ptr + 1;
    msh_ptr->next = msh_ptr->data;
    return;
}

void print_MemorySpace(void *space) {

    struct MemorySpaceHeader *msh = space;

    printf("space: %p %ld %ld\n", space, msh->data - space, msh->next - msh->data);
    printf("data:  %p\n", msh->data);
    printf("next:  %p\n", msh->next);

    for(int i = 0; i < 32; ++i) {
        if(msh->root[i]) { 
            printf("order %d: %p: %p -> %p\n", i, &msh->root[i], msh->root[i], msh->current[i]);
            printf("\t%d", msh->root[i]->order);
            printf(" %p -> %p -> %p", msh->root[i]->previous, msh->root[i], msh->root[i]->next);
            printf(" %d", msh->root[i]->size);
            printf(" %p\n", msh->root[i]->data);
        }
    }

    return;
}

void *allocate_MemorySpace(void *space, unsigned char order) {

    struct MemorySpaceHeader *msh_ptr = space;
    struct MemoryBlock *mb_ptr = msh_ptr->next;
    char *data_ptr;

    if(!msh_ptr->root[order]) {

        msh_ptr->root[order] = mb_ptr;
        msh_ptr->current[order] = mb_ptr;

        mb_ptr->order = order;
        mb_ptr->next = 0;
        mb_ptr->previous = 0;
        mb_ptr->size = 1 << order;
        mb_ptr->data = mb_ptr + 1;

        data_ptr = mb_ptr->data;
        msh_ptr->next = data_ptr + (1 << order);
        
        return mb_ptr->data;
    }

    else {

        return 0;
    }

}