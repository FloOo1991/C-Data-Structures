#include <string.h>
#include "flib_list.h"

typedef struct flib_list {
    flib_ptr data;
    flib_ui32 capacity;
    flib_ui32 size;
    flib_ui32 element_size;
} flib_list;

void _flib_list_resize(flib_list *list, flib_ui32 new_cap);

flib_list* flib_list_alloc(flib_ui32 capacity, flib_ui32 element_size) {
    flib_list *list = (flib_list *)malloc(sizeof(flib_list));
    if (list == NULL) return NULL;

    list->data = (flib_ptr)malloc(capacity * element_size);
    if ((void *)list->data == NULL) { free(list); return NULL; }

    memset((void *)list->data, 0, capacity * element_size);
    list->capacity = capacity;
    list->element_size = element_size;
    list->size = 0;

    return list;
}

void flib_list_dealloc(flib_list** list) {
    if (list == NULL || *list == NULL) return;
    if ((void *)(*list)->data != NULL) free((void *)(*list)->data);
    free(*list);
    *list = NULL;
}

flib_ui32 flib_list_get_size(const flib_list* list) {
    if (list == NULL) return 0;
    return list->size;
}

flib_ui32 flib_list_get_capacity(const flib_list* list) {
    if (list == NULL) return 0;
    return list->capacity;
}

flib_i32 flib_list_is_empty(const flib_list* list) {
    if (list == NULL) return 1;
    return list->size == 0;
}

void* flib_list_get_item(const flib_list* list, flib_ui32 index) {
    if (list == NULL) return NULL;
    if (index >= list->size) return NULL;

    flib_ptr element = list->data + (list->element_size * index);
    return (void *)element;
}

void flib_list_set_item(flib_list* list, flib_ui32 index, void* item) {
    if (list == NULL) return;
    if (item == NULL) return;
    if (index >= list->size) return;

    flib_ptr element = list->data + (list->element_size * index);
    memcpy((void *)element, item, list->element_size);
}

void flib_list_add(flib_list *list, void *item) {
    if (list == NULL || item == NULL) return;

    if (list->capacity == 0) {
        _flib_list_resize(list, 10);
    } else if (list->size >= list->capacity) {
        _flib_list_resize(list, list->capacity * 2);
    }

    flib_ptr element = list->data + (list->element_size * list->size);
    memcpy((void *)element, item, list->element_size);
    list->size++;
}

void flib_list_remove(flib_list *list) {
    if (flib_list_is_empty(list)) return;
    flib_list_remove_at(list, list->size - 1);
}

void flib_list_remove_at(flib_list *list, flib_ui32 index) {
    if (list == NULL || index >= list->size || flib_list_is_empty(list)) return;  

    flib_ptr element = list->data + (list->element_size * index);
    flib_i32 offset = (list->size - (index + 1));
    if (offset > 0) memmove((void *)element, (void*)(element + list->element_size), offset * list->element_size);

    list->size--;
    memset((void *)(list->data + (list->size * list->element_size)), 0, list->element_size);
}

void flib_list_clear(flib_list *list) {
    if (list == NULL || flib_list_is_empty(list)) return;
    memset((void *)list->data, 0, list->element_size * list->size);
    list->size = 0;
}

void flib_list_shrink_to_fit(flib_list *list) {
    _flib_list_resize(list, list->size);
}

void flib_list_sort(flib_list* list, flib_compare_func comparer) {
    if (list == NULL || comparer == NULL) return;
    qsort((void *)list->data, list->size, list->element_size, comparer);
}

void flib_list_find(flib_list* list, void* item, flib_i32 *out_index) {
    if (out_index != NULL) *out_index = -1;
    if (list == NULL || item == NULL) return;

    flib_ptr element = list->data;

    for (int i = 0; i < list->size; i++) {
        if (memcmp((void *)element, item, list->element_size) == 0) { *out_index = i; return; }
        element += list->element_size;
    }
}

void _flib_list_resize(flib_list *list, flib_ui32 new_cap) {
    if (list == NULL) return;

    if (new_cap == 0) { free((void *)list->data); list->capacity = 0; list->size = 0; return; }
        
    flib_ptr tmp = (flib_ptr)realloc((void *)list->data, list->element_size * new_cap);
    if ((void *)tmp == NULL) return;

    list->data = tmp;
    list->capacity = new_cap;
    if (list->capacity <= list->size) list->size = list->capacity;
    else memset((void *)list->data + (list->element_size * list->size), 0, list->element_size * (list->capacity - list->size));
}