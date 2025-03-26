#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "memory_util.h"
#include <time.h>

int main() {

    printf("hello!\n");

    int space[100000];
    prime_MemorySpace(space, 100000 * sizeof(int));
    char *s1;
    printf("!\n");

    for(int i = 0; i < 500000000; ++i) {
        s1 = allocate_MemorySpace(space, 3);
        free_MemorySpace(s1);
    }
    printf("!\n");

    for(int i = 0; i < 500000000; ++i) {
        s1 = malloc(8);
        free(s1);
    }
    printf("!\n");

    return 0;
}