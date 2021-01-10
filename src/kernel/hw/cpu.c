#include "cpu.h"
#include "panic.h"

cpu cur_cpu;

int8_t cpu_init()
{
    if (_check_cpuid())
        panic("CPU init failed. No CPUID!");
    
    _get_cpuid(&(cur_cpu.info));

    return 0;
}