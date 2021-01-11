#include <stdint.h>

typedef struct {
    uint16_t offset_0_15;
    uint16_t selector;
    uint8_t reserved;
    uint8_t type : 3;
    uint8_t D : 1;
    uint8_t S : 1;
    uint8_t DPL : 2;
    uint8_t P : 1;
    uint16_t offset_16_31;
} __attribute__((__packed__)) idt_entry;

typedef struct {
    uint16_t length;
    uint32_t offset;
} __attribute__((__packed__)) idt_desc;

void idt_init();