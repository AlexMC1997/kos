#ifndef _KMM_H
#define _KMM_H

#include <stddef.h>
#include "gcc.h"
#include "vmm.h"

#define new_cache(num, obj, slab_size) \
    caches[num].slabs = slab_alloc(sizeof(obj), slab_size);\
    caches[num].obj_sz = sizeof(obj);\
    caches[num].slab_sz = slab_size; 

typedef enum {
    SLL_NODE,
    HASH_TAB,
    TEST_OBJ,
    TEST2_OBJ,
    TEST3_OBJ,
    KERN_OBJ_NUM
} kern_objs_e;

typedef enum {
    SLAB_FULL,
    SLAB_FREE,
    SLAB_PARTIAL,
} slab_state_e;

typedef struct {
    int smth;
    char smwh[20];
} test;

typedef struct {
    int smth;
    char smwh[1200];
} test2;

typedef struct _test3 {
    test2* smth;
    struct _test3* next;
} test3;

typedef struct _Slab {
    slab_state_e state;
    void** last_free;
    struct _Slab* next;
    uint8_t objs;
} gcc_packed Slab;

typedef struct {
    Slab* slabs;
    size_t obj_sz;
    pg_num_4k_t slab_sz;
} Obj_Cache;

int kmm_init();
void* kbrk(pg_num_4k_t len);
void* kmalloc(kern_objs_e type);
int kfree(void* ptr, kern_objs_e type);

#endif