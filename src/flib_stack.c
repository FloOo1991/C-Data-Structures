#include <string.h>
#include "flib_stack.h"

typedef struct flib_stack {
    flib_ptr data;
    flib_ui32 capacity;
    flib_ui32 size;
    flib_ui32 element_size;
} flip_stack;

void _flib_stack_resize(flib_stack *stack, flib_ui32 new_cap);

flib_stack *flib_stack_alloc(flib_ui32 capacity, flib_ui32 element_size) {
    flib_stack *stack = (flib_stack *)malloc(sizeof(flib_stack));
    if (stack == NULL) return NULL;

    stack->data = (flib_ptr)malloc(capacity * element_size);
    if ((void *)stack->data == NULL) { free(stack); return NULL; }

    memset((void *)stack->data, 0, capacity * element_size);
    stack->capacity = capacity;
    stack->size = 0;
    stack->element_size = element_size;

    return stack;
}

void flib_stack_dealloc(flib_stack **stack) {
    if (stack == NULL || *stack == NULL) return;

    if ((void *)(*stack)->data != NULL) free((void *)(*stack)->data);
    free(*stack);
}

flib_ui32 flib_stack_get_size(const flib_stack *stack) {
    if (stack == NULL) return 0;
    return stack->size;
}

flib_ui32 flib_stack_get_capacity(const flib_stack *stack) {
    if (stack == NULL) return 0;
    return stack->capacity;
}

flib_i32 flib_stack_is_empty(const flib_stack *stack) {
    if (stack == NULL) return 1;
    return stack->size == 0;
}

void flib_stack_push(flib_stack *stack, void *item) {
    if (stack == NULL || item == NULL) return;

    if (stack->capacity == 0) {
        _flib_stack_resize(stack, 10);
    } else if (stack->size >= stack->capacity) {
        _flib_stack_resize(stack, stack->capacity * 2);
    }

    flib_ptr element = stack->data + (stack->size * stack->element_size);
    memcpy((void *)element, item, stack->element_size);
    stack->size++;
}

void flib_stack_pop(flib_stack *stack, void *out_item) {
    if (stack == NULL) return;
    if (flib_stack_is_empty(stack)) return;

    if (out_item != NULL) memcpy(out_item, stack->data + (stack->element_size * (stack->size - 1)), stack->element_size);
    
    memset(stack->data + (stack->element_size * (stack->size - 1)), 0, stack->element_size);
    stack->size--;
}

void flib_stack_peek(flib_stack *stack, void *out_item) {
    if (stack == NULL || out_item == NULL) return;
    if (flib_stack_is_empty(stack)) return;

    memcpy(out_item, stack->data + (stack->element_size * (stack->size - 1)), stack->element_size);
}

void _flib_stack_resize(flib_stack *stack, flib_ui32 new_cap) {
    if (stack == NULL) return;

    flib_ptr tmp = (flib_ptr)realloc((void *)stack->data, new_cap * stack->element_size);
    if (tmp == NULL) return;

    stack->data = tmp;
    stack->capacity = new_cap;
    if (stack->capacity < stack->size) stack->size = stack->capacity;
    memset(stack->data + (stack->size * stack->element_size), 0, (stack->capacity - stack->size) * stack->element_size);
}