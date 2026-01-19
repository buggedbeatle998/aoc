#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    const size_t WIDTH = strcmp(argv[1], "test.txt") == 0 ? 15 : 141;
    uint64_t *beams = (uint64_t *)calloc(WIDTH, sizeof(uint64_t));
    char *dummy = malloc(2 * WIDTH * sizeof(char));
    char tester;
    int32_t off;
    
    fscanf(fptr, "%*[.]%nS", &off);
    //printf("%d\n", off);
    beams[off] = 1;
    fscanf(fptr, "%*[^\n]\n%n", &off);
    //printf("%d\n", off);
    
    while (fscanf(fptr, "%[.]\n", dummy) == 1) {
        uint64_t pos = 0;
        while (fscanf(fptr, "%[.]%c%n", dummy, &tester, &off) == 2) {
            pos += (uint64_t)off;
            if (pos - 1 >= WIDTH)
                break;
            if (beams[pos - 1]) {
                beams[pos - 2] += beams[pos - 1];
                beams[pos] += beams[pos - 1];
                beams[pos - 1] = 0;
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

    for (uint64_t i = 0; i < WIDTH; ++i) {
        total += beams[i];
    }
    
    //printf("%lb\n", beams.bits[0]);
    free(beams);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
