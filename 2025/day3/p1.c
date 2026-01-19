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
        uint8_t best1 = 0;
        uint8_t best2 = 0;
        for (uint32_t i = 0; i < (strcmp(argv[1], "test.txt") == 0 ? 15 : 100); ++i) {
            uint8_t n = bank[i] - '0';
            //printf("%d ", n);
            if (best2 > best1) {
                best1 = best2;
                best2 = n;
            } else if (n > best2) {
                best2 = n;
            }
        }
        //printf("\n%d %d\n", (uint32_t)best1, (uint32_t)best2);
        total += best1 * 10 + best2;
    }

    free(bank);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
