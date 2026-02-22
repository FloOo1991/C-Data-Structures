#ifndef FLIB_LINKED_LIST_H
#define FLIB_LINKED_LIST_H
#include "flib_definitions.h"

typedef struct flib_linked_list flib_linked_list;

flib_linked_list *flib_linked_list_alloc(flib_ui32 capacity, flib_ui32 element_size);
void flib_linked_list_dealloc(flib_linked_list **list);

void flib_linked_list_append(flib_linked_list *list, void *value);
void flib_linked_list_prepend(flib_linked_list *list, void *value);

flib_i32 flib_linked_list_is_empty(const flib_linked_list *list);
flib_ui32 flib_linked_list_get_size(const flib_linked_list *list);

void *flib_linked_list_get_front(const flib_linked_list *list);
void *flib_linked_list_get_last(const flib_linked_list *list);
#endif /* FLIB_LINKED_LIST_H */