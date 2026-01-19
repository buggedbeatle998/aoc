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
        if (dir == 'R')
            state += mag;
        else if (dir == 'L')
            state += 100 - (mag % 100);
        else
            printf("Something went wrong: %s", &dir);
        state %= 100;
        if (state == 0)
            ++total;
    }

    fclose(fptr);
    printf("%d\n", total);
    
    return 0;
}
