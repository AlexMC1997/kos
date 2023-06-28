#ifndef _PFA_H
#define _PFA_H

#include "kmmap.h"
#include "gcc.h"

#define PG_SIZE 4096
#define SZ_4_MAX 4096
#define SZ_4_OVF 3072
#define SZ_4_GD 2048
#define SZ_4_UDF 512
#define SZ_16_MAX 1024
#define SZ_16_OVF 768
#define SZ_16_GD 512
#define SZ_16_UDF 128
#define SZ_64_MAX 256
#define SZ_64_OVF 192
#define SZ_64_GD 128
#define SZ_64_UDF 32
#define SZ_256_MAX 64
#define SZ_256_OVF 48
#define SZ_256_GD 32
#define SZ_256_UDF 8
#define SZ_1024_MAX 16
#define SZ_1024_OVF 12
#define SZ_1024_GD 8
#define SZ_1024_UDF 2

typedef uint8_t pg_map_t;
typedef uint32_t pg_num_4k_t;
typedef uint16_t pg_num_16k_t;
typedef uint16_t pg_num_64k_t;
typedef uint8_t pg_num_256k_t;
typedef uint8_t pg_num_1024k_t;

typedef enum {
    PF_4K,
    PF_16K,
    PF_64K,
    PF_256K,
    PF_1024K
} PF_Size;

typedef struct {
    uint32_t refill_4 : 1;
    uint32_t refill_16 : 1;
    uint32_t refill_64 : 1;
    uint32_t refill_256 : 1;
    uint32_t refill_1024 : 1;
    uint32_t dump_4 : 1;
    uint32_t dump_16 : 1;
    uint32_t dump_64 : 1;
    uint32_t dump_256 : 1;
    uint32_t dump_1024 : 1;
} gcc_packed PFA_Flags;

void pfa_init(size_t kmmap_len, Memarea* kmmap);
int pfa_pf_alloc(PF_Size sz, pg_num_4k_t* ptr);
size_t pfa_memstat();

#endif