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
    uint64_t first;
    uint64_t last;

    while (fscanf(fptr, "%ld-%ld\n", &first, &last) == 2) {
        for (uint16_t i = 0; i < count; ++i) {
            if (map[i].last < map[i].first)
                continue;
            if (map[i].first >= first) {
                if (map[i].last <= last) {
                    total -= map[i].last - map[i].first + 1;
                    map[i].first = 1;
                    map[i].last = 0;
                } else if (map[i].first <= last) {
                    last = map[i].first - 1;
                }
            } else {
                if (map[i].last <= last) {
                    if (map[i].last >= first) {
                        first = map[i].last + 1;
                    }
                } else {
                    first = 1;
                    last = 0;
                    break;
                }
            }
        }
        if (first <= last) {
            //printf("%ld %ld\n", first, last);
            total += last - first + 1;
            map[count].first = first;
            map[count++].last = last;
        }
    }
    
    free(map);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
