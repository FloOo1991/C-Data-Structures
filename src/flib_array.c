#include "flib_array.h"

typedef struct flib_array {
    void             *_Data;
    flib_size_t      _Size;
    flib_size_t      _ElementSize;
} flib_array;

flib_array* flib_array_create(flib_size_t _Size, flib_size_t _ElementSize) {
    flib_array *array = (flib_array *)malloc(sizeof(flib_array));
    if (array == NULL) return NULL; 

    void *data = calloc(_Size, _ElementSize);
    if (data == NULL) { free(array); return NULL; }

    array->_Data = data;
    array->_Size = _Size;
    array->_ElementSize = _ElementSize;

    return array;
}

void flib_array_destroy(flib_array **_Array) {
    if (_Array == NULL || *_Array == NULL) return;
    if ((*_Array)->_Data != NULL) free((*_Array)->_Data);
    
    free(*_Array);
    *_Array = NULL;
}

flib_ui32 flib_array_get_size(flib_array *_Array) {
    if (_Array == NULL) return 0;
    return _Array->_Size;
}

void *flib_array_get_item(flib_array *_Array, flib_ui32 _Index) {
    if (_Array == NULL || _Index >= _Array->_Size) return NULL;
    return (void *)((flib_ui8 *)_Array->_Data + (_Array->_ElementSize * _Index));
}

void flib_array_set_item(flib_array *_Array, flib_ui32 _Index, void *_Data) {
    if (_Array == NULL || _Index >= _Array->_Size) return;
    memcpy((flib_ui8 *)_Array->_Data + (_Array->_ElementSize * _Index), _Data, _Array->_ElementSize);
}

void flib_array_fill(flib_array *_Array, void *_Item) {
    if (_Array == NULL || _Array->_Size == 0 || _Item == NULL) return;

    flib_ui8 *array_data = (flib_ui8 *)_Array->_Data;
    memcpy(array_data, _Item, _Array->_ElementSize);

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
}

void flib_array_resize(flib_array *_Array, flib_size_t _NewSize) {
    if (_Array == NULL || _Array->_Size == _NewSize) return;

    if (_NewSize == 0) {
        free(_Array->_Data);
        
        _Array->_Data = NULL;
        _Array->_Size = 0;
        
        return;
    } else {
        void *ptr = NULL;
        if (!flib_recalloc(_Array->_Data, _Array->_Size, _NewSize, _Array->_ElementSize, &ptr)) return;          
        _Array->_Data = ptr;
    }
    
    _Array->_Size = _NewSize;
}

void flib_array_sort(flib_array *_Array, flib_compare_func _CompareFunc) {
    if (_Array == NULL || _CompareFunc == NULL) return;
    qsort(_Array->_Data, _Array->_Size, _Array->_ElementSize, _CompareFunc);
}

flib_i32 flib_array_find(flib_array *_Array, void *_Item) {
    if (_Array == NULL || _Item == NULL) return -1;

    for (int i = 0; i < _Array->_Size; i++) {
        if (memcmp((flib_ui8 *)_Array->_Data + (i * _Array->_ElementSize), _Item, _Array->_ElementSize) == 0) return i;
    }

    return -1;
}
