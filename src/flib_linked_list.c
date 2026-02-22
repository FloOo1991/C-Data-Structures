#include <string.h>
#include "flib_linked_list.h"

typedef struct flib_linked_list_node {
    flib_ui32 node_index;
    flib_ui32 next_index;
    flib_ui32 prev_index;
} flib_linked_list_node;

typedef struct flib_linked_list {
    flib_linked_list_node *nodes;
    flib_ptr data;
    flib_ui32 capacity;
    flib_ui32 size;
    flib_ui32 element_size;
    flib_ui32 head_index;
} flib_linked_list;

void _flib_linked_list_resize(flib_linked_list *list, flib_ui32 new_cap);

flib_linked_list *flib_linked_list_alloc(flib_ui32 capacity, flib_ui32 element_size) {
    flib_linked_list *list = (flib_linked_list *)malloc(sizeof(flib_linked_list));
    if (list == NULL) return NULL;

    flib_linked_list_node *nodes = (flib_linked_list_node *)malloc(sizeof(flib_linked_list_node) * capacity);
    if (nodes == NULL) { free(list); return NULL; }

    flib_ptr data = (flib_ptr)malloc(capacity * element_size);
    if ((void *)data == NULL) {free(nodes); free(list); return NULL; }

    list->nodes = nodes;
    list->data = data;
    list->capacity = capacity;
    list->size = 0;
    list->element_size = element_size;
    list->head_index = 0;

    return list;
}

void flib_linked_list_dealloc(flib_linked_list **list) {
    if (list == NULL || *list == NULL) return;
    
    if ((*list)->nodes != NULL) free((*list)->nodes);
    if ((void *)(*list)->data != NULL) free((void *)(*list)->data);

    free(*list);
    *list = NULL;
}

void flib_linked_list_append(flib_linked_list *list, void *value) {
    if (list == NULL || value == NULL) return;
    
    if (list->size >= list->capacity) _flib_linked_list_resize(list, list->capacity * 2);

    if (flib_linked_list_is_empty(list)) {
        flib_linked_list_node *node = &list->nodes[list->head_index];
        
        node->node_index = list->head_index;
        node->next_index = list->head_index;
        node->prev_index = list->head_index;

        void *data = (void *)list->data + (list->element_size * node->node_index);
        memcpy(data, value, list->element_size);
        
    } else if (flib_linked_list_get_size(list) == 1) {
        flib_linked_list_node *head = &list->nodes[list->head_index];
        flib_linked_list_node *node = &list->nodes[list->size];
        
        node->node_index = list->size;
        node->next_index = head->node_index;
        node->prev_index = head->node_index;
        head->next_index = node->node_index;
        head->prev_index = node->node_index;

        void *data = (void *)list->data + (list->element_size * node->node_index);
        memcpy(data, value, list->element_size);
    } else {
        flib_linked_list_node *head = &list->nodes[list->head_index];
        flib_linked_list_node *last = &list->nodes[head->prev_index];
        flib_linked_list_node *node = &list->nodes[list->size];

        node->node_index = list->size;
        head->prev_index = node->node_index;
        last->next_index = node->node_index;
        node->prev_index = last->node_index;
        node->next_index = head->node_index;

        void *data = (void *)list->data + (list->element_size * node->node_index);
        memcpy(data, value, list->element_size);
    }
 
    list->size++;
}

void flib_linked_list_prepend(flib_linked_list *list, void *value) {
    if (list == NULL || value == NULL) return;

    if (list->size >= list->capacity) _flib_linked_list_resize(list, list->capacity * 2);

    if (flib_linked_list_is_empty(list)) {
        flib_linked_list_node *node = &list->nodes[list->head_index];

        node->node_index = list->head_index;
        node->next_index = list->head_index;
        node->prev_index = list->head_index;

        void *data = (void *)list->data + (list->element_size * node->node_index);
        memcpy(data, value, list->element_size);
        
    } else if (flib_linked_list_get_size(list) == 1) {
        flib_linked_list_node *head = &list->nodes[list->head_index];
        flib_linked_list_node *node = &list->nodes[list->size];
        
        node->node_index = list->size;
        node->next_index = head->node_index;
        node->prev_index = head->node_index;
        head->next_index = node->node_index;
        head->prev_index = node->node_index;
        list->head_index = node->node_index;

        void *data = (void *)list->data + (list->element_size * node->node_index);
        memcpy(data, value, list->element_size);
    } else {
        flib_linked_list_node *head = &list->nodes[list->head_index];
        flib_linked_list_node *last = &list->nodes[head->prev_index];
        flib_linked_list_node *node = &list->nodes[list->size];

        node->node_index = list->size;
        head->prev_index = node->node_index;
        last->next_index = node->node_index;
        node->prev_index = last->node_index;
        node->next_index = head->node_index;
        list->head_index = node->node_index;

        void *data = (void *)list->data + (list->element_size * node->node_index);
        memcpy(data, value, list->element_size);
    }
 
    list->size++;
}

flib_i32 flib_linked_list_is_empty(const flib_linked_list *list) {
    if (list == NULL) return 0;
    return list->size == 0;
}

flib_ui32 flib_linked_list_get_size(const flib_linked_list *list) {
    if (list == NULL) return 0;
    return list->size;
}

void *flib_linked_list_get_front(const flib_linked_list *list) {
    if (list == NULL || flib_linked_list_is_empty(list)) return NULL;
    return (void *)list->data + (list->element_size * list->head_index);
}

void *flib_linked_list_get_last(const flib_linked_list *list) {
    if (list == NULL || flib_linked_list_is_empty(list)) return NULL;
    flib_ui32 tail_index = list->nodes[list->head_index].prev_index;
    return (void *)list->data + (list->element_size * tail_index);
}

void _flib_linked_list_resize(flib_linked_list *list, flib_ui32 new_cap) {
    if (list == NULL || list->capacity == new_cap) return;

    if (new_cap == 0) {
        if ((void *)list->data != NULL) free((void *)list->data);
        if (list->nodes != NULL) free(list->nodes);
        list->capacity = 0;
        list->size = 0;
        list->head_index = 0; 
        return; 
    }
        
    flib_linked_list_node *tmp_nodes = (flib_linked_list_node *)realloc(list->nodes, sizeof(flib_linked_list_node) * new_cap);
    if (tmp_nodes == NULL) return;

    flib_ptr tmp_data = (flib_ptr)realloc((void *)list->data, list->element_size * new_cap);
    if ((void *)tmp_data == NULL) return;
    
    list->nodes = tmp_nodes;
    list->data = tmp_data;
    list->capacity = new_cap;
    
    if (list->capacity <= list->size) list->size = list->capacity;
    else { 
        memset(list->nodes + list->size, 0, sizeof(flib_linked_list_node) * (list->capacity - list->size));
        memset((void *)list->data + (list->element_size * list->size), 0, list->element_size * (list->capacity - list->size));
    }
}
