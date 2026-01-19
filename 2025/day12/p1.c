#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    char *presents = malloc(sizeof(char) * 10 * 6);

    int32_t i = -1;
    while (i < 5) {
        fscanf(fptr, "%d%*c%*c", &i);
        //printf("%d\n", i);
        for (size_t n = 0; n < 3; ++n) {
            fscanf(fptr, "%[^\n]\n", presents + i * 10 + n * 3);
        }
        fscanf(fptr, "%*[\n]");
    }
    
    int32_t width;
    int32_t height;
    int32_t temp;
    while (fscanf(fptr, "%dx%d: ", &width, &height) == 2) {
        int32_t area = 0;
        for (i = 0; i < 6; ++i) {
            fscanf(fptr, "%d ", &temp);
            area += temp;
        }
        if (area * 9 <= width * height)
            ++total;
        fscanf(fptr, "%*[\n]");
    }
    
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
