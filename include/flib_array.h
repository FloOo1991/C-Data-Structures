#ifndef FLIB_ARRAY_H
#define FLIB_ARRAY_H

#include <flib_definitions.h>

typedef struct flib_array flib_array;

flib_array *flib_array_alloc(flib_ui32 size, flib_ui32 element_size);
void flib_array_dealloc(flib_array **array);

flib_ui32 flib_array_get_size(flib_array *array);
flib_i32 flib_array_is_empty(flib_array *array);

void *flib_array_get_item(flib_array *array, flib_ui32 index);
flib_i32 flib_array_set_item(flib_array *array, flib_ui32 index, void *item);
void flib_array_fill(flib_array *array, void *item);

void flib_array_resize(flib_array *array, flib_ui32 size);

void flib_array_sort(flib_array *array, flib_compare_func compare_func);
flib_i32 flib_array_find(flib_array *array, void *item);

const void *flib_array_get_ptr(flib_array *array);
#endif /* FLIB_ARRAY_H */