#ifndef __io
#define __io
#include "stdint.h"

#define outb(b, p) asm("outb %1, %0" : : "dN"(p), "a"(b))
#define inb(b, p) asm("inb %1, %0" : "=a"(b) : "dN"(p))
#define cli() asm("cli")
#define sti() asm("sti")

typedef uint16_t port16;

#endif