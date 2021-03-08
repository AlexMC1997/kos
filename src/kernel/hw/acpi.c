#include "string.h"
#include "mem.h"
#include "terminal.h"
#include "io.h"
#include "acpi.h"
#include "panic.h"

struct rsdp* RSDP;

void acpi_init()
{
    get_rsdp(&RSDP);
}

//Finds RSDP and assigns to ptr
void get_rsdp(rsdp** ptr)
{
    char* pt = (char*)MEM_EBDA_START;

    for (;pt < (char*)(MEM_EBDA_START + 0x400); pt+=0x10)
        if (!memcmp(pt, "RSD PTR ", 8))
            goto rsdp_found;
    
    for (pt = (char*)0xE0000; pt < (char*)MEM_MB_BIOS_END; pt+=0x10)
        if (!memcmp(pt, "RSD PTR ", 8))
            goto rsdp_found;
    
    panic("RSDP could not be found.");
    
    rsdp_found:
    *ptr = (rsdp*)pt;

    uint32_t check = 0;
    for (uint8_t i = 0; i < sizeof(rsdp); i++)
        check += *(pt + i);
    
    if ((uint8_t)check)
        panic("RSDP checksum failed.");
    if ((*ptr)->revision)
        panic("RSDP Revision 2+ found.");
}