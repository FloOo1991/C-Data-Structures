#include <stdio.h>
#include "flib_list.h"
#include "flib_linked_list.h"
#include "flib_stack.h"
#include "flib_queue.h"
#include "flib_timer.h"

void unit_test_list(flib_ui32 iterations, flib_ui32 items) {
    double total_time = 0;
    for (int i = 0; i < iterations; i++) {
        flib_time timer = flib_timer_create();
        flib_list *list = flib_list_alloc(10, sizeof(flib_i32));

        for (int j = 0; j < items; j++) flib_list_add(list, &j);
        flib_list_dealloc(&list);
        total_time += flib_timer_get_milliseconds(&timer);
    }

    printf("FLIB_LIST_TEST: For %d iterations, allocated a list with a capacity of 10 and added %d items:\n"
           "Total time: %f ms, Average time: %f\n\n", iterations, items, total_time, total_time / iterations);
}

void unit_test_stack(flib_ui32 iterations, flib_ui32 items) {
    double total_time = 0;
    for (int i = 0; i < iterations; i++) {
        flib_time timer = flib_timer_create();
        flib_stack *stack = flib_stack_alloc(10, sizeof(flib_i32));

        for (int j = 0; j < items; j++) flib_stack_push(stack, &j);
        flib_stack_dealloc(&stack);
        total_time += flib_timer_get_milliseconds(&timer);
    }

    printf("FLIB_STACK_TEST: For %d iterations, allocated a stack with a capacity of 10 and pushed %d items:\n"
           "Total time: %f ms, Average time: %f\n\n", iterations, items, total_time, total_time / iterations);
}

void unit_test_queue(flib_ui32 iterations, flib_ui32 items) {
    double total_time = 0;
    for (int i = 0; i < iterations; i++) {
        flib_time timer = flib_timer_create();
        flib_queue *queue = flib_queue_alloc(10, sizeof(flib_i32));

        for (int j = 0; j < items; j++) flib_queue_enqueue(queue, &j);
        flib_queue_dealloc(&queue);
        total_time += flib_timer_get_milliseconds(&timer);
    }

    printf("FLIB_QUEUE_TEST: For %d iterations, allocated a queue with a capacity of 10 and pushed %d items:\n"
           "Total time: %f ms, Average time: %f\n\n", iterations, items, total_time, total_time / iterations);
}

void unit_test_linked_list(flib_ui32 iterations, flib_ui32 items) {
    double total_time = 0;
    for (int i = 0; i < iterations; i++) {
        flib_time timer = flib_timer_create();
        flib_linked_list *list = flib_linked_list_alloc(10, sizeof(flib_i32));

        for (int j = 0; j < items; j++) flib_linked_list_append(list, &j);
        flib_linked_list_dealloc(&list);
        total_time += flib_timer_get_milliseconds(&timer);
    }

    printf("FLIB_LINKED_LIST_TEST: For %d iterations, allocated a linked list and appended %d items:\n"
           "Total time: %f ms, Average time: %f\n\n", iterations, items, total_time, total_time / iterations);
}

int main() {
    unit_test_list(100, 1000000);
    unit_test_stack(100, 1000000);
    unit_test_queue(100, 1000000);
    unit_test_linked_list(100, 1000000);
    return 0;
}