#ifndef STRING
#define STRING

#include <stdlib.h>

struct String {

    char *c;
    size_t c_length;
    size_t c_capacity;

    struct StringDivider *d;    
    size_t d_length;
    size_t d_capacity;
};

struct StringDivider {

    int type;
    char *c;
    size_t length;
};

size_t capacity(char *s);
struct String *new_String(size_t capacity);
int delete_String(struct String *s);

int extend_StringFromCharBuffer(struct String *s, size_t maxCapacity, char *buffer, char *bufferTerminator);


#endif
