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
    int32_t *points = malloc(sizeof(int64_t) * (NUM * 2 + 2));


    for (uint16_t i = 0; fscanf(fptr, "%d,%d", points + i * 2, points + i * 2 + 1) == 2; ++i);
    points[NUM * 2] = points[0];
    points[NUM * 2 + 1] = points[1];
    points[NUM * 2 + 2] = points[2];
    points[NUM * 2 + 3] = points[3];
    
    for (uint16_t i = 0; i < NUM; ++i) {
        int32_t x1 = points[i * 2];
        int32_t y1 = points[i * 2 + 1];
        int32_t x2 = points[i * 2 + 2];
        int32_t y2 = points[i * 2 + 3];
        int32_t x3 = points[i * 2 + 4];
        int32_t y3 = points[i * 2 + 5];
        bool vert = y3 - y2 != 0;
        int32_t vert_dir;
        int32_t horz_dir;
        if (vert) {
            vert_dir = (y3 - y2) / abs(y3 - y2);
            horz_dir = (x1 - x2) / abs(x1 - x2);
            x1 *= horz_dir;
            x2 *= horz_dir;
            y1 *= vert_dir;
            y2 *= vert_dir;
        } else {
            vert_dir = (x3 - x2) / abs(x3 - x2);
            horz_dir = (y1 - y2) / abs(y1 - y2);
            y1 *= horz_dir;
            y2 *= horz_dir;
            x1 *= vert_dir;
            x2 *= vert_dir;
        }
        uint32_t min_dist = 200000;
        for (uint16_t n = i & 1; n < NUM + 1; n += 2) {
            int32_t _x1 = points[n * 2];
            int32_t _y1 = points[n * 2 + 1];
            int32_t _x2 = points[n * 2 + 2];
            int32_t _y2 = points[n * 2 + 3];
            if (vert) {
                _x1 *= horz_dir;
                _x2 *= horz_dir;
                _y1 *= vert_dir;
                if (_y1 > y1 && _y1 - y1 < min_dist) {
                    if (_x1 > x2 && _x1 < x1 || _x2 > x2 && _x2 < x1 || _x1 < x2 && _x2 > x1 || _x1 > x1 && _x2 < x2) {
                        min_dist = _y1 - y1;
                    }
                }
            } else {
                _y1 *= horz_dir;
                _y2 *= horz_dir;
                _x1 *= vert_dir;
                if (_x1 > x1 && _x1 - x1 < min_dist) {
                    if (_y1 > y2 && _y1 < y1 || _y2 > y2 && _y2 < y1 || _y1 < y2 && _y2 > y1 || _y1 > y1 && _y2 < y2) {
                        min_dist = _x1 - x1;
                    }
                }
            }

        }
        int64_t area = min_dist * (vert ? x1 - x2 : y1 - y2);
        if (area > total) {
            total = area;
        }
    }
    
    free(points);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
