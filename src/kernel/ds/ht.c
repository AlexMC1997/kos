#include <stdint.h>
#include <stddef.h>
#include "ht.h"
#include "kmm.h"
#include "string.h"

HT_Obj* ht_obj_new(uint8_t (*hash)(size_t, void*))
{
    HT_Obj* table = kmalloc(HASH_TAB);
    memset(table, 0, sizeof(HT_Obj));
    table->hash = hash;

    return table;
}

HT_Int* ht_int_new(uint8_t (*hash)(int))
{
    HT_Int* table = kmalloc(HASH_TAB);
    memset(table, 0, sizeof(HT_Int));
    table->hash = hash;

    return table;
}

void ht_obj_add(HT_Obj* table, void* data, size_t sz)
{
    size_t ind = (table->hash)(sz, data);
    SLL_Node* cur = table->buckets[ind];


}