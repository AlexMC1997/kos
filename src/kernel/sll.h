#ifndef _SLL_H
#define _SLL_H

#include "stdint.h"
#include "stddef.h"
#include "gcc.h"

#define tail(head) ((SLL_Node*)(head->data))

typedef struct _sll_node {
    void* data;
    struct _sll_node* next;
} gcc_packed SLL_Node;

typedef SLL_Node SLL;

SLL* sll_new(void* data);
SLL* sll_new_empty();
SLL* sll_new_v(size_t count, ...);
SLL* sll_new_arr(size_t n, void* arr[]);
size_t sll_len(SLL* list);
SLL_Node* sll_add_front(SLL* list, void* data);
SLL_Node* sll_add_back(SLL* list, void* data);
void* sll_remove_front(SLL* list);
void* sll_remove_back(SLL* list);
void* sll_get(SLL* list, size_t ind);
int sll_contains_val(SLL* list, void* c);
void* sll_find_obj(SLL* list, size_t n, void* obj);
void sll_destroy(SLL* list);
void sll_foreach(SLL* list, void (*action)(SLL_Node*));
void sll_to_array(SLL* list, void** arr);

#endif