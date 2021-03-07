//Kernel Memory Manager
//Basic slab allocator for kernel data structures

#include <stddef.h>
#include "vmm.h"
#include "kmm.h"
#include "mem.h"

Obj_Cache caches[KERN_OBJ_NUM];
void* kmm_break = KERN_TOP;

//Expands Kernel heap by len 4k pages.
void* kbrk(pg_num_4k_t len)
{
    pg_num_4k_t brk_addr = (pg_num_4k_t)((uintptr_t)(kmm_break) >> 12);
    vmm_pd_vm_alloc(len, brk_addr, (Alloc_Flags){1, 0, 0, 0}, KERN_PD);
    void* ptr = kmm_break;
    kmm_break += len << 12;
    return ptr;
}

//Allocates a slab on kernel heap and returns its address.
static Slab* slab_alloc(size_t obj_sz, pg_num_4k_t slab_sz)
{
    Slab* the_slab = kbrk(slab_sz);
    uint8_t* objs = &(the_slab->objs);
    size_t* tmp;
    size_t end = (slab_sz * PG_SIZE) - sizeof(Slab) - 2*obj_sz;
    
    the_slab->last_free = 0;
    the_slab->next = NULL;
    the_slab->state = SLAB_FREE;

    size_t i = 0;
    for (size_t k = 1; i < end; i += obj_sz, k++) {
        tmp = objs + i;
        //who even knows why
        while ((*tmp = k) != k);
    }
    tmp = objs + i;
    *tmp = -1;
    
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
    size_t fetch = 0;

    while (slab->state == SLAB_FULL) {
        if (!slab->next)
            goto new_slab;
        slab = slab->next;
    }

    fetch = slab->last_free;
    slab->last_free = *(uint32_t*)(&(slab->objs) + (slab->last_free * obj_sz));
    slab->state = SLAB_PARTIAL;
    if (slab->last_free == -1)
        slab->state = SLAB_FULL;
    goto end;

    new_slab:
    slab->next = slab_alloc(obj_sz, slab_sz);
    slab = slab->next;
    slab->state = SLAB_PARTIAL;
    slab->last_free = 1;
    fetch = 0;

    end:
    return (&slab->objs) + (fetch * obj_sz);
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
}

int kfree(void* ptr, kern_objs_e type)
{

}