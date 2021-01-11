#ifndef _PIC_H
#define _PIC_H

#include "io.h"

#define PIC_MASTER_COM 0x20
#define PIC_SLAVE_COM 0xA0
#define PIC_MASTER_IMR 0x21
#define PIC_SLAVE_IMR 0xA1

#define PIC_ICW1 0b00010011
#define PIC_ICW2 0x20
#define PIC_SLAVE_ICW2 0x28
#define PIC_ICW3 0x40
#define PIC_SLAVE_ICW3 0x28
#define PIC_ICW4 0b00000001

typedef struct {
    port16 com;
    port16 imr;
} pic;

void pic_init();
void pic_com(pic this, uint8_t command);
void pic_mask(pic this, uint8_t mask);

#endif