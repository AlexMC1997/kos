#ifndef _ACPI_H
#define _ACPI_H

struct rsdt {

};

struct rsdp {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    struct rsdt* rsdt_ptr;
};

void acpi_init();
void get_rsdp(struct rsdp** ptr);

#endif