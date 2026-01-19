#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "bitstring.h"


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    const size_t WIDTH = strcmp(argv[1], "test.txt") == 0 ? 15 : 141;
    bitstring beams = bitstring_init(WIDTH / 64 + 1);
    char *dummy = malloc(2 * WIDTH * sizeof(char));
    char tester;
    int32_t off;
    
    fscanf(fptr, "%*[.]%nS", &off);
    //printf("%d\n", off);
    bitstring_set(beams, off, 1);
    fscanf(fptr, "%*[^\n]\n%n", &off);
    //printf("%d\n", off);
    
    while (fscanf(fptr, "%[.]\n", dummy) == 1) {
        uint64_t pos = 0;
        while (fscanf(fptr, "%[.]%c%n", dummy, &tester, &off) == 2) {
            pos += (uint64_t)off;
            if (pos - 1 >= WIDTH)
                break;
            if (bitstring_get(beams, pos - 1)) {
                ++total;
                bitstring_set(beams, pos - 1, 0);
                bitstring_set(beams, pos - 2, 1);
                bitstring_set(beams, pos, 1);
                //printf("%ld ", pos - 1);
            }
            //for (uint64_t i = 0; i < off - 1; ++i) {
            //    printf(bitstring_get(beams, pos - off + i) ? "|" : ".");
            //}
            //printf("^");
            //printf("%ld%c ", pos - 1, tester);
        }
        //printf("%lb\n", beams.bits[0]);
        //fscanf(fptr, "%*[\n]\n");
        //printf("\n");
    }
    
    //printf("%lb\n", beams.bits[0]);
    bitstring_free(beams);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
