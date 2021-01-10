#include <cpuid.h>
#ifndef _CPU_H
#define _CPU_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t stepping : 4;
    uint32_t model : 4;
    uint32_t family : 4;
    uint32_t type : 2;
    uint32_t ext_model : 4;
    uint32_t ext_family : 8;
} __attribute__((__packed__)) id_type;

typedef struct {
    uint32_t brand : 8;
    uint32_t clflush : 8;
    uint32_t cpu_cnt : 8;
    uint32_t apic_id : 8;
} __attribute__((__packed__)) id_cpu;

typedef struct { //Do not change structure
    char vendor[13];
    
    id_type family;
    id_cpu cpu_info;
    uint32_t feat_1;
    uint32_t feat_2;

    uint32_t conf_a;
    uint32_t conf_b;
    uint32_t conf_c;
    uint32_t conf_d;

} __attribute__((__packed__)) cpuid;

typedef struct {
    cpuid info;
} cpu;

extern uint32_t _check_cpuid();
extern void _get_cpuid(cpuid* info);

int8_t cpu_init();

#endif