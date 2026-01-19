#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


typedef struct tuple {
    uint64_t first;
    uint64_t last;
} tuple;


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    
    uint16_t count = 0;
    tuple *map = calloc(200, sizeof(tuple));

    while (fscanf(fptr, "%ld-%ld\n", &map[count].first, &map[count].last) == 2) {
        ++count;
    }
    
    uint64_t num;

    while (fscanf(fptr, "%ld\n", &num) == 1) {
        for (uint16_t i = 0; i < count; ++i) {
            if (num >= map[i].first && num <= map[i].last) {
                ++total;
                break;
            }
        }
    }
    
    free(map);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
