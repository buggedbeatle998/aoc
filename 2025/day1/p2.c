#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint32_t total = 0;
    char dir;
    uint32_t mag;
    int32_t state = 50;

    while (fscanf(fptr, "%[LR]%d\n", &dir, &mag) == 2) {
        total += (uint32_t)mag / 100;
        mag %= 100;
        if (dir == 'R') {
            state += mag;
            if (state >= 100)
                ++total;
        } else if (dir == 'L') {
            if (state == 0)
                --total;
            state += 100 - mag;
            if (state <= 100)
                ++total;
        } else
            printf("Something went wrong: %s", &dir);
        state %= 100;
        //printf("%d %d\n", state, total);
    }

    fclose(fptr);
    printf("%d\n", total);
    
    return 0;
}
