#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include "terminal.h"
#include "vgatext.h"
#include "string.h"
#include "panic.h"
#include "assert.h"
#include "multiboot.h"
#include "kmmap.h"
#include "cpu.h"
#include "acpi.h"
#include "pic.h"
#include "idt.h"
#include "gdt.h"
#include "io.h"
#include "pfa.h"
#include "vmm.h"

//Initializes the exception system, including the PIC and interrupts
void except_init()
{
    idt_init();
    tputs("IDT initialized\n");
    pic_init();
    tputs("PIC initialized\n");
    tss_init();
    tputs("TSS initialized\n");
}

//Initializes physical memory, including the Page Frame Allocator
void mem_init(size_t len, multiboot_mmap* m_mmap)
{
    kmmap_init(len, m_mmap);
    pfa_init(kmmap_len, kmmap);
}

//Kernel C entry; passed GRUB info for parsing
void kern_main(uint32_t magic, multiboot_info* mbi)
{
    if (magic != MULTIBOOT_MAGIC)
        panic("Multiboot magic mismatch.");

    cpu_init();
    mem_init(mbi->mmap_length, mbi->mmap_addr);
    acpi_init();

    vga_text_init();
    terminal_init();

    except_init();

    tprintf("%x\n", r_esp());

    VMS_Entry vm[3];
    PD_Entry* pd;

    vm[0].vm_addr = 1;
    vm[0].sz = 5;
    vm[0].flags.user = 0;
    vm[0].flags.write = 0;
    vm[1].vm_addr = 0xA;
    vm[1].sz = 3;
    vm[1].flags.user = 1;
    vm[1].flags.write = 1;
    vm[2].vm_addr = 0xA62F0;
    vm[2].sz = 150;
    vm[2].flags.user = 0;
    vm[2].flags.write = 1;

    vmm_vms_alloc(3, vm, &pd);
    
    return;
}