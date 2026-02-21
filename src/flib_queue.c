#include <string.h>
#include "flib_queue.h"

typedef struct flib_queue {
    flib_ptr data;
    flib_ui32 capacity;
    flib_ui32 size;
    flib_ui32 element_size;
} flib_queue;

void _flib_queue_resize(flib_queue *queue, flib_ui32 new_cap);

flib_queue *flib_queue_alloc(flib_ui32 capacity, flib_ui32 element_size) {
    flib_queue *queue = malloc(sizeof(flib_queue));
    if (queue == NULL) return NULL;
    
    queue->data = (flib_ptr)malloc(capacity * element_size);
    if ((void *)queue->data == NULL) { free(queue); return NULL; }

    memset((void *)queue->data, 0, capacity * element_size);
    queue->capacity = capacity;
    queue->size = 0;
    queue->element_size = element_size;

    return queue;
}

void flib_queue_dealloc(flib_queue **queue) {
    if (queue == NULL || *queue == NULL) return;

    if ((void *)(*queue)->data != NULL) free((void *)(*queue)->data);
    free(*queue);
}

flib_ui32 flib_queue_get_size(const flib_queue *queue) {
    if (queue == NULL) return 0;
    return queue->size;
}

flib_ui32 flib_queue_get_capacity(const flib_queue *queue) {
    if (queue == NULL) return 0;
    return queue->capacity;
}

flib_i32 flib_queue_is_empty(const flib_queue *queue) {
    if (queue == NULL) return 1;
    return queue->size == 0;
}

void flib_queue_enqueue(flib_queue *queue, void *item) {
    if (queue == NULL || item == NULL) return;

    if (queue->capacity == 0) {
        _flib_queue_resize(queue, 10);
    } else if (queue->size >= queue->capacity) {
        _flib_queue_resize(queue, queue->capacity * 2);
    }

    flib_ptr element = queue->data + (queue->size * queue->element_size);
    memcpy((void *)element, item, queue->element_size);
    queue->size++;
}

void flib_queue_dequeue(flib_queue *queue, void *opt_out_item) {
    if (queue == NULL) return;
    if (flib_queue_is_empty(queue)) return;

    if (opt_out_item != NULL) memcpy(opt_out_item, (void *)queue->data, queue->element_size);

    if (queue->size > 1) memmove((void *)queue->data, (void *)queue->data + queue->element_size, queue->element_size * (queue->size - 1));
    memset((void *)queue->data + (queue->element_size * (queue->size - 1)), 0, queue->element_size);
    queue->size--;

    if (queue->capacity > queue->size * 3) _flib_queue_resize(queue, queue->capacity * 0.5f);
}

void *flib_queue_get_ptr(flib_queue *queue) {
    if (queue == NULL) return NULL;
    return (void *)queue->data;
}

void _flib_queue_resize(flib_queue *queue, flib_ui32 new_cap) {
    if (queue == NULL) return;
    
    if (new_cap == 0) { free((void *)queue->data); queue->data = 0; queue->capacity = 0; queue->size = 0; return; }

    flib_ptr tmp = (flib_ptr)realloc((void *)queue->data, queue->element_size * new_cap);
    if ((void *)tmp == NULL) return;

    queue->data = tmp;
    queue->capacity = new_cap;
    if (queue->capacity <= queue->size) {
        queue->size = queue->capacity; 
    } else {
        memset((void *)queue->data + (queue->size * queue->element_size), 0, queue->element_size * (queue->capacity - queue->size));
    }
}
