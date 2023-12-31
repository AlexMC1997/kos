#include "io.h"
#include "idt.h"
#include "string.h"
#include "terminal.h"
#include "mem.h"

extern const uint32_t _IVT_ENTRY_LEN; 
extern const uintptr_t _IVT_START;

IDT_Desc* idt_desc_ptr = (IDT_Desc*)KERN_IDT;
IDT_Entry IDT[256];

void idt_init()
{
    uint8_t* ptr = (uint8_t*)(&_IVT_START);
    uint16_t i = 0;

    //Hardware interrupts - not available to user space
    for (; i < 48; i++) {
        IDT[i].DPL = 0;
        IDT[i].offset_0_15 = (uint16_t)((uint32_t)(ptr + (_IVT_ENTRY_LEN * i)));
        IDT[i].offset_16_31 = (uint16_t)((uint32_t)(ptr + (_IVT_ENTRY_LEN * i)) >> 16);
        IDT[i].P = 1;
        IDT[i].reserved = 0;
        IDT[i].S = 0;
        IDT[i].D = 1;
        IDT[i].selector = 0x8;
        IDT[i].type = 0x6;
    }
    
    //Other interrupts - available to user space
    for (; i < 256; i++) {
        IDT[i].DPL = 3;
        IDT[i].offset_0_15 = (uint16_t)((uint32_t)(ptr + (_IVT_ENTRY_LEN * i)));
        IDT[i].offset_16_31 = (uint16_t)((uint32_t)(ptr + (_IVT_ENTRY_LEN * i)) >> 16);
        IDT[i].P = 1;
        IDT[i].reserved = 0;
        IDT[i].S = 0;
        IDT[i].D = 1;
        IDT[i].selector = 0x8;
        IDT[i].type = 0x6;
    }

    idt_desc_ptr->length = 256 * sizeof(IDT_Entry);
    idt_desc_ptr->offset = (uint32_t)IDT;

    asm volatile ("lidtl (%c0)" : : "i"(KERN_IDT));
}