#ifndef _ACPI_H
#define _ACPI_H

typedef struct {

} rsdt;

typedef struct {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    rsdt* rsdt_ptr;
} rsdp;

void acpi_init();
void get_rsdp(rsdp** ptr);

#endif