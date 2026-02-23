#include "flib_list.h"
#include "flib_array.h"

typedef struct flib_array {
    void             *_Data;
    flib_size_t      _Size;
    flib_size_t      _ElementSize;
} flib_array;

typedef struct flib_list {
    flib_array *_Array;
    flib_size_t _Size;
} flib_list;

flib_i32 flib_list_create(flib_size_t _Capacity, flib_size_t _ElementSize, flib_list **_OutList) {
    if (_OutList == NULL) return FLIB_FALSE;

    if (!flib_malloc(sizeof(flib_list), (void **)_OutList)) return FLIB_FALSE;
    if (!flib_array_create(_Capacity, _ElementSize, &(*_OutList)->_Array)) { free(*_OutList); *_OutList = NULL; return FLIB_FALSE; }

    (*_OutList)->_Size = 0;
    return FLIB_TRUE;
}

void flib_list_destroy(flib_list **_List) {
    if (_List == NULL) return;
    flib_array_destroy(&(*_List)->_Array);
    free(*_List);
    *_List = NULL;
}

flib_size_t flib_list_get_size(flib_list *_List) {
    if (_List == NULL) return 0;
    return _List->_Size;
}

flib_size_t flib_list_get_capacity(flib_list *_List) {
    if (_List == NULL) return 0;
    return _List->_Array->_Size;
}

flib_i32 flib_list_is_empty(flib_list *_List) {
    if (_List == NULL) return FLIB_TRUE;
    return _List->_Size == 0;
}

void *flib_list_get_element(flib_list *_List, flib_ui32 _Index) {
    if (_List == NULL) return NULL;
    return flib_array_get_element(_List->_Array, _Index);
}

flib_i32 flib_list_append(flib_list *_List, void *_Element) {
    if (_List == NULL || _Element == NULL) return FLIB_FALSE;
    if (_List->_Size >= _List->_Array->_Size) {
        if (!flib_array_resize(_List->_Array, _List->_Array->_Size * 2)) return FLIB_FALSE;
    }

    if (flib_array_set_element(_List->_Array, _List->_Size, _Element)) {
        _List->_Size++;
        return FLIB_TRUE;
    } 

    return FLIB_FALSE;
}

flib_i32 flib_list_prepend(flib_list *_List, void *_Element) {
    if (_List == NULL || _Element == NULL) return FLIB_FALSE;
    if (_List->_Size >= _List->_Array->_Size) {
        if (!flib_array_resize(_List->_Array, _List->_Array->_Size * 2)) return FLIB_FALSE;
    }

    memmove((flib_ui8 *)_List->_Array->_Data + _List->_Array->_ElementSize, _List->_Array->_Data, _List->_Size * _List->_Array->_ElementSize);

    if (flib_array_set_element(_List->_Array, 0, _Element)) {
        _List->_Size++;
        return FLIB_TRUE;
    }

    return FLIB_FALSE;
}

flib_i32 flib_list_fill(flib_list *_List, void *_Element) {
    if (_List == NULL || _Element == NULL) return FLIB_FALSE;
    if (flib_array_fill(_List->_Array, _Element)) {
        _List->_Size = _List->_Array->_Size;
        return FLIB_TRUE;
    }

    return FLIB_FALSE;
}

flib_i32 flib_list_remove_at(flib_list *_List, flib_ui32 _Index) {
    if (_List == NULL || _Index >= _List->_Size) return FLIB_FALSE;

    if (_Index < _List->_Size - 1) {
        memmove((flib_ui8 *)_List->_Array->_Data + (_List->_Array->_ElementSize * _Index), (flib_ui8 *)_List->_Array->_Data + (_List->_Array->_ElementSize * (_Index + 1)), _List->_Array->_ElementSize * (_List->_Size - _Index - 1));
    }

    memset((flib_ui8 *)_List->_Array->_Data + (_List->_Array->_ElementSize * (_List->_Size - 1)), 0, _List->_Array->_ElementSize);
    _List->_Size--;

    return FLIB_TRUE;
}

flib_i32 flib_list_swap_remove_at(flib_list *_List, flib_ui32 _Index) {
    if (_List == NULL || _Index >= _List->_Size) return FLIB_FALSE;

    if (_Index < _List->_Size - 1) {
        memmove((flib_ui8 *)_List->_Array->_Data + (_List->_Array->_ElementSize * _Index), (flib_ui8 *)_List->_Array->_Data + (_List->_Array->_ElementSize * (_List->_Size - 1)), _List->_Array->_ElementSize);
    }

    memset((flib_ui8 *)_List->_Array->_Data + (_List->_Array->_ElementSize * (_List->_Size - 1)), 0, _List->_Array->_ElementSize);
    _List->_Size--;

    return FLIB_TRUE;
}

flib_i32 flib_list_shrink_to_fit(flib_list *_List) {
    if (_List == NULL || _List->_Size == _List->_Array->_Size) return FLIB_FALSE;
    return flib_array_resize(_List->_Array, _List->_Size);
}

flib_i32 flib_list_filter(flib_list *_List, flib_predicate_func _Predicate) {
    if (_List == NULL || _Predicate == NULL) return FLIB_FALSE;

    for (int i = 0; i < _List->_Size; i++) {
        if (!_Predicate(flib_list_get_element(_List, i))) {
            flib_list_swap_remove_at(_List, i);
            i--;
        }
    }

    return FLIB_TRUE;
}

void flib_list_sort(flib_list *_List, flib_compare_func _CompareFunc) {
    if (_List == NULL) return;
    flib_array_sort(_List->_Array, _CompareFunc);
}

flib_list_iterator flib_list_iterator_create(flib_list *_List) {
    flib_list_iterator it = {
        ._List = _List,
        ._Index = -1
    };

    return it;
}

flib_i32 flib_list_iterator_move_next(flib_list_iterator *_Iterator) {
    if (_Iterator == NULL) return FLIB_FALSE;
    
    _Iterator->_Index++;
    return _Iterator->_Index < _Iterator->_List->_Size;
}

const void *flib_list_iterator_get_current(flib_list_iterator *_Iterator) {
    if (_Iterator == NULL) return NULL;
    return (const flib_ui8 *)_Iterator->_List->_Array->_Data + (_Iterator->_List->_Array->_ElementSize * _Iterator->_Index);
}
