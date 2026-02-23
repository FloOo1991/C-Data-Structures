#include <stdio.h>
#include "flib_list.h"
#include "flib_timer.h"

flib_i32 predicate_func(const void *num) {
    if (*(flib_i32 *)num > 30) return FLIB_TRUE;
    return FLIB_FALSE;
}

int main() {
    flib_time timer = flib_timer_create();
    flib_list *list = NULL;
    if (!flib_list_create(64, sizeof(flib_i32), &list)) return -1;

    for (int i = 0; i < flib_list_get_capacity(list); i++) {
        flib_list_append(list, &i);
    }

    flib_list_filter(list, predicate_func);

    for (int i = 0; i < flib_list_get_size(list); i++) {
        printf("Index %d: %d\n", i, *(flib_i32 *)flib_list_get_element(list, i));
    }

    flib_list_destroy(&list);

    return 0;
}