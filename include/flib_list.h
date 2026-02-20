#ifndef FLIB_LIST_H
#define FLIB_LIST_H
#include "flib_definitions.h"

typedef struct flib_list flib_list;
typedef flib_i32 (* flib_list_compare_func)(const void *lhs, const void *rhs);

#define flib_list_foreach(item, list) for (int i = 0; i < (list)->size && ((item) = flib_list_get_item((list), i)); i++)

/**
 * @brief Creates and allocates a new empty list.
 * 
 * @param capacity The capacity of the list initialized.
 * @param element_size The size of one element in bytes of the type the list should contain.
 * @return A pointer to the list on success, otherwise NULL.
 */
flib_list *flib_list_alloc(flib_ui32 capacity, flib_ui32 element_size);
void flib_list_dealloc(flib_list **list);

flib_ui32 flib_list_get_size(const flib_list *list);
flib_ui32 flib_list_get_capacity(const flib_list *list);
flib_i32 flib_list_is_empty(const flib_list *list);

void *flib_list_get_item(const flib_list *list, flib_ui32 index);
flib_i32 flib_list_set_item(flib_list *list, flib_ui32 index, void *item);

flib_i32 flib_list_add(flib_list *list, void *item);
void flib_list_remove(flib_list *list);
void flib_list_remove_at(flib_list *list, flib_ui32 index);

void flib_list_sort(flib_list *list, flib_list_compare_func comparer);
void flib_list_find(flib_list *list, void *item, flib_i32 *out_index);

#endif /* FLIB_LIST_H */