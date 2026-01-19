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
    uint16_t HEIGHT = strcmp(argv[1], "test.txt") == 0 ? 3 : 4;
    uint64_t *widths = calloc(WIDTH, sizeof(uint64_t));
    uint16_t *nums = calloc(WIDTH * 4, sizeof(uint16_t));
    char *ops = calloc(WIDTH, sizeof(uint64_t));
    
    for (uint8_t i = 0; i < HEIGHT; ++i) {
        fscanf(fptr, "%*[^\n]\n");
    }
    
    int32_t tempsc;
    for (uint16_t i = 0; fscanf(fptr, "%[*+] %n", ops + i, &tempsc) == 1; ++i) {
        widths[i] = tempsc - 1;
        //printf("%d", tempsc);
    }

    rewind(fptr);
    char temp;
    for (uint8_t n = 0; n < HEIGHT; ++n) {
        for (uint16_t i = 0; i < WIDTH; ++i) {
            //printf("%c %ld\n", ops[i % WIDTH], temp);
            for (uint8_t w = 0; w < widths[i]; ++w) {
                fscanf(fptr, "%c", &temp);
                if (temp == ' ')
                    continue;
                if (nums[i * 4 + w] == 0) {
                    nums[i * 4 + w] = temp - '0';
                } else {
                    nums[i * 4 + w] = nums[i * 4 + w] * 10 + temp - '0';
                }
                //printf("%d '%c' %d %d\n", nums[i * 4 + w], temp, i, w);
            }
            fscanf(fptr, "%*c");
        }
        //fscanf(fptr, "%*[^\n]\n");
    }

    for (uint16_t i = 0; i < WIDTH; ++i) {
        uint64_t sub_total = ops[i] == '*' ? 1 : 0;
        for (uint8_t w = 0; w < widths[i]; ++w) {
            if (ops[i] == '*') {
                sub_total *= nums[i * 4 + w];
            } else {
                sub_total += nums[i * 4 + w];
            }
        }
        //printf("%ld\n", sub_total);
        total += sub_total;
    }

    free(widths);
    free(nums);
    free(ops);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
