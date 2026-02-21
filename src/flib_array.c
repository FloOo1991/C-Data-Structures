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
    if (array == NULL) return NULL; 

    array->data = (flib_ptr)malloc(size * element_size);
    if ((void *)array->data == NULL) { free(array); return NULL; }

    array->size = size;
    array->element_size = element_size;

    memset((void *)array->data, 0, size * element_size);

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

void flib_array_fill(flib_array *array, void *item) {
    if (array == NULL || item == NULL) return;

    flib_ptr element = array->data;
    flib_ui8 data[4 * array->element_size];

    if (array->size > 4) {
        
        for (int i = 0; i < 4; i++) {
            memcpy(data + (i * array->element_size), item, array->element_size);
        }

        for (int i = 0; i < array->size / 4; i++) {
            memcpy((void *)element, data, 4 * array->element_size);
            element += 4 * array->element_size;
        }
    }
    
    for (int i = 0; i < array->size % 4; i++) {
        memcpy((void *)element, item, array->element_size);
        element += array->element_size;
    }
}

void flib_array_resize(flib_array *array, flib_ui32 size) {
    if (array == NULL) return;

    flib_ptr tmp = 0;
    
    if (size == 0) {
        tmp = (flib_ptr)realloc((void *)array->data, array->element_size);
        if ((void *)tmp == NULL) return;
        memset((void *)tmp, 0, array->element_size);
    } else {
        tmp = (flib_ptr)realloc((void *)array->data, array->element_size * size);
        if ((void *)tmp == NULL) return;
        if (size > array->size) memset((void *)(tmp + (array->size * array->element_size)), 0, (size - array->size) * array->element_size);
    }
    
    array->data = tmp;
    array->size = size;
}

void flib_array_sort(flib_array *array, flib_compare_func compare_func) {
    if (array == NULL || compare_func == NULL) return;
    qsort((void *)array->data, array->size, array->element_size, compare_func);
}

flib_i32 flib_array_find(flib_array *array, void *item) {
    if (array == NULL || item == NULL) return -1;

    flib_ptr element = array->data;

    for (int i = 0; i < array->size; i++) {
        if (memcmp((void *)element + (i * array->element_size), item, array->element_size) == 0) return i;
    }

    return -1;
}

const void *flib_array_get_ptr(flib_array *array) {
    if (array == NULL) return NULL;
    return (void *)array->data;
}
