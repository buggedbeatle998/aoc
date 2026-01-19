#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    char *bank = (char *)malloc(sizeof(char) * 101);

    while (fscanf(fptr, "%s\n", bank) == 1) {
        uint8_t *best = (uint8_t *)calloc(12, sizeof(uint8_t));
        //printf("%d", strcmp(argv[1], "test"));
        for (uint8_t i = 0; i < (strcmp(argv[1], "test.txt") == 0 ? 15 : 100); ++i) {
            uint8_t n = bank[i] - '0';
            //printf("%d ", n);
            for (uint8_t k = 0; k < 11; ++k) {
                if (best[k] < best[k + 1]) {
                    best[k] = best[k + 1];
                    best[k + 1] = 0;
                }
            }
            if (n > best[11])
                best[11] = n;
        }
        //printf("\n%d %d\n", (uint32_t)best1, (uint32_t)best2);
        uint64_t num = 0;
        for (uint8_t i = 0; i < 12; ++i) {
            num *= 10;
            num += best[i];
            //printf("%d", best[i]);
        }
        total += num;
        //printf("%ld\n", num);
        free(best);
    }

    free(bank);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
