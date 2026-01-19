#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    uint64_t first;
    uint64_t last;

    while (fscanf(fptr, "%ld-%ld,", &first, &last) == 2) {
        for (uint64_t i = first; i <= last; ++i) {
            uint64_t order = (uint64_t)log10(i) + 1;
            if (order & 1)
                continue;
            order >>= 1;
            order = (uint64_t)pow(10, order);
            //printf("%d\n", order);
            if (i / order == i % order) {
                //printf("%ld\n", i);
                total += i;
                i += order;
            }
        }
    }

    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
