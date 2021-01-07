#include <stdalign.h>
#include <stdint.h>
#include <limits.h>

struct __GDT_ENTRY {
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t base_16_23;
    uint8_t Ac : 1;
    uint8_t RW : 1;
    uint8_t DC : 1;
    uint8_t Ex : 1;
    uint8_t S : 1;
    uint8_t Privl : 2;
    uint8_t Pr : 1;
    uint8_t limit_16_19 : 4;
    uint8_t none : 2;
    uint8_t Sz : 1;
    uint8_t Gr : 1;
    uint8_t base_24_31;
};

struct __GDT_DESCRIPT {
    uint16_t size;
    const struct __GDT_ENTRY* offset;
};

const struct __GDT_ENTRY GDT[] = {
    { //Code Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    1,
        .S =     1,
        .Privl = 0,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //Data Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    0,
        .S =     1,
        .Privl = 0,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    }
};
const struct __GDT_DESCRIPT GDT_DESCRIPT = { 1, GDT };
const struct __GDT_DESCRIPT* GDT_DESCRIPT_PTR = &GDT_DESCRIPT;

