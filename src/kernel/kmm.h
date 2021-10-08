#ifndef _KMM_H
#define _KMM_H

#include <stddef.h>
#include "gcc.h"
#include "vmm.h"

#define new_cache(num, obj, slab_size) \
    caches[num].slabs = slab_alloc(sizeof(obj), slab_size);\
    caches[num].obj_sz = sizeof(obj);\
    caches[num].slab_sz = slab_size; 

//Enum defining all object types the kernel supports
typedef enum {
    NONE,
    SLL_NODE,
    DLL_NODE,
    HASH_TAB,
    MEM_256,
    MEM_1K,
    MEM_4K,
    MEM_16K,
    MEM_64K,
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
} gcc_packed test;

typedef struct {
    int smth;
    char smwh[1200];
} gcc_packed test2;

typedef struct _test3 {
    test2* smth;
    struct _test3* next;
} gcc_packed test3;

typedef struct _Slab {
    slab_state_e state;
    void** last_free;
    struct _Slab* next;
    uint8_t objs;
} gcc_packed Slab;

#define MEM_256_SZ (256 - sizeof(Slab))
#define MEM_1K_SZ (1024 - sizeof(Slab))
#define MEM_4K_SZ (4096 - sizeof(Slab))
#define MEM_16K_SZ (16384 - sizeof(Slab))
#define MEM_64K_SZ (65536 - sizeof(Slab))

typedef struct {
    uint8_t arr[MEM_256_SZ];
} gcc_packed Mem_256;

typedef struct {
    uint8_t arr[MEM_1K_SZ];
} gcc_packed Mem_1K;

typedef struct {
    uint8_t arr[MEM_4K_SZ];
} gcc_packed Mem_4K;

typedef struct { 
    uint8_t arr[MEM_16K_SZ];
} gcc_packed Mem_16K;

typedef struct {
    uint8_t arr[MEM_64K_SZ];
} gcc_packed Mem_64K;

typedef struct {
    Slab* slabs;
    size_t obj_sz;
    pg_num_4k_t slab_sz;
} gcc_packed Cache_Header;

int kmm_init();
void* kbrk(pg_num_4k_t len);
void* kmalloc(kern_objs_e type);
int kfree(void* ptr, kern_objs_e type);

#endif