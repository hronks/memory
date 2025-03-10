#include <stdio.h>
#include "memory.h"

int main() {

    printf("hello!\n");

    char space[100000];
    prime_MemorySpace(space);
    printf("\n");
    print_MemorySpace(space);


    printf("\n%p\n", allocate_MemorySpace(space, 4));
    print_MemorySpace(space);

    printf("\n%p\n", allocate_MemorySpace(space, 3));
    print_MemorySpace(space);

//    for(int i = 0; i < 1000; ++i)
//        printf("%p ", space + i);
}