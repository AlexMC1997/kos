#pragma GCC push_options
#pragma GCC optimize("O0")

#include <limits.h>
#include <stddef.h>
#include "gdt.h"
#include "io.h"
#include "terminal.h"

GDT_Entry GDT[] = {
    { //NULL segment
        .limit_0_15 =   0,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    0,
        .DC =    0,
        .Ex =    0,
        .S =     0,
        .Privl = 0,
        .Pr =    0,
        .limit_16_19 = 0,
        .none = 0,
        .Sz = 0,
        .Gr = 0,
        .base_24_31 = 0
    },
    { //Kernel Code Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    1,
        .S =     1,
        .Privl = 0,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //Kernel Data Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    0,
        .S =     1,
        .Privl = 0,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //User Code Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    1,
        .S =     1,
        .Privl = 3,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //User Data Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    0,
        .S =     1,
        .Privl = 3,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //Task State Selector
        .limit_0_15 =  0xFFFF & sizeof(TSS_Entry),
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    1, //TSS not LDT
        .RW =    0, //Not busy
        .DC =    0,
        .Ex =    1, //1 is 32 bit
        .S =     0, 
        .Privl = 0,
        .Pr =    1,
        .limit_16_19 = sizeof(TSS_Entry) >> 16,
        .none = 0,
        .Sz = 1,
        .Gr = 0,
        .base_24_31 = 0
    }
};

const GDT_Desc GDT_DESCRIPT = { (6*sizeof(GDT_Entry))-1, GDT };
const GDT_Desc* GDT_DESCRIPT_PTR = &GDT_DESCRIPT;

TSS_Entry tss;

void tss_init()
{
    GDT[5].base_0_15 = (uint16_t)((uint32_t)&tss & 0xFFFF);
    GDT[5].base_16_23 = ((uint32_t)(&tss) >> 16) & 0xFF;
    GDT[5].base_24_31 = ((uint32_t)(&tss) >> 24) & 0xFF;

    tss.ss0 = GDT_KDATA_SEG;

    asm volatile ("movw $0x28, %%ax; ltr %%ax" : : : "ax");
}

void tss_set_stack(uint32_t stack)
{
    tss.esp0 = stack;
}

#pragma GCC pop_options