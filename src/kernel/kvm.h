#ifndef _KVM_H
#define _KVM_H

#include <stddef.h>
#include <stdint.h>
#include "vmm.h"
#include "gdt.h"
#include "idt.h"

typedef struct {
    PD_Entry* pd;
    IDT_Desc* idt;
    GDT_Desc* gdt;
    void* stack_base;
    void* code_base;
    void* heap_base;
    
} Kernel;

#endif