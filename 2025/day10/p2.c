#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


void output_matrix(float *matrix, size_t width, size_t height);
void row_echelon_reduce(float *matrix, float *augment, size_t width, size_t height);
size_t find_kernel_bases(float *matrix, float *bases, size_t width, size_t height);


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    char *temp = (char *)malloc(sizeof(char) * (19 + 1));
    float *buttons = malloc(sizeof(float) * 16 * 16);
    float *jolts = malloc(sizeof(float) * 10);
    float *pushes = malloc(sizeof(float) * 16);
    float *bases = malloc(sizeof(float) * 16 * 16);
    int32_t len;

    while (fscanf(fptr, "[%*[.#]]%n ", &len) == 0) {
        len -= 2;
        //if (len == 4) {
        //    fscanf(fptr, "%*[^\n]\n");
        //    continue;
        //}
        
        memset(buttons, 0, sizeof(float) * 16 * 16);
        int32_t butt_len;
        size_t butt_num;
        for (butt_num = 0; fscanf(fptr, "(%[^)])%n ", temp, &butt_len) == 1; ++butt_num) {
            butt_len /= 2;
            for (size_t n = 0; n < butt_len; ++n)
                buttons[butt_num * 16 + temp[n * 2] - '0'] = 1;
            //printf("\t%b\n", buttons[butt_num]);
        }

        fscanf(fptr, "%*c");
        for (size_t i = 0; i < len && fscanf(fptr, "%a,", jolts + i); ++i);

        //printf("%ld\n", butt_num - len);
        
        //printf("start\n");
        //output_matrix(buttons, butt_num, len);
        row_echelon_reduce(buttons, jolts, butt_num, len);
        //printf("result\n");
        //output_matrix(buttons, butt_num, len);

        //output_matrix(jolts, 1, len);
        memset(pushes, 0, sizeof(float) * 16);
        for (int64_t y = len - 1; y >= 0; --y) {
            //printf("\t%ld\n", y);
            size_t x;
            for (x = 0; x < butt_num && !buttons[x * 16 + y]; ++x);
            if (x == butt_num)
                continue;
            pushes[x] = jolts[y];
            for (size_t x1 = x + 1; x1 < butt_num; ++x1) {
                pushes[x] -= pushes[x1] * buttons[x1 * 16 + y];
            }
        }

        output_matrix(pushes, 1, butt_num);

        size_t num_bases = find_kernel_bases(buttons, bases, butt_num, len);
        printf("bases %ld:", num_bases);
        output_matrix(bases, num_bases, butt_num);
        
        if (fscanf(fptr, "%*[^\n]\n") == EOF)
            break;
    }
    
    free(bases);
    free(pushes);
    free(jolts);
    free(temp);
    free(buttons);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}

void output_matrix(float *matrix, size_t width, size_t height) {
    printf("\n");
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            printf("%f ", matrix[x * 16 + y]);
        }
        printf("\n");
    }
    printf("\n");
}


void row_echelon_reduce(float *matrix, float *augment, size_t width, size_t height) {
    size_t col = 0;
    size_t row = 0;

    while (col < width && row < height) {
        size_t ri_max = row;
        for (size_t i = row + 1; i < height; ++i) {
            if (fabsf(matrix[col * 16 + i]) > fabsf(matrix[col * 16 + ri_max]))
                ri_max = i;
        }
        if (matrix[col * 16 + ri_max] == 0) {
            ++col;
        } else {
            int16_t temp;
            for (size_t i = 0; i < width; ++i) {
                temp = matrix[i * 16 + row];
                matrix[i * 16 + row] = matrix[i * 16 + ri_max];
                matrix[i * 16 + ri_max] = temp;
            }
            temp = augment[row];
            augment[row] = augment[ri_max];
            augment[ri_max] = temp;
            //printf("col: %ld row: %ld, swap: %ld %ld\n", col, row, row, ri_max);
            //output_matrix(matrix, width, height);
            for (size_t i = row + 1; i < height; ++i) {
                float scale = (float)matrix[col * 16 + i] / matrix[col * 16 + row];
                matrix[col * 16 + i] = 0;
                for (size_t j = col + 1; j < width; ++j) {
                    matrix[j * 16 + i] -= matrix[j * 16 + row] * scale;
                }
                augment[i] -= augment[row] * scale;
                //printf("reduction: %ld\n", i);
                //output_matrix(matrix, width, height);
            }

            ++col;
            ++row;
        }
    }

    for (size_t i = 0; i < height; ++i) {
        float scale = 0;
        for (size_t n = 0; n < width; ++n) {
            if (!scale) {
                if (matrix[n * 16 + i] != 0) {
                    scale = (float)1 / matrix[n * 16 + i];
                    if (scale == 1)
                        break;
                    matrix[n * 16 + i] = 1;
                }
            } else {
                matrix[n * 16 + i] *= scale;
            }
        }
        if (scale)
            augment[i] *= scale;
    }
}

size_t find_kernel_bases(float *matrix, float *bases, size_t width, size_t height) {
    float *identity = calloc(16 * 16, sizeof(float));
    for (size_t i = 0; i < width; ++i) {
        identity[i * 16 + i] = 1;
    }
    //output_matrix(identity, width, height);
    size_t num_bases = 0;
    size_t col = 0;
    size_t row = 0;

    while (col < width && row < height) {
        if (matrix[col * 16 + row] == 0) {
            //printf("col: %ld row: %ld\n", col, row);
            memset(bases + num_bases * 16, 0, sizeof(float) * width);
            for (size_t y = 0; y < col + 1; ++y) {
                bases[num_bases * 16 + y] = (float)identity[col * 16 + y];
            }
            ++num_bases;
            ++col;
        } else {
            for (size_t x = col + 1; x < width; ++x) {
                if (matrix[x * 16 + row] != 0) {
                    for (size_t y = 0; y < col + 1; ++y) {
                        identity[x * 16 + y] -= (float)identity[col * 16 + y] * matrix[x * 16 + row];
                    }
                }
            }
            //output_matrix(identity, width, width);
            ++col;
            ++row;
        }
    }

    for (; col < width; ++col) {
        memset(bases + num_bases * 16, 0, sizeof(float) * width);
        for (size_t y = 0; y < col + 1; ++y) {
            bases[num_bases * 16 + y] = (float)identity[col * 16 + y];
        }
        ++num_bases;
    }

    free(identity);
    return num_bases;
}
