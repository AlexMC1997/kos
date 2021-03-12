//Defines functions handling a basic singly linked list.
//List has distinct head and tail nodes; the data
//field of the head node contains a pointer to the tail,
//the data field of the tail contains the length of the list.
//This allows the list to use only one slab type.
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "sll.h"
#include "kmm.h"
#include "string.h"

//Creates a new singly linked list whose first
//member contains data. This may be either a value
//type, or a pointer.
SLL* sll_new(void* data)
{
    SLL_Node* head = kmalloc(SLL_NODE);
    head->data = kmalloc(SLL_NODE);
    tail(head)->data = 1;
    head->next = kmalloc(SLL_NODE);
    tail(head)->next = head->next;
    head->next->data = data;
    head->next->next = NULL;
    return head;
}

SLL* sll_new_empty()
{
    SLL_Node* head = kmalloc(SLL_NODE);
    head->data = kmalloc(SLL_NODE);
    tail(head)->data = 0;
    head->next = NULL;
    tail(head)->next = NULL;
    return head;
}

//Initializes a new list from a variable number of arguments.
//Number of arguments must be specified in count.
SLL* sll_new_v(size_t count, ...)
{
    va_list args;
    SLL* list = sll_new_empty();
    va_start(args, count);

    for (size_t i = 0; i < count; i++)
        sll_add_back(list, va_arg(args, void*));

    return list;
}

//Initializes a new list from an array of length n.
SLL* sll_new_arr(size_t n, void* arr[])
{
    SLL* list = sll_new_empty();

    for (size_t i = 0; i < n; i++) 
        sll_add_back(list, arr[i]);

    return list;
}

//Returns length of list.
size_t sll_len(SLL* list)
{
    return (size_t)(tail(list)->data);
}

//Adds element to front of list and returns pointer to it.
SLL_Node* sll_add_front(SLL* list, void* data)
{
    SLL_Node* ptr = list->next;
    list->next = kmalloc(SLL_NODE);
    list->next->data = data;
    if (!tail(list)->data) 
        tail(list)->next = list->next;
    list->next->next = ptr;
    tail(list)->data++;
    return list->next;
}

//Adds element to back of list and returns pointer to it.
SLL_Node* sll_add_back(SLL* list, void* data)
{
    if (!tail(list)->data)
        return sll_add_front(list, data);
    tail(list)->next->next = kmalloc(SLL_NODE);
    tail(list)->next = tail(list)->next->next;
    tail(list)->next->data = data;
    tail(list)->next->next = NULL;
    tail(list)->data++;
    return tail(list)->next;
}

//Removes front node from list and returns data it contained.
//Constant time.
void* sll_remove_front(SLL* list)
{
    SLL_Node* rem = list->next;

    if (!rem)
        return NULL;

    void* data = rem->data;
    
    list->next = rem->next;
    tail(list)->data--;
    kfree(rem, SLL_NODE);

    return data;
}

//Removes node from back of list and returns data it contained.
//Linear time.
void* sll_remove_back(SLL* list)
{
    SLL_Node* cur = list;
    SLL_Node* rem;
    size_t len = sll_len(list);
    void* data;
    
    if (!len) 
        return NULL;

    for (size_t i = 0; i < len - 1; i++, cur = cur->next);

    rem = cur->next;
    cur->next = NULL;
    data = rem->data;
    tail(list)->data--;
    tail(list)->next = cur;
    kfree(rem, SLL_NODE);

    return data;
}

//Gets data from list ind list element.
void* sll_get(SLL* list, size_t ind)
{   
    if (sll_len(list) < ind)
        return NULL;

    SLL_Node* cur = list->next;
    for (size_t i = 0; i < ind; i++)
        cur = cur->next;

    return cur->data;
}

//Checks if value is contained in list, returning
//1 if so and 0 otherwise.
int sll_contains_val(SLL* list, void* c)
{
    SLL_Node* cur = list->next;
    for (; cur->data != (void*)c; cur = cur->next) {
        if (!cur->next)
            return 0;
    }

    return 1;
}

//Searches list for an object n bytes long.
//Returns pointer to object that is contained
//in the list if found, otherwise returns NULL.
void* sll_find_obj(SLL* list, size_t n, void* obj)
{
    SLL_Node* cur = list->next;
    for (; memcmp(cur->data, obj, n); cur = cur->next) {
        if (!cur->next)
            return NULL;
    }

    return cur->data;
}

//Deletes list from memory.
void sll_destroy(SLL* list)
{
    for (; (volatile size_t)(tail(list)->data); sll_remove_front(list));

    kfree(tail(list), SLL_NODE);
    kfree(list, SLL_NODE);
}

void sll_foreach(SLL* list, void (*action)(SLL_Node*))
{
    SLL_Node* cur = list->next;

    for (; cur; cur = cur->next)
        action(cur);
}

void sll_to_array(SLL* list, void** arr)
{
    SLL_Node* cur = list->next;
    for (size_t i = 0; cur; cur = cur->next, i++)
        arr[i] = cur->data;
}
