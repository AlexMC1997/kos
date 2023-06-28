//Virtual Memory Manager; manages the paging system
#include "vmm.h"
#include "panic.h"
#include "string.h"
#include "assert.h"
#include "terminal.h"

//Allocates a page directory and writes the physical address
//of the containing page to ph_ptr.
//Expects an identity mapping already present;
//undefined behavior otherwise.
int vmm_pd_alloc(PD_Entry** ph_ptr)
{
    pg_num_4k_t tmp;
    if (pfa_pf_alloc(PF_4K, &tmp))
        return -1;
    
    //Nulls page directory
    *ph_ptr = (PD_Entry*)(tmp << 12);
    memset(*ph_ptr, 0, PG_SIZE);

    return 0;
}

//Allocates a page table to a page directory entry specified in ph_ptr.
//Optionally returns page table address in pt_ptr.
//Expects an identity mapping already present;
//undefined behavior otherwise.
int vmm_pt_alloc(PD_Entry* ph_ptr, PT_Entry* pt_ptr[])
{
    pg_num_4k_t tmp;
    if (pfa_pf_alloc(PF_4K, &tmp))
        return -1;
    
    //CHECK IF VALID, FETCH FROM SWAP IF SO
    //SHOULD PASS IN VALID FLAG

    //Nulls page table
    memset((uint8_t*)(tmp << 12), 0, PG_SIZE);

    ph_ptr->addr_0_3 = (tmp & 0xF);
    ph_ptr->addr_4_19 = (tmp >> 4);

    if (pt_ptr)
        *pt_ptr = (PT_Entry*)(tmp << 4);

    return 0;
}

//Allocates 4k page frames for a range of pages from a page table.
//May overlap already present regions.
//The base address is simply rounded mod 1k.
//It may be expressed as a full address or an offset.
int vmm_pg_alloc_4k(PT_Entry pt[], pg_num_4k_t base, size_t len)
{
    pg_num_4k_t tmp;
    size_t ind;

    base %= PG_SIZE / 4;

    assert((base + len) <= (PG_SIZE / 4));
    if ((base + len) > (PG_SIZE / 4))
        panic("Invalid page range on alloc.");
    
    for (ind = 0; ind < len; ind++) {
        if (pt[base + ind].present)
            continue;
        if (pfa_pf_alloc(PF_4K, &tmp))
            goto cleanup;
        
        //MUST ALSO CHECK IF VALID, FETCH FROM SWAP IF SO
        
        pt[base + ind].addr_0_3 = (uint8_t)(tmp & 0xF);
        pt[base + ind].addr_4_19 = (uint16_t)(tmp >> 4);
        pt[base + ind].present = 1;
    }

    return 0;

    cleanup:
    return -1;
}

//Allocates specified region within a page table (4 MiB space).
//Does not allocate physical memory for relevant pages.
int vmm_pt_vm_alloc(pg_num_4k_t len, pg_num_4k_t addr, Alloc_Flags flags, PT_Entry pt_ptr[])
{
    pg_num_4k_t ind, end;
    ind = addr;
    end = addr + len;

    if (end > PG_SIZE / 4)
        panic("Page table address overflow.");

    for (; ind < end; ind++) {
        if (pt_ptr[ind].valid) {
            if (flags.user && !pt_ptr[addr].user)
                pt_ptr[ind].user = flags.user;
            if (flags.write && !pt_ptr[addr].write)
                pt_ptr[ind].write = flags.write;
        } else {
            pt_ptr[ind].valid = 1;
            pt_ptr[ind].user = flags.user;
            pt_ptr[ind].write = flags.write;
        }            
    }

    return 0;

    cleanup:
    return -1;
}

//Allocates region specified by addr and len in the 
//virtual memory space indicated by pd_ptr.
//Physical memory is allocated for relevant page tables,
//but not for the pages within.
int vmm_pd_vm_alloc(pg_num_4k_t len, pg_num_4k_t addr, Alloc_Flags flags, PD_Entry pd_ptr[])
{
    PT_Entry* cur_pt;
    pg_num_4k_t cur_pg, cur_len;
    size_t pd_ind, pd_len, pd_end;
    
    cur_pg = addr % (PG_SIZE / 4);
    cur_len = len;
    pd_ind = addr >> 10;
    pd_len = len & 0x3FF ? len + 0x400 : len; //round up
    pd_len >>= 10;
    
    pd_end = pd_ind + pd_len;

    if (pd_end > PG_SIZE / 4)
        panic("Virtual address space overflow.");

    for (; pd_ind < pd_end; pd_ind++) {
        //Checks if page table is already present
        if (!pd_ptr[pd_ind].present) {
            if (vmm_pt_alloc(pd_ptr + pd_ind, &cur_pt)) 
                goto cleanup;
        } else 
            cur_pt = (PT_Entry*)(pd_addr_v(pd_ptr[pd_ind]) << 12); 
        
        //Checks if page table is valid first, to
        //avoid overwriting a higher table privilege
        //than specified in new region.
        //Otherwise it creates the table flags.
        if (pd_ptr[pd_ind].valid) {
            if (flags.user && !pd_ptr[pd_ind].user)
                pd_ptr[pd_ind].user = 1;
            if (flags.write && !pd_ptr[pd_ind].write)
                pd_ptr[pd_ind].write = 1;
        } else {
            pd_ptr[pd_ind].present = 1;
            pd_ptr[pd_ind].user = flags.user;
            pd_ptr[pd_ind].write = flags.write;
            pd_ptr[pd_ind].valid = 1;
        }
        pg_num_4k_t run_len = (PG_SIZE / 4) - cur_pg;
        vmm_pt_vm_alloc(cur_len > run_len ? run_len : cur_len, cur_pg, flags, cur_pt);

        cur_len -= run_len;
        cur_pg = 0;
    }

    return 0;

    cleanup:
    return -1;
}

//Allocates a virtual memory space, returning a physical pointer 
//to its ruling page directory in ph_ptr.
//The space is specified with a VMS table of length len
//passed through vms.
//Expects an identity mapping already present;
//undefined behavior otherwise.
int vmm_vms_alloc(size_t len, VMS_Entry vms[], PD_Entry* ph_ptr[])
{
    if (vmm_pd_alloc(ph_ptr))
        return -1;

    //Runs through VMS table allocating page tables and pages as appropriate
    for (size_t i = 0; i < len; i++) {
        if(vmm_pd_vm_alloc(vms[i].sz, vms[i].vm_addr, vms[i].flags, *ph_ptr))
            return -1;
    }
    return 0;
}