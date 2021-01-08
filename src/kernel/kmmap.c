#include "kmmap.h"
#include "panic.h"

memarea kmmap[KMMAP_LEN];

memarea* kmmap_init(multiboot_mmap* m_mmap, size_t len)
{
    size_t end = len / sizeof(multiboot_mmap);
    for (size_t i = 0; i < end; i++) {

        if (m_mmap[i].base_addr_high) {
            panic("Memory map has 64 bit address.");
        } else if (m_mmap[i].length_high) {
            panic("Memory map has long entry.");
        }
        kmmap[i].addr = (void*)m_mmap[i].base_addr_low;
        kmmap[i].size = m_mmap[i].length_low;
        kmmap[i].type = (mem_type)m_mmap[i].type;
    }

    return kmmap;
}