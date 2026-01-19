#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    const uint8_t SIZE = (strcmp(argv[1], "test.txt") == 0 ? 10 : 139);
    const uint16_t GRID_SIZE = SIZE * SIZE;
    const int16_t DIRS[8] = {-SIZE - 1, -1, SIZE - 1, -SIZE + 1, 1, SIZE + 1, -SIZE, SIZE};
    uint64_t total = 0;
    char *grid = malloc(sizeof(char) * GRID_SIZE + 1);

    for (uint8_t i = 0; fscanf(fptr, "%s\n", grid + SIZE * i) == 1; ++i);
    
    for (uint16_t i = 0; i < GRID_SIZE; ++i) {
        if (grid[i] == '.')
            continue;
        grid[i] = 'X';
        uint8_t count = 0;
        ++total;
        for (uint8_t n = 0; n < 8; ++n) {
            if (n == 0 && i % SIZE == 0) {
                n = 2;
                continue;
            }
            if (n == 3 && i % SIZE == SIZE - 1) {
                n = 5;
                continue;
            }
            int16_t check = i + DIRS[n];
            if (check < 0 || check >= GRID_SIZE)
                continue;
            //printf("%d %d, %d %c\n", i, n, check, grid[check]);
            if (grid[check] != '.' && ++count == 4) {
                --total;
                grid[i] = '@';
                break;
            }
        }
    }
    
    //printf("%s\n", grid);
    free(grid);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
