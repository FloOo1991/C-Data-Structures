#include <stdlib.h>
#include <string.h>
#include "flib_array.h"

typedef struct flib_array {
    flib_ptr    data;
    flib_ui32   size;
    flib_ui32   element_size;
} flib_array;

flib_array* flib_array_alloc(flib_ui32 size, flib_ui32 element_size) {
    flib_array *array = (flib_array *)malloc(sizeof(flib_array));
    if (array == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); return NULL; }

    array->data = (flib_ptr)malloc(size * element_size);
    if ((void *)array->data == NULL) { free(array); fprintf(stderr, "Failed to allocate memory.\n"); return NULL; }

    array->size = size;
    array->element_size = element_size;

    memset((void *)array->data, 0, size * element_size);

    return array;
}

flib_array* flib_array_init(void* data, flib_ui32 size, flib_ui32 element_size) {
    if (data == NULL) return NULL;

    flib_array *array = (flib_array *)malloc(sizeof(flib_array));
    if (array == NULL) return NULL;

    array->data = (flib_ptr)malloc(size * element_size);
    if ((void *)array->data == NULL) { free(array); return NULL; }
    memcpy((void *)array->data, data, size * element_size);
    
    array->size = size;
    array->element_size = element_size;

    return array;
}

void flib_array_dealloc(flib_array **array) {
    if (array == NULL || *array == NULL) return;
    if ((void *)(*array)->data != NULL) free((void *)(*array)->data);
    free(*array);
    *array = NULL;
}

flib_ui32 flib_array_get_size(flib_array *array) {
    if (array == NULL) return 0;
    return array->size;
}

void *flib_array_get_item(flib_array *array, flib_ui32 index) {
    if (array == NULL || index >= array->size) return NULL;
    
    flib_ptr element = array->data + (array->element_size * index);
    return (void *)element;
}

flib_i32 flib_array_set_item(flib_array *array, flib_ui32 index, void *data) {
    if (array == NULL || index >= array->size || data == NULL) return 0;

    flib_ptr element = array->data + (array->element_size * index);
    memmove((void *)element, data, array->element_size);
    return 1;
}
