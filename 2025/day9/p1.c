#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    const uint16_t NUM = strcmp(argv[1], "test.txt") == 0 ? 8 : 496;
    int32_t *points = malloc(sizeof(int64_t) * NUM * 2);


    for (uint16_t i = 0; fscanf(fptr, "%d,%d", points + i * 2, points + i * 2 + 1) == 2; ++i);
    
    for (uint16_t i = 0; i < NUM; ++i) {
        for (uint16_t n = i + 1; n < NUM; ++n) {
            uint64_t area = ((uint64_t)abs(points[i * 2] - points[n * 2]) + 1) * ((uint64_t)abs(points[i * 2 + 1] - points[n * 2 + 1]) + 1);
            if (area > total) {
                total = area;
            }
        }
    }
    
    free(points);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
