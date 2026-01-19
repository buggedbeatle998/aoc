#include <inttypes.h>
#include <stdalign.h>
#include <stddef.h>

typedef struct Node {
    max_align_t value[1];
    int64_t priority;
    struct Node *left;
    struct Node *right;
} Node;

void pqueue_push(int64_t value, int64_t priority);
void pqueue_pop(int64_t value, int64_t priority);
