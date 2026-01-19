#include "bitstring.h"

#include <stdio.h>


bitstring bitstring_init(size_t size) {
    bitstring bits;

    bits.bits = (uint64_t *)calloc(size, sizeof(uint64_t));
    bits.size = size;

    return bits;
}

void bitstring_free(bitstring bits) {
    free(bits.bits);
}

bool bitstring_get(bitstring bits, size_t pos) {
    size_t off = pos / 64;

    if (off + 1 > bits.size) {
        printf("Bitstring index out of range.");
        exit(1);
    }

    return bits.bits[off] & ((uint64_t)1 << (pos - off * 64));
}

void bitstring_set(bitstring bits, size_t pos, bool val) {
    size_t off = pos / 64;

    if (off + 1 > bits.size) {
        bits.bits = (uint64_t *)realloc(bits.bits, sizeof(uint64_t) * (off + 1));
        bits.size = off + 1;
    }

    if (val) {
        bits.bits[off] |= ((uint64_t)1 << (pos % 64));
    } else {
        bits.bits[off] &= (~((uint64_t)1 << (pos % 64)));
    }
}
