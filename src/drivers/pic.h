#ifndef _PIC_H
#define _PIC_H

#include "io.h"

#define PIC_MASTER_COM 0x20
#define PIC_SLAVE_COM 0xA0
#define PIC_MASTER_IMR 0x21
#define PIC_SLAVE_IMR 0xA1

#define PIC_ICW1 0b00010001
#define PIC_ICW2 0x20
#define PIC_SLAVE_ICW2 0x28
#define PIC_ICW3 0x4
#define PIC_SLAVE_ICW3 0x2
#define PIC_ICW4 0b00000001
#define PIC_EOI 0x20

#define PIC_IRQ_TIMER 0b00000001
#define PIC_IRQ_KB 0b00000010

typedef enum pic_irq {
    PIC_IRQ0,
    PIC_IRQ1,
    PIC_IRQ2,
    PIC_IRQ3,
    PIC_IRQ4,
    PIC_IRQ5,
    PIC_IRQ6,
    PIC_IRQ7,
    PIC_IRQ8,
    PIC_IRQ9,
    PIC_IRQ10,
    PIC_IRQ11,
    PIC_IRQ12,
    PIC_IRQ13,
    PIC_IRQ14,
    PIC_IRQ15,
} e_pic_irq;

typedef struct {
    port16 com;
    port16 imr;
} pic;

void pic_init();
void pic_com(pic this, uint8_t command);
void pic_mask(pic this, uint8_t mask);
void pic_eoi(e_pic_irq irq);

#endif