#ifndef _IO_H
#define _IO_H
#include "stdint.h"
#include "gcc.h"

#define outb(b, p) asm("outb %1, %0" : : "dN"(p), "a"(b))
#define inb(b, p) asm("inb %1, %0" : "=a"(b) : "dN"(p))
#define cli() asm("cli")
#define sti() asm("sti")
#define hlt() asm("hlt")

//Returns the current value of the stack pointer
static inline uint32_t gcc_inline r_esp() {
    register uint32_t reg_eax asm("%eax");
    asm volatile ("movl %esp, %eax"); 
    return reg_eax; 
}

typedef uint16_t port16;

#endif