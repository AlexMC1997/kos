#ifndef _TRAP_H
#define _TRAP_H

#include <stdint.h>
#include <stddef.h>
#include <gcc.h>

typedef enum {
    FLT_DIV_BY_ZERO,
    FLT_DEBUG,
    INT_NMI,
    TRAP_BREAK,
    TRAP_OVF,
    FLT_BRE,
    FLT_INV_OP,
    FLT_NO_DEV,
    ABRT_DOUBLE_FAULT,
    FLT_CSO,
    FLT_INV_TSS,
    FLT_NO_SEG,
    FLT_SSF,
    FLT_GPF,
    FLT_PF,
} trap_no_e;

typedef struct {
    uint32_t ebp;
    uint32_t edi;
    uint32_t esi;
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
    uint16_t trap_no;
    uint32_t error_code;
    uintptr_t eip;
    uintptr_t cs;
    uint32_t eflags;
    uintptr_t esp;
    uintptr_t ss;
} gcc_packed Trap_Frame;

typedef struct {
    uint32_t present : 1;
    uint32_t write : 1;
    uint32_t user : 1;
    uint32_t reserved : 1;
    uint32_t fetch : 1;
} gcc_packed PF_Code;

#endif 

