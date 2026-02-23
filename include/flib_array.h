#ifndef FLIB_ARRAY_H
#define FLIB_ARRAY_H

#include <flib_definitions.h>

typedef struct flib_array flib_array;

flib_array *flib_array_create(flib_size_t _Size, flib_size_t _ElementSize);
void flib_array_destroy(flib_array **_Array);

flib_ui32 flib_array_get_size(flib_array *_Array);
flib_i32 flib_array_is_empty(flib_array *_Array);

void *flib_array_get_item(flib_array *_Array, flib_ui32 _Index);
void flib_array_set_item(flib_array *_Array, flib_ui32 _Index, void *_Data);
void flib_array_fill(flib_array *_Array, void *_Item);

void flib_array_resize(flib_array *array, flib_size_t size);

void flib_array_sort(flib_array *array, flib_compare_func compare_func);
flib_i32 flib_array_find(flib_array *array, void *item);

const void *flib_array_get_ptr(flib_array *array);
#endif /* FLIB_ARRAY_H */