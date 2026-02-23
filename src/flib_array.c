#include "flib_array.h"

typedef struct flib_array {
    void             *_Data;
    flib_size_t      _Size;
    flib_size_t      _ElementSize;
} flib_array;

flib_i32 flib_array_create(flib_size_t _Size, flib_size_t _ElementSize, flib_array **_OutArray) {
    if (_OutArray == NULL) return FLIB_FALSE;

    if (!flib_malloc(sizeof(flib_array), (void **)_OutArray)) return FLIB_FALSE;
    if (!flib_calloc(_Size, _ElementSize, &(*_OutArray)->_Data)) { free(*_OutArray); *_OutArray = NULL; return FLIB_FALSE; }

    (*_OutArray)->_Size = _Size;
    (*_OutArray)->_ElementSize = _ElementSize;

    return FLIB_TRUE;
}

void flib_array_destroy(flib_array **_Array) {
    if (_Array == NULL || *_Array == NULL) return;
    if ((*_Array)->_Data != NULL) free((*_Array)->_Data);
    
    free(*_Array);
    *_Array = NULL;
}

const void *flib_array_get_data(flib_array *_Array) {
    if (_Array == NULL) return NULL;
    return _Array->_Data;
}

flib_i32 flib_array_copy(flib_array *_SourceArray, flib_array **_OutCopy) {
    if (_SourceArray == NULL || _OutCopy == NULL) return FLIB_FALSE;
    if (!flib_array_create(_SourceArray->_Size, _SourceArray->_ElementSize, &*_OutCopy)) return FLIB_FALSE;

    memcpy((*_OutCopy)->_Data, _SourceArray->_Data, (*_OutCopy)->_Size * (*_OutCopy)->_ElementSize);
    return FLIB_TRUE;
}

flib_size_t flib_array_get_size(flib_array *_Array) {
    if (_Array == NULL) return 0;
    return _Array->_Size;
}

flib_i32 flib_array_is_empty(flib_array *_Array) {
    if (_Array == NULL) return 1;
    return _Array->_Size == 0;
}

void *flib_array_get_element(flib_array *_Array, flib_ui32 _Index) {
    if (_Array == NULL || _Index >= _Array->_Size) return NULL;
    return (void *)((flib_ui8 *)_Array->_Data + (_Array->_ElementSize * _Index));
}

flib_i32 flib_array_set_element(flib_array *_Array, flib_ui32 _Index, void *_Element) {
    if (_Array == NULL || _Index >= _Array->_Size) return FLIB_FALSE;
    memcpy((flib_ui8 *)_Array->_Data + (_Array->_ElementSize * _Index), _Element, _Array->_ElementSize);
    return FLIB_TRUE;
}

flib_i32 flib_array_fill(flib_array *_Array, void *_Element) {
    if (_Array == NULL || _Array->_Size == 0 || _Element == NULL) return FLIB_FALSE;

    flib_ui8 *array_data = (flib_ui8 *)_Array->_Data;
    memcpy(array_data, _Element, _Array->_ElementSize);

    flib_size_t btc = _Array->_Size * _Array->_ElementSize;
    flib_size_t bc = _Array->_ElementSize;

    while (bc < btc) {
        flib_size_t bl = btc - bc;

        if (bl > bc) {
            memcpy(array_data + bc, array_data, bc);
            bc += bc;
        } else {
            memcpy(array_data + bc, array_data, bl);
            bc += bl;
        }
    }
    
    return FLIB_TRUE;
}

flib_i32 flib_array_resize(flib_array *_Array, flib_size_t _NewSize) {
    if (_Array == NULL || _Array->_Size == _NewSize) return FLIB_FALSE;

    if (_NewSize == 0) {
        free(_Array->_Data);
        
        _Array->_Data = NULL;
        _Array->_Size = 0;
        
        return FLIB_TRUE;
    } else {
        void *ptr = NULL;
        if (!flib_recalloc(_Array->_Data, _Array->_Size, _NewSize, _Array->_ElementSize, &ptr)) return FLIB_FALSE;          
        _Array->_Data = ptr;
    }
    
    _Array->_Size = _NewSize;
    return FLIB_TRUE;
}

void flib_array_sort(flib_array *_Array, flib_compare_func _CompareFunc) {
    if (_Array == NULL || _CompareFunc == NULL) return;
    qsort(_Array->_Data, _Array->_Size, _Array->_ElementSize, _CompareFunc);
}

flib_i32 flib_array_find(flib_array *_Array, void *_Element) {
    if (_Array == NULL || _Element == NULL) return -1;

    for (int i = 0; i < _Array->_Size; i++) {
        if (memcmp((flib_ui8 *)_Array->_Data + (i * _Array->_ElementSize), _Element, _Array->_ElementSize) == 0) return i;
    }

    return -1;
}

flib_array_iterator flib_array_iterator_create(const flib_array *_Array)
{
    flib_array_iterator iterator = {
        ._Array = _Array,
        ._Index = -1
    };

    return iterator;
}

flib_i32 flib_array_iterator_move_next(flib_array_iterator *_Iterator)
{
    if (_Iterator == NULL) return 0;
    _Iterator->_Index++;
    return _Iterator->_Index < _Iterator->_Array->_Size; 
}

const void *flib_array_iterator_get_current(flib_array_iterator *_Iterator) {
    if (_Iterator == NULL) return NULL;

    return (const flib_ui8 *)_Iterator->_Array->_Data + (_Iterator->_Array->_ElementSize * _Iterator->_Index);
}
