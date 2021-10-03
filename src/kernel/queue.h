#ifndef _QUEUE_H
#define _QUEUE_H

#include "stdint.h"
#include "stddef.h"
#include "sll.h"
#include "gcc.h"

typedef SLL Queue;

static inline gcc_inline Queue* queue_new(void* data) {
    return sll_new(data);
}

static inline gcc_inline Queue* queue_new_empty() {
    return sll_new_empty();
}

static inline gcc_inline void queue_enqueue(Queue* q, void* data) {
    sll_add_back(q, data);
}

static inline gcc_inline void* queue_peek(Queue* q) {
    return sll_get(q, 0);
}

static inline gcc_inline void* queue_dequeue(Queue* q) {
    return sll_remove_front(q);
}

static inline gcc_inline size_t queue_len(Queue* q) {
    return sll_len(q);
}

static inline gcc_inline int queue_contains(Queue* q, void* c) {
    return sll_contains_val(q, c);
}

static inline gcc_inline void queue_destroy(Queue* q) {
    sll_destroy(q);
}

static inline gcc_inline void queue_destroy_p(Queue* q, void (*action)(SLL_Node*)) {
    sll_destroy_p(q, action);
}

#endif