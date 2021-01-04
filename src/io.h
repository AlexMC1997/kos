#ifndef __io
#define __io
#include "stdint.h"

#define outb(b, p) asm("outb %1, %0" : : "dN"(p), "a"(b))
#define inb(b, p) asm("inb %1, %0" : "=a"(b) : "dN"(p))
#define cli() asm("cli")
#define sti() asm("sti")

typedef uint16_t port16;

extern const port16 CRT_ADD_REG;
extern const port16 CRT_DATA_REG;
extern const port16 MISC_OUT_REG_RD;
extern const port16 MISC_OUT_REG_WR;
extern const port16 ATTR_ADD_REG;
extern const port16 ATTR_DATA_REG;

#endif