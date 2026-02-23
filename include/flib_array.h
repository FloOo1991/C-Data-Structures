#ifndef FLIB_ARRAY_H
#define FLIB_ARRAY_H

#include <flib_definitions.h>

typedef struct flib_array flib_array;


flib_i32 flib_array_create(flib_size_t _Size, flib_size_t _ElementSize, flib_array **_Out);
void flib_array_destroy(flib_array **_Array);

const void *flib_array_get_data(flib_array *_Array);

flib_i32 flib_array_copy(flib_array *_SourceArray, flib_array **_OutCopy);

flib_size_t flib_array_get_size(flib_array *_Array);
flib_i32 flib_array_is_empty(flib_array *_Array);

void *flib_array_get_element(flib_array *_Array, flib_ui32 _Index);
flib_i32 flib_array_set_element(flib_array *_Array, flib_ui32 _Index, void *_Element);
flib_i32 flib_array_fill(flib_array *_Array, void *_Element);

flib_i32 flib_array_resize(flib_array *_Array, flib_size_t _NewSize);

void flib_array_sort(flib_array *_Array, flib_compare_func _CompareFunc);
flib_i32 flib_array_find(flib_array *_Array, void *_Element);

typedef struct flib_array_iterator {
    const flib_array *_Array;
    flib_i64 _Index;
} flib_array_iterator;

flib_array_iterator flib_array_iterator_create(const flib_array *_Array);
flib_i32 flib_array_iterator_move_next(flib_array_iterator *_Iterator);
const void *flib_array_iterator_get_current(flib_array_iterator *_Iterator);
#endif /* FLIB_ARRAY_H */