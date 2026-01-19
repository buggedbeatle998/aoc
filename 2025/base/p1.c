#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;


    while (fscanf(fptr, "") == ) {
        
    }
    
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
