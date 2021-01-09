#pragma GCC push_options
#pragma GCC optimize("O0")

#include <stdalign.h>
#include <stdint.h>
#include <limits.h>
#include <stddef.h>

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
} __attribute__((__packed__));

struct __GDT_DESCRIPT {
    uint16_t size;
    const struct __GDT_ENTRY* offset;
} __attribute__((__packed__));

const struct __GDT_ENTRY GDT[] = {
    { //NULL segment
        .limit_0_15 =   0,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    0,
        .DC =    0,
        .Ex =    0,
        .S =     0,
        .Privl = 0,
        .Pr =    0,
        .limit_16_19 = 0,
        .none = 0,
        .Sz = 0,
        .Gr = 0,
        .base_24_31 = 0
    },
    { //Kernel Code Selector
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
    { //Kernel Data Selector
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
    },
    { //User Code Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    1,
        .S =     1,
        .Privl = 3,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //User Data Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    0,
        .RW =    1,
        .DC =    0,
        .Ex =    0,
        .S =     1,
        .Privl = 3,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 1,
        .Gr = 1,
        .base_24_31 = 0
    },
    { //Task State Selector
        .limit_0_15 =   UINT16_MAX,
        .base_0_15 = 0,
        .base_16_23 = 0,
        .Ac =    1, //TSS not LDT
        .RW =    0, //Not busy
        .DC =    0,
        .Ex =    1, //1 is 32 bit
        .S =     0, 
        .Privl = 0,
        .Pr =    1,
        .limit_16_19 = 0xF,
        .none = 0,
        .Sz = 0,
        .Gr = 1,
        .base_24_31 = 0
    }
};
const struct __GDT_DESCRIPT GDT_DESCRIPT = { (6*sizeof(struct __GDT_ENTRY))-1, GDT };
const struct __GDT_DESCRIPT* GDT_DESCRIPT_PTR = &GDT_DESCRIPT;

#pragma GCC pop_options