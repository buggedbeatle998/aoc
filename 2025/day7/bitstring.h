#ifndef MY_BITSTRING
#define MY_BITSTRING

#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>



typedef struct bitstring {
    uint64_t *bits;
    size_t size;
} bitstring;

bitstring bitstring_init(size_t);
void bitstring_free(bitstring);
bool bitstring_get(bitstring, size_t);
void bitstring_set(bitstring, size_t, bool);

#endif
