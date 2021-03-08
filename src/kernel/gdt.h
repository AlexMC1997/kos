#include <stdint.h>
#include "gcc.h"

#define GDT_NULL_SEG 0
#define GDT_KCODE_SEG 0x8
#define GDT_KDATA_SEG 0x10
#define GDT_UCODE_SEG 0x18
#define GDT_UDATA_SEG 0x20
#define GDT_TASK_SEG 0x28

typedef struct {
    uint32_t prev;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint32_t trap;
    uint32_t iomap_base;
} gcc_packed tss_entry;

typedef struct {
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t base_16_23;
    uint8_t Ac : 1;
    uint8_t RW : 1;
    uint8_t DC : 1;
    uint8_t Ex : 1;
    uint8_t S : 1;
    uint8_t Privl : 2;
    uint8_t Pr : 1;
    uint8_t limit_16_19 : 4;
    uint8_t none : 2;
    uint8_t Sz : 1;
    uint8_t Gr : 1;
    uint8_t base_24_31;
} gcc_packed gdt_entry;

typedef struct {
    uint16_t size;
    const gdt_entry* offset;
} gcc_packed gdt_descript;

void tss_init();
void tss_set_stack(uint32_t stack);