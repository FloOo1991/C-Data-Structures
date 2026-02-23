#ifndef FLIB_LIST_H
#define FLIB_LIST_H
#include "flib_definitions.h"

typedef struct flib_list flib_list;
typedef struct flib_list_iterator flib_list_iterator;

flib_i32 flib_list_create(flib_size_t _Capacity, flib_size_t _ElementSize, flib_list **_OutList);
void flib_list_destroy(flib_list **_List);

flib_size_t flib_list_get_size(flib_list *_List);
flib_size_t flib_list_get_capacity(flib_list *_List);
flib_i32 flib_list_is_empty(flib_list *_List);

void *flib_list_get_element(flib_list *_List, flib_ui32 _Index);

flib_i32 flib_list_append(flib_list *_List, void *_Element);
flib_i32 flib_list_prepend(flib_list *_List, void *_Element);
flib_i32 flib_list_fill(flib_list *_List, void *_Element);
flib_i32 flib_list_remove_at(flib_list *_List, flib_ui32 _Index);
flib_i32 flib_list_swap_remove_at(flib_list *_List, flib_ui32 _Index);
flib_i32 flib_list_shrink_to_fit(flib_list *_List);

flib_i32 flib_list_filter(flib_list *_List, flib_predicate_func _Predicate);

void flib_list_sort(flib_list *_List, flib_compare_func _CompareFunc);

typedef struct flib_list_iterator {
    const flib_list *_List;
    flib_i64 _Index;
} flib_list_iterator;

flib_list_iterator flib_list_iterator_create(flib_list *_List);
flib_i32 flib_list_iterator_move_next(flib_list_iterator *_Iterator);
const void *flib_list_iterator_get_current(flib_list_iterator *_Iterator);
#endif /* FLIB_LIST_H */