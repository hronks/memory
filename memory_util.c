#include "memory_util.h"

/*
void print_MemorySpace(void *space) {

    struct MemorySpaceHeader *msh = space;
    struct MemoryBlock *mb_allocated_ptr, *mb_free_ptr;

    printf("SPACE %p ", space);
    printf("(%d / %d), ", msh->usage, msh->size);
    printf("frontier: %p\n", (void *) msh->frontier);

    for(int i = 0; i < 32; ++i) {
        
        mb_allocated_ptr = msh->allocated[i];
        mb_free_ptr = msh->free[i];

        if(mb_allocated_ptr || mb_free_ptr) {
            printf("  ORDER %d:\n", i);
        }

        if(mb_allocated_ptr) {
            printf("    ALLOCATED:\n");
        }

        while(mb_allocated_ptr) {            
            printf("      %p: (%p, %p) ", (void *) mb_allocated_ptr, (void *) mb_allocated_ptr->next, (void *) mb_allocated_ptr->previous);
            printf("data: %p\n", mb_allocated_ptr->data);
            mb_allocated_ptr = mb_allocated_ptr->previous;
        }

        if(mb_free_ptr) {
            printf("    FREE:\n");
            while(mb_free_ptr) {             
                printf("      %p: (%p, %p) ", (void *) mb_free_ptr, (void *) mb_free_ptr->previous, (void *) mb_free_ptr->next);
                printf("data: %p\n", mb_free_ptr->data);
                mb_free_ptr = mb_free_ptr->next;
            }
        }
    }
    return;
}
*/