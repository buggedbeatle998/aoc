#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


typedef struct uivec3 {
    int32_t x;
    int32_t y;
    int32_t z;
} uivec3;


typedef struct Node {
    uint16_t i1;
    uint16_t i2;
    uint64_t mag;
    struct Node *left;
    struct Node *right;
    uint16_t num_sleft;
} Node;


Node *make_node(uint16_t n, uint16_t i, uint64_t mag, uint16_t num_sleft) {
    Node *temp = malloc(sizeof(Node));
    temp->i1 = n;
    temp->i2 = i;
    temp->mag = mag;
    temp->left = NULL;
    temp->right = NULL;
    temp->num_sleft = num_sleft;
    //printf("created");
    return temp;
}


void free_tree(Node *tree) {
    if (tree->left != NULL) {
        free_tree(tree->left);
    }
    if (tree->right != NULL) {
        free_tree(tree->right);
    }
    free(tree);
}


void in_order(Node *tree, uint16_t *set_num, uint16_t *lens, uint16_t *next, const uint32_t NUM, uint32_t *pairs) {
    if (tree->left != NULL) {
        in_order(tree->left, set_num, lens, next, NUM, pairs);
    }

    //lens[0] = 5;
    //printf("%ld\n", tree->mag);
    uint16_t setnum1 = set_num[tree->i1];
    uint16_t setnum2 = set_num[tree->i2];
    if (!*pairs)
        return;
    --*pairs;
    //printf("%d %d\n", tree->i1, tree->i2);
    if (setnum1) {
        if (setnum2) {
            if (setnum1 != setnum2) {
                if (lens[setnum2] > lens[setnum1]) {
                    uint16_t temp = setnum1;
                    setnum1 = setnum2;
                    setnum2 = temp;
                }
                lens[setnum1] += lens[setnum2];
                for (u_int16_t i = 0; lens[setnum2] && i < NUM; ++i) {
                    if (set_num[i] == setnum2) {
                        set_num[i] = setnum1;
                        lens[setnum2]--;
                    }
                }
            } else {
                //++*pairs;
            }
        } else {
            set_num[tree->i2] = setnum1;
            ++lens[setnum1];
        }
    } else {
        if (setnum2) {
            set_num[tree->i1] = setnum2;
            ++lens[setnum2];
        } else {
            set_num[tree->i1] = *next;
            set_num[tree->i2] = *next;
            lens[*next] += 2;
            ++*next;
            //printf("\t%d\n", *next);
        }
    }
    //for (uint16_t i = 0; i < NUM; ++i) {
    //    printf("%d\n", lens[i]);
    //}
    //printf("\n");

    if (tree->right != NULL) {
        in_order(tree->right, set_num, lens, next, NUM, pairs);
    }
}


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    const uint32_t NUM = strcmp(argv[1], "test.txt") == 0 ? 20 : 1000;
    uint32_t PAIRS = strcmp(argv[1], "test.txt") == 0 ? 10 : 1000;
    uivec3 *boxes = malloc(3 * sizeof(uint32_t) * NUM);
    Node *root = NULL;
    uint16_t *set_num = calloc(NUM, sizeof(uint16_t));
    uint16_t *lens = calloc(NUM, sizeof(uint16_t));

    for (uint32_t i = 0; fscanf(fptr, "%d,%d,%d\n", &boxes[i].x, &boxes[i].y, &boxes[i].z) == 3; ++i);
    
    for (uint32_t n = 0; n < NUM; ++n) {
        for (uint32_t i = n + 1; i < NUM; ++i) {
            int64_t dx = abs(boxes[n].x - boxes[i].x);
            int64_t dy = abs(boxes[n].y - boxes[i].y);
            int64_t dz = abs(boxes[n].z - boxes[i].z);
            uint64_t mag = dx * dx + dy * dy + dz * dz;
            //printf("%ld\n", mag);
            Node *curr = root;
            int16_t thresh = PAIRS *10;
            while (true) {
                if (root == NULL) {
                    root = make_node(n, i, mag, 1);
                    //printf("hi");
                    break;
                }
                if (mag < curr->mag) {
                    ++curr->num_sleft;
                    if (curr->left == NULL) {
                        curr->left = make_node(n, i, mag, i);
                        break;
                    } else {
                        curr = curr->left;
                    }
                } else {
                    thresh -= curr->num_sleft;
                    if (thresh < 0)
                        break;
                    if (curr->right == NULL) {
                        curr->right = make_node(n, i, mag, i);
                        break;
                    } else {
                        curr = curr->right;
                    }
                    
                }
            }
        }
    }
    
    uint16_t next = 1;
    if (root != NULL) {
        in_order(root, set_num, lens, &next, NUM, &PAIRS);
        //for (uint16_t i = 0; i < NUM; ++i) {
        //    printf("%d\n", lens[i]);
        //}
    }
    
    uint16_t first = 1;
    uint16_t second = 1;
    uint16_t third = 1;
    for (uint16_t i = 1; i < next; ++i) {
        if (second > first) {
            first = second;
            second = 1;
        }
        if (third > second) {
            second = third;
            third = 1;
        }
        if (lens[i] > third) {
            third = lens[i];
        }
    }
    total = first * second * third;

    if (root != NULL)
        free_tree(root);
    free(boxes);
    free(set_num);
    free(lens);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}
