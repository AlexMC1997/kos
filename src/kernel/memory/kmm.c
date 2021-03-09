//Kernel Memory Manager
//Basic slab allocator for kernel data structures

#include <stddef.h>
#include "vmm.h"
#include "kmm.h"
#include "mem.h"
#include "panic.h"

static Obj_Cache caches[KERN_OBJ_NUM];
static void* kmm_break = (void*)KERN_TOP;

//Expands Kernel heap by len 4k pages.
void* kbrk(pg_num_4k_t len)
{
    pg_num_4k_t brk_addr = ((pg_num_4k_t)(kmm_break) >> 12);
    vmm_pd_vm_alloc(len, brk_addr, (Alloc_Flags){1, 0, 0, 0}, KERN_PD);
    void* ptr = kmm_break;
    kmm_break += len << 12;
    return ptr;
}

//Allocates a slab on kernel heap and returns its address.
static Slab* slab_alloc(size_t obj_sz, pg_num_4k_t slab_sz)
{
    Slab* the_slab = kbrk(slab_sz);
    void* objs = &(the_slab->objs);
    void** tmp;
    size_t i, end = (slab_sz * PG_SIZE) - sizeof(Slab) - 2*obj_sz;
    
    the_slab->last_free = (void**)objs;
    the_slab->next = NULL;
    the_slab->state = SLAB_FREE;

    for (i = 0; i < end; i += obj_sz) {
        tmp = objs + i;
        *tmp = objs + i + obj_sz;
    }
    tmp = objs + i;
    *tmp = NULL;
    
    return the_slab;
}

//Allocates memory for a Kernel object of type.
//The allocation must be for a Kernel object of type;
//undefined behavior otherwise, with likely fatal consequences
//for the memory subsystem.
void* kmalloc(kern_objs_e type)
{
    if (type >= KERN_OBJ_NUM)
        panic("Invalid Kernel object.");

    pg_num_4k_t slab_sz = caches[type].slab_sz;
    size_t obj_sz = caches[type].obj_sz;
    Slab* slab = caches[type].slabs;
    void* fetch = NULL;

    while (slab->state == SLAB_FULL) {
        if (!slab->next)
            goto new_slab;
        slab = slab->next;
    }

    fetch = slab->last_free;
    slab->last_free = *(slab->last_free);
    slab->state = SLAB_PARTIAL;
    if (!slab->last_free)
        slab->state = SLAB_FULL;
    goto end;

    new_slab:
    slab->next = slab_alloc(obj_sz, slab_sz);
    slab = slab->next;
    slab->state = SLAB_PARTIAL;
    fetch = slab->last_free;
    slab->last_free = *(slab->last_free);

    end:
    return fetch;
}

//Initializes the slab allocator.
//Each kernel object needs a cache which stores
//its size and the size of its corresponding slab
//in pages along with a pointer to the slab list itself.
int kmm_init()
{
    new_cache(TEST_OBJ, test, 1);
    new_cache(TEST2_OBJ, test2, 3);
    new_cache(TEST3_OBJ, test3, 1);

    return 0;
}

int kfree(void* ptr, kern_objs_e type)
{
    return 0;
}