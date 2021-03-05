#include "kmmap.h"
#include "pfa.h"
#include "panic.h"

Memarea kmmap[KMMAP_LEN];
size_t kmmap_len;

void kmmap_init(size_t len, multiboot_mmap* m_mmap)
{
    kmmap_len = len / sizeof(multiboot_mmap);
    for (size_t i = 0; i < kmmap_len; i++) {
        if (m_mmap[i].base_addr_high) {
            panic("Memory map has 64 bit address.");
        } else if (m_mmap[i].length_high) {
            panic("Memory map has long entry.");
        }
        kmmap[i].addr = (void*)m_mmap[i].base_addr_low;
        kmmap[i].size = m_mmap[i].length_low;
        kmmap[i].type = (Mem_Type)m_mmap[i].type;
    }
}