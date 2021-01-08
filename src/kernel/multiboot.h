#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <stdint.h>
#include <stddef.h>
#include "elf.h"

#define MULTIBOOT_MAGIC 0x2BADB002

typedef struct __bootmod {
    uint8_t* mod_start;
    uint8_t* mod_end;
    char* string;
    uint32_t reserved;
} bootmod;

typedef struct __boot_device {
    uint8_t part3;
    uint8_t part2;
    uint8_t part1;
    uint8_t drive;
} __attribute__((__packed__)) boot_device;

typedef struct __multiboot_mmap {
    size_t size; //ignore
    uint8_t* base_addr_low;
    uint8_t* base_addr_high;
    size_t length_low;
    size_t length_high;
    uint32_t type;
} __attribute__((__packed__)) multiboot_mmap;

typedef struct __multiboot_info {
    uint32_t flags;
    size_t mem_lower;
    size_t mem_upper;
    boot_device boot_device;
    char* cmdline;
    uint32_t mods_count;
    bootmod* mods_addr;
    uint32_t num;
    size_t size;
    elf* addr;
    uint8_t* shndx;
    size_t mmap_length;
    multiboot_mmap* mmap_addr;
    
} __attribute__((__packed__)) multiboot_info;

#endif