#ifndef _KMM_H
#define _KMM_H

#include <stddef.h>
#include "gcc.h"

typedef enum {
    TEST_OBJ,
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

typedef struct _slab {
    slab_state_e state;
    uint32_t last_free;
    struct _slab* next;
    uint8_t objs;
} gcc_packed slab;

typedef struct {
    slab* slabs;
    size_t obj_sz;
    pg_num_4k_t slab_sz;
} Obj_Cache;

int kmm_init();
void* kbrk(pg_num_4k_t len);
void* kmalloc(kern_objs_e type);

#endif