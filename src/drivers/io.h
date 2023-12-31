#ifndef _IO_H
#define _IO_H

#include "stdint.h"
#include "gcc.h"

#define outb(b, p) asm volatile ("outb %1, %0" : : "dN"(p), "a"(b))
#define inb(b, p) asm volatile ("inb %1, %0" : "=a"(b) : "dN"(p))
#define cli() asm("cli")
#define sti() asm("sti")
#define hlt() asm("hlt")
#define mbar() asm volatile ("":::"memory")
#define mfence() asm volatile ("mfence":::"memory")
#define pause() asm volatile ("pause":::"memory")

//Returns the current value of the stack pointer
static inline gcc_inline uint32_t r_esp() {
    register uint32_t reg_esp asm("%esp");
    return reg_esp; 
}

//Returns the current value of the CR2 register
static inline gcc_inline uint32_t r_cr2() {
    register uint32_t reg_eax asm("%eax");
    asm volatile ("movl %cr2, %eax"); 
    return reg_eax; 
}

typedef uint16_t port16;

#endif