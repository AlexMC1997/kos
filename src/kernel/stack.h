#ifndef _STACK_H
#define _STACK_H

#include "stdint.h"
#include "stddef.h"
#include "sll.h"
#include "gcc.h"

typedef SLL Stack;

static inline gcc_inline Stack* stack_new(void* data) {
    return sll_new(data);
}

static inline gcc_inline Stack* stack_new_empty() {
    return sll_new_empty();
}

static inline gcc_inline void stack_push(Stack* s, void* data) {
    sll_add_front(s, data);
}

static inline gcc_inline void* stack_pop(Stack* s) {
    return sll_remove_front(s);
}

static inline gcc_inline size_t stack_len(Stack* s) {
    return sll_len(s);
}

static inline gcc_inline int stack_contains(Stack* s, void* c) {
    return sll_contains_val(s, c);
}

static inline gcc_inline void stack_destroy(Stack* s) {
    sll_destroy(s);
}

#endif