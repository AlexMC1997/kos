#ifndef _KMMAP_H
#define _KMMAP_H

#include "stdint.h"
#include "multiboot.h"

#define KMMAP_LEN 20

typedef enum {
    MEM_FREE = 1,
    MEM_RESERVED,
    MEM_ACPI,
    MEM_PRESERVED,
    MEM_BAD
} Mem_Type;

typedef struct {
    Mem_Type type;
    size_t size;
    void* addr;
} Memarea;

extern Memarea kmmap[KMMAP_LEN];
extern size_t kmmap_len;

void kmmap_init(size_t len, multiboot_mmap* m_mmap);

#endif