#ifndef _VMM_H
#define _VMM_H

#include "pfa.h"

typedef struct {
    uint8_t write : 1;
    uint8_t user : 1;
    uint8_t wr_thru : 1;
    uint8_t dis_cache : 1;
} Alloc_Flags;

//x86 Page Table entry.
typedef struct {
    uint8_t present : 1;
    uint8_t write : 1;
    uint8_t user : 1;
    uint8_t wr_thru : 1;
    uint8_t dis_cache : 1;
    uint8_t accessed : 1;
    uint8_t dirty : 1;
    uint8_t valid : 1;
    uint8_t global : 1;
    uint8_t map : 1;
    uint8_t last : 1;
    uint8_t avail : 1;
    uint8_t addr_0_3 : 4;
    uint16_t addr_4_19;
} gcc_packed PT_Entry;

//x86 Page Directory entry.
typedef struct {
    uint8_t present : 1;
    uint8_t write : 1;
    uint8_t user : 1;
    uint8_t wr_thru : 1;
    uint8_t dis_cache : 1;
    uint8_t accessed : 1;
    uint8_t valid : 1;
    uint8_t sz : 1;
    uint8_t avail : 4;
    uint8_t addr_0_3 : 4;
    uint16_t addr_4_19;
} gcc_packed PD_Entry;

//Describes a segment from vm_addr to sz of a virtual memory space.
typedef struct {
    //Virtual starting page number.
    pg_num_4k_t vm_addr;
    //Number of pages to allocate.
    pg_num_4k_t sz;
    Alloc_Flags flags;
} VMS_Entry;

int vmm_vms_alloc(size_t len, VMS_Entry* vms, PD_Entry** ph_ptr);
int vmm_pt_alloc(PD_Entry* ph_ptr, PT_Entry** pt_ptr);
int vmm_pd_alloc(PD_Entry** ph_ptr);
int vmm_pd_vm_alloc(pg_num_4k_t len, pg_num_4k_t addr, Alloc_Flags flags, PD_Entry pd_ptr[]);
int vmm_pg_alloc_4k(PT_Entry pt[], pg_num_4k_t base, size_t len);

#endif