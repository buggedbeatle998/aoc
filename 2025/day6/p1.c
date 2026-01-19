#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    uint16_t WIDTH = strcmp(argv[1], "test.txt") == 0 ? 4 : 1000;
    uint64_t *nums = calloc(WIDTH, sizeof(uint64_t));
    char *ops = calloc(WIDTH, sizeof(uint64_t));
    
    for (uint8_t i = 0; i < (strcmp(argv[1], "test.txt") == 0 ? 3 : 4); ++i) {
        fscanf(fptr, "%*[^\n]\n");
    }

    for (uint16_t i = 0; fscanf(fptr, "%[*+] ", ops + i) == 1; ++i);

    rewind(fptr);
    uint64_t temp;
    for (uint16_t i = 0; fscanf(fptr, "%ld ", &temp) == 1; ++i) {
        //printf("%c %ld\n", ops[i % WIDTH], temp);
        if (i < WIDTH) {
            nums[i] = temp;
        } else {
            if (ops[i % WIDTH] == '+') {
                nums[i % WIDTH] += temp;
            } else {
                nums[i % WIDTH] *= temp;
            }
        }
    }

    for (uint16_t i = 0; i < WIDTH; ++i) {
        total += nums[i];
    }
    
    free(nums);
    free(ops);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
