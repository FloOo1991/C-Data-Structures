#ifndef FLIB_ARRAY_H
#define FLIB_ARRAY_H

#include <flib_definitions.h>

typedef struct flib_array flib_array;

flib_array *flib_array_alloc(flib_ui32 size, flib_ui32 element_size);
flib_array *flib_array_init(void *data, flib_ui32 size, flib_ui32 element_size);
void flib_array_dealloc(flib_array **array);

flib_ui32 flib_array_get_size(flib_array *array);
flib_i32 flib_array_is_empty(flib_array *array);

void *flib_array_get_item(flib_array *array, flib_ui32 index);
flib_i32 flib_array_set_item(flib_array *array, flib_ui32 index, void *data);
#endif /* FLIB_ARRAY_H */