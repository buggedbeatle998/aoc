#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


bool test_buttons(uint16_t lights, uint16_t *buttons, int32_t len, size_t depth, uint64_t used);


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    char *temp = (char *)malloc(sizeof(char) * (19 + 1));
    uint16_t *buttons = (uint16_t *)malloc(sizeof(uint16_t) * 64);
    uint16_t lights;
    int32_t len;

    while (fscanf(fptr, "[%[.#]]%n ", temp, &len) == 1) {
        len -= 2;
        lights = 0U;
        for (size_t i = 0; i < len; ++i) {
            if (temp[i] == '#')
                lights |= 1U << i;
        }
        //printf("%b\n", lights);
        
        memset(buttons, 0, sizeof(uint16_t) * 64);
        int32_t butt_len;
        size_t butt_num;
        for (butt_num = 0; fscanf(fptr, "(%[^)])%n ", temp, &butt_len) == 1; ++butt_num) {
            butt_len /= 2;
            for (size_t n = 0; n < butt_len; ++n)
                buttons[butt_num] |= 1U << (temp[n * 2] - '0');
            //printf("\t%b\n", buttons[butt_num]);
        }

        total += butt_num;
        for (size_t depth = 1; depth < butt_num; ++depth) {
            //printf("%ld", depth);
            if (test_buttons(lights, buttons, butt_num, depth, 0UL)) {
                total += -butt_num + depth;
                //printf("\n\t%ld", depth);
                break;
            }
        }
        //printf("\n");

        if (fscanf(fptr, "%*[^\n]\n") == EOF)
            break;
    }
    
    free(temp);
    free(buttons);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}


bool test_buttons(uint16_t lights, uint16_t *buttons, int32_t butt_len,  size_t depth, uint64_t used) {
    for (size_t i = 0; i < butt_len; ++i) {
        if (used & (1UL << i))
            continue;
        lights ^= buttons[i];
        if (depth > 1) {
            if (test_buttons(lights, buttons, butt_len, depth - 1, used | (1UL << i)))
                return true;
        } else if (lights == 0U)
            return true;
        lights ^= buttons[i];
    }
    return false;
}
