#ifndef _KMMAP_H
#define _KMMAP_H

#include "stdint.h"
#include "multiboot.h"

#define KMMAP_LEN 20

typedef enum __mem_type {
    MEM_FREE = 1,
    MEM_RESERVED,
    MEM_ACPI,
    MEM_PRESERVED,
    MEM_BAD
} mem_type;

typedef struct __memarea {
    mem_type type;
    size_t size;
    void* addr;
} memarea;

memarea* kmmap_init(multiboot_mmap* m_mmap, size_t len);

#endif