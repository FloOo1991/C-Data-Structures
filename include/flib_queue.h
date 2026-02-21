#ifndef FLIB_QUEUE_H
#define FLIB_QUEUE_H
#include "flib_definitions.h"

typedef struct flib_queue flib_queue;

flib_queue *flib_queue_alloc(flib_ui32 capacity, flib_ui32 element_size);
void flib_queue_dealloc(flib_queue **queue);

flib_ui32 flib_queue_get_size(const flib_queue *queue);
flib_ui32 flib_queue_get_capacity(const flib_queue *queue);
flib_i32 flib_queue_is_empty(const flib_queue *queue);

void flib_queue_enqueue(flib_queue *queue, void *item);
void flib_queue_dequeue(flib_queue *queue, void *opt_out_item);

void *flib_queue_get_ptr(flib_queue *queue);
#endif /* FLIB_QUEUE_H */