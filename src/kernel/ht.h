#ifndef _HT_H
#define _HT_H

#include <stdint.h>
#include <stddef.h>
#include "gcc.h"
#include "sll.h"

typedef struct {
    uint8_t (*hash)(size_t, void*);
    SLL_Node* buckets[253];
} gcc_packed _Hash_Table;

typedef _Hash_Table HT_Obj;

typedef struct {
    uint8_t (*hash)(int);
    SLL_Node* buckets[253];
} gcc_packed HT_Int;

#endif