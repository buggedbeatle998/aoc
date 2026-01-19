#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


bool test_buttons(uint16_t *currj, uint16_t *jolts, int32_t jolt_len, uint16_t *buttons, int32_t len, size_t depth);


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    char *temp = (char *)malloc(sizeof(char) * (19 + 1));
    uint16_t *buttons = (uint16_t *)malloc(sizeof(uint16_t) * 64);
    uint16_t *jolts = (uint16_t *)malloc(sizeof(uint16_t) * 10);
    uint16_t *currj = (uint16_t *)malloc(sizeof(uint16_t) * 10);
    int32_t len;

    while (fscanf(fptr, "[%*[.#]]%n ", &len) == 0) {
        len -= 2;
        //if (len == 4) {
        //    fscanf(fptr, "%*[^\n]\n");
        //    continue;
        //}
        
        memset(buttons, 0, sizeof(uint16_t) * 64);
        int32_t butt_len;
        size_t butt_num;
        for (butt_num = 0; fscanf(fptr, "(%[^)])%n ", temp, &butt_len) == 1; ++butt_num) {
            butt_len /= 2;
            for (size_t n = 0; n < butt_len; ++n)
                buttons[butt_num] |= 1U << (temp[n * 2] - '0');
            //printf("\t%b\n", buttons[butt_num]);
        }

        fscanf(fptr, "%*c");
        for (size_t i = 0; i < len && fscanf(fptr, "%hu,", jolts + i); ++i);
        printf("{");
        for (size_t i = 0; i < len; ++i) {
            printf("%d, ", jolts[i]);
        }
        printf("}\n");
        uint16_t max_jolt = 0;
        for (size_t i = 0; i < len; ++i) {
            if (jolts[i] > max_jolt) {
                max_jolt = jolts[i];
            }
        }
        for (size_t depth = max_jolt; depth < 1000; ++depth) {
            //printf("%ld ", depth);
            memset(currj, 0, sizeof(uint16_t) * len);
            if (test_buttons(currj, jolts, len, buttons, butt_num, depth)) {
                total += depth;
                //printf("\n\t%ld", depth);
                break;
            }
        }
        //printf("\n");
        
        if (fscanf(fptr, "%*[^\n]\n") == EOF)
            break;
    }
    
    free(jolts);
    free(currj);
    free(temp);
    free(buttons);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}


bool test_buttons(uint16_t *currj, uint16_t *jolts, int32_t jolt_len, uint16_t *buttons, int32_t butt_len, size_t depth) {
    for (size_t i = 0; i < butt_len; ++i) {
        uint16_t button = buttons[i];
        bool skip = false;
        if (depth == 12 && jolts[0] == 7) {
            printf("{");
            for (size_t i = 0; i < jolt_len; ++i) {
                printf("%d, ", currj[i]);
            }
            printf("}\n");
        }
        for (size_t j = 0; j < jolt_len; ++j) {
            if ((button & 1) && currj[j] == jolts[j]) {
                button = buttons[i];
                for (size_t n = 0; n < j; ++n) {
                    currj[n] -= button & 1;
                    button >>= 1;
                }
                skip = true;
                break;
            }
            currj[j] += button & 1;
            button >>= 1;
        }
        if (skip)
            continue;
        if (depth == 1) {
            bool valid = true;
            for (size_t j = 0; j < jolt_len; ++j) {
                if (currj[j] != jolts[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid)
                return true;
        }
        else {
            if (test_buttons(currj, jolts, jolt_len, buttons, butt_len, depth - 1))
                return true;
        }
        button = buttons[i];
        for (size_t j = 0; j < jolt_len; ++j) {
            currj[j] -= button & 1;
            button >>= 1;
        }
    }
    return false;
}
