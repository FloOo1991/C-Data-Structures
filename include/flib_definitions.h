#ifndef FLIB_DEFINITIONS_H
#define FLIB_DEFINITIONS_H
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FLIB_FALSE          0
#define FLIB_TRUE           1

typedef char                flib_i8;
typedef short               flib_i16;
typedef int                 flib_i32;
typedef unsigned char       flib_ui8;
typedef unsigned short      flib_ui16;
typedef unsigned int        flib_ui32;

typedef long long           flib_i64;
typedef unsigned long long  flib_ui64;

typedef unsigned long long  flib_size_t;

typedef long long           flib_intptr_t;
typedef unsigned long long  flib_uintptr_t;
typedef long long           flib_ptrdiff_t;

typedef flib_i32 (* flib_compare_func)(const void *_Lhs, const void *_Rhs);
typedef flib_i32 (* flib_predicate_func)(const void *_Element);

#define FLIB_THROW_EXCEPTION(fmt, ...) do { fprintf(stderr, "Exception: " fmt "(in '%s', line '%d)\n", ##__VA_ARGS__, __FILE__, __LINE__); exit(-1); } while (0)
#define FLIB_THROW_NULL_EXCEPTION(param) FLIB_THROW_EXCEPTION("Parameter '" param "' is NULL.")

#define FLIB_NOT_IMPLEMENTED(fmt, ...) do { fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__); assert(0); } while(0)
#define FLIB_LOG_INFO(fmt, ...)  do { fprintf(stdout, "[INFO] " fmt "\n", ##__VA_ARGS__); } while(0)

static inline flib_i32 flib_malloc(flib_size_t _Size, void **_OutMemory) {
    *_OutMemory = malloc(_Size);
    if (*_OutMemory == NULL) return 0;
    return 1;
}

static inline flib_i32 flib_calloc(flib_size_t _Size, flib_size_t _ElementSize, void **_OutMemory) {
    *_OutMemory = calloc(_Size, _ElementSize);
    if (*_OutMemory == NULL) return 0;
    return 1;
}

static inline flib_i32 flib_realloc(void *_Memory, flib_size_t _NewSize, void **_OutMemory) {
    *_OutMemory = realloc(_Memory, _NewSize);
    if (*_OutMemory == NULL) return 0;
    return 1;
}

static inline flib_i32 flib_recalloc(void *_Memory, flib_size_t _OldSize, flib_size_t _NewSize, flib_size_t _ElemenSize, void **_OutMemory) {
    *_OutMemory = realloc(_Memory, _NewSize * _ElemenSize);
    if (*_OutMemory == NULL) return 0;

    if (_NewSize > _OldSize) {
        memset((flib_ui8 *)*_OutMemory + (_OldSize * _ElemenSize), 0, (_NewSize - _OldSize) * _ElemenSize);
    }

    return 1;
}
#endif