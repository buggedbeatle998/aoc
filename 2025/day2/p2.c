#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    uint64_t first;
    uint64_t last;

    while (fscanf(fptr, "%ld-%ld,", &first, &last) == 2) {
        for (uint64_t i = first; i <= last; ++i) {
            uint8_t order = (uint64_t)log10(i) + 1;
            uint64_t mask = 1;
            for (uint32_t n = 1; n <= (order >> 1); ++n) {
                //printf("%d\n", order);
                mask *= 10;
                //printf("\n\t%ld ", mask);
                if (order % n == 0) {
                    uint64_t val = i % mask;
                    //printf("\n\t%ld ", val);
                    bool valid = true;
                    for (uint64_t masked = mask; masked <= i; masked *= mask) {
                        if ((i % (masked * mask)) / masked != val) {
                            //printf("%ld ", (i % (masked * mask)) / masked);
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        //printf("%ld, %d\n", i, n);
                        total += i;
                        break;
                    }
                }
            }
        }
    }

    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
