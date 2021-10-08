#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>
#include "gcc.h"

typedef struct {
    uint16_t offset_0_15;
    uint16_t selector;
    uint8_t reserved;
    uint8_t type : 3;
    uint8_t D : 1;
    uint8_t S : 1;
    uint8_t DPL : 2;
    uint8_t P : 1;
    uint16_t offset_16_31;
} gcc_packed IDT_Entry;

typedef struct {
    uint16_t length;
    uint32_t offset;
} gcc_packed IDT_Desc;

void idt_init();

#endif