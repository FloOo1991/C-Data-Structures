#include <stdio.h>
#include "flib_list.h"
#include "flib_queue.h"

flib_i32 flib_compare_int32_asc(const flib_i32 *lhs, const flib_i32 *rhs) {
    if (*lhs < *rhs) {
        return -1;
    } else if (*lhs == *rhs) {
        return 0;
    } else {
        return 1;
    }
}

flib_i32 flib_compare_int32_dsc(const flib_i32 *lhs, const flib_i32 *rhs) {
    if (*lhs < *rhs) {
        return 1;
    } else if (*lhs == *rhs) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    srand(1);

    flib_queue *queue = flib_queue_alloc(10, sizeof(flib_i32));

    for (int i = 0; i < 32; i++) {
        flib_i32 num = rand();
        flib_queue_enqueue(queue, &num);
        printf("Added number %d to the queue.\n", num);
    }

    for (int i = 0; i < 32; i++) {
        flib_i32 num;
        flib_queue_dequeue(queue, &num);
        printf("Removed number %d from the queue.\n", num);
    }

    flib_queue_dealloc(&queue);

    return 0;
}