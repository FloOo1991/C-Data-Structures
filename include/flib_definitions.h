#ifndef FLIB_DEFINITIONS_H
#define FLIB_DEFINITIONS_H
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef char                flib_i8;
typedef short               flib_i16;
typedef int                 flib_i32;
typedef unsigned char       flib_ui8;
typedef unsigned short      flib_ui16;
typedef unsigned int        flib_ui32;

typedef long long           flib_i64;
typedef unsigned long long  flib_ui64;

typedef unsigned long long  flib_ptr;

#define FLIB_THROW_EXCEPTION(fmt, ...) do { fprintf(stderr, "Exception: " fmt "(in '%s', line '%d)\n", ##__VA_ARGS__, __FILE__, __LINE__); exit(-1); } while (0)
#define FLIB_THROW_NULL_EXCEPTION(param) FLIB_THROW_EXCEPTION("Parameter '" param "' is NULL.")

#define FLIB_NOT_IMPLEMENTED(fmt, ...) do { fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__); assert(0); } while(0)
#define FLIB_LOG_INFO(fmt, ...)  do { fprintf(stdout, "[INFO] " fmt "\n", ##__VA_ARGS__); } while(0)
#endif