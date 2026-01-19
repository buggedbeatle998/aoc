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
    int32_t *points = malloc(sizeof(int64_t) * (NUM + 1) * 2);

    for (uint16_t i = 0; fscanf(fptr, "%d,%d", points + i * 2, points + i * 2 + 1) == 2; ++i);
    points[NUM * 2] = points[0];
    points[NUM * 2 + 1] = points[1];
    bool vert0 = points[2] - points[0] == 0;

    for (uint16_t i = 0; i < NUM; ++i) {
        int32_t x1 = points[i * 2];
        int32_t y1 = points[i * 2 + 1];
        for (uint16_t n = i + 1; n < NUM; ++n) {
            int32_t x2 = points[n * 2];
            int32_t y2 = points[n * 2 + 1];
            uint64_t area = ((uint64_t)abs(x2 - x1) + 1) * ((uint64_t)abs(y2 - y1) + 1);
            if (area > total) {
                int32_t vert_dir;
                int32_t horz_dir;
                vert_dir = (y2 - y1) / abs(y2 - y1);
                horz_dir = (x2 - x1) / abs(x2 - x1);
                x1 *= horz_dir;
                x2 *= horz_dir;
                y1 *= vert_dir;
                y2 *= vert_dir;
                bool valid = true;
                for (uint16_t k = 0; k < NUM; ++k) {
                    int32_t _x1 = points[k * 2];
                    int32_t _y1 = points[k * 2 + 1];
                    int32_t _x2 = points[k * 2 + 2];
                    int32_t _y2 = points[k * 2 + 3];
                    _x1 *= horz_dir;
                    _x2 *= horz_dir;
                    _y1 *= vert_dir;
                    _y2 *= vert_dir;
                    bool vert = vert0 ^ (k & 1);
                    //if (x1 == 9 && y1 == 5 && x2 == 2 && y2 == 3) {
                    //    printf("\t(%d, %d) (%d, %d)\n", _x1, _y1, _x2, _y2);
                    //}
                    if (vert) {
                        if (_x1 > x1 && _x1 < x2 && (_y1 > y1 && _y1 < y2 || _y2 > y1 && _y2 < y2 || _y1 <= y1 && _y2 >= y2 || _y2 <= y1 && _y1 >= y2)) {
                            valid = false;
                            break;
                        }
                    } else {
                        if (_y1 > y1 && _y1 < y2 && (_x1 > x1 && _x1 < x2 || _x2 > x1 && _x2 < x2 || _x1 <= x1 && _x2 >= x2 || _x2 <= x1 && _x1 >= x2)) {
                            valid = false;
                            break;
                        }
                    }
                }
                x1 *= horz_dir;
                y1 *= vert_dir;
                if (valid) {
                    total = area;
                    //printf("(%d, %d) (%d, %d)\n", x1, y1, x2, y2);
                }
            }
        }
    }
    
    free(points);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
