#ifndef FLIB_STACK_H
#define FLIB_STACK_H
#include "flib_definitions.h"

typedef struct flib_stack flib_stack;

flib_stack *flib_stack_alloc(flib_ui32 capacity, flib_ui32 element_size);
void flib_stack_dealloc(flib_stack **stack);

flib_ui32 flib_stack_get_size(const flib_stack *stack);
flib_ui32 flib_stack_get_capacity(const flib_stack *stack);
flib_i32 flib_stack_is_empty(const flib_stack *stack);

void flib_stack_push(flib_stack *stack, void *item);
void flib_stack_pop(flib_stack *stack, void *opt_out_item);
void flib_stack_peek(flib_stack *stack, void *out_item);
#endif 