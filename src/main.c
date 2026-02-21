#include <stdio.h>
#include <malloc.h>
#include "flib_array.h"
#include "flib_list.h"
#include "flib_timer.h"

int main() {
    double total_time = 0;
    flib_i32 max_iterations = 100;

    for (int j = 0; j < max_iterations; j++) {
        flib_time timer = flib_timer_create();
        flib_array *array = flib_array_alloc(10000000, sizeof(flib_i32));

        flib_i32 num = 32;
        flib_array_fill(array, &num);

        flib_array_dealloc(&array);
        total_time += flib_timer_get_milliseconds(&timer);
    }


    printf("Allocated an array with 1.000.000 elements and filled with number 32 for %d iterations.\n"
           "Total time: %f ms, Average time: %f ms\n", max_iterations, total_time, total_time / max_iterations);
    return 0;
}