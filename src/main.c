#include <stdio.h>
#include "flib_list.h"

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

    flib_list *list = flib_list_alloc(10, sizeof(flib_i32));

    for (flib_i32 i = 0; i < 40; i++) {
        flib_i32 rnd = rand();
        flib_list_add(list, &rnd);
    }

    flib_list_sort(list, (flib_list_compare_func)flib_compare_int32_dsc);

    for (flib_i32 i = 0; i < flib_list_get_size(list); i++) {
        printf("Item [%d]:\t %d\n", i, *((flib_i32*)flib_list_get_item(list, i)));
    }

    flib_list_dealloc(&list);

    return 0;
}