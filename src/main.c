#include <stdio.h>
#include "flib_array.h"
#include "flib_timer.h"

int main() {
    flib_array *array = flib_array_create(1000000, sizeof(flib_i32));
    
    flib_time timer = flib_timer_create();

    flib_i32 num = 100;
    flib_array_fill(array, &num);

    printf("Fill array with 1.000.000 (4 bytes each) items took %f ms\n", flib_timer_get_milliseconds(&timer));

    flib_array_destroy(&array);

    return 0;
}