//Page Frame Allocator, backend of the memory system
//Manages physical memory
#include <stddef.h>
#include <stdint.h>
#include "pfa.h"
#include "kmmap.h"
#include "mem.h"
#include "panic.h"
#include "gcc.h"
#include "assert.h"
#include "terminal.h"

//Notes: page daemon will do bookkeeping 

static PFA_Flags flags;

static pg_num_4k_t stack_pg_4k[SZ_4_MAX];
static pg_num_16k_t stack_pg_16k[SZ_16_MAX];
static pg_num_64k_t stack_pg_64k[SZ_64_MAX];
static pg_num_256k_t stack_pg_256k[SZ_256_MAX];
static pg_num_1024k_t stack_pg_1024k[SZ_1024_MAX];

static size_t stack_4k_ptr;
static size_t stack_16k_ptr;
static size_t stack_64k_ptr;
static size_t stack_256k_ptr;
static size_t stack_1024k_ptr;

static size_t last_4k;
static uint8_t last_4k_sub;

static size_t last_16k;
static uint8_t last_16k_sub;

static size_t last_64k;

static size_t last_256k;

static size_t last_1024k;

static pg_map_t* pg_reservoir;
static size_t reservoir_size;

//Reserves a region in the reservoir
void pfa_mask_region(pg_num_4k_t page_start, pg_num_4k_t page_end)
{
    size_t ind_st, ind_end, sub_ind_st, sub_ind_end;
    pg_map_t mask;

    ind_st = page_start / 8;
    ind_end = page_end / 8;

    if (ind_end > reservoir_size || ind_st > reservoir_size)
        panic("Page number out of bounds.");
    if (page_start > page_end)
        panic("Bad page range.");
    
    sub_ind_st = page_start % 8;
    sub_ind_end = page_end % 8;

    if (ind_st == ind_end) {    
        mask = ~(UINT32_MAX << sub_ind_st) | (UINT32_MAX << sub_ind_end);
        pg_reservoir[ind_st] &= mask;
    } else {
        mask = ~(UINT32_MAX << sub_ind_st);
        pg_reservoir[ind_st++] &= mask;
        for (; ind_st < ind_end; pg_reservoir[ind_st++] = 0);
        mask = (UINT32_MAX << sub_ind_end);
        pg_reservoir[ind_end] &= mask;
    }
}

//Updates last_4k and last_4k_sub, 
//pointing it to the next free 4k page in the reservoir.
static int find_4k()
{
    if (pg_reservoir[last_4k] & (1 << last_4k_sub))
        return 0;
    
    for (size_t init = last_4k; !pg_reservoir[last_4k];) {
        last_4k++;
        if (last_4k >= reservoir_size)
            last_4k = 0;
        else if (last_4k == init)
            return -1;
    }

    for (last_4k_sub = 0; !(pg_reservoir[last_4k] & (1 << last_4k_sub)); last_4k_sub++);
    
    return 0;
}

//Fetches a free 4k page from the reservoir
//Should be run on init and by the daemon
static int fetch_pg_4k(pg_num_4k_t* ptr)
{
    //Must call this first, in case page was swept by another stack
    if (find_4k())
        return -1;

    assert(pg_reservoir[last_4k] & (1 << last_4k_sub));
    
    *ptr = ((pg_num_4k_t)last_4k << 3) | last_4k_sub;
    pg_reservoir[last_4k] &= ~(1 << last_4k_sub);

    last_4k_sub++;

    return 0;
}

//Updates last_16k and last_16k_sub, 
//pointing it to the next free 16k region in the reservoir.
static int find_16k()
{
    pg_map_t tmp;

    if (last_16k_sub <= 4 && (pg_reservoir[last_16k] & (0xF << last_16k_sub)) == (0xF << last_16k_sub))
        return 0;

    for (
        size_t init = last_16k; 
        !((((tmp = pg_reservoir[last_16k]) & 0xF) == 0xF) || ((tmp & 0xF0) == 0xF0)); 
    ) {
        last_16k++;
        if (last_16k >= reservoir_size)
            last_16k = 0;
        else if (last_16k == init)
            return -1;
    }

    last_16k_sub = (tmp & 0xF) == 0xF ? 0 : 4;

    return 0;
}

//Fetches 4 free contiguous, 16k aligned 4k pages from the reservoir
//Should be run on init and by the daemon
static int fetch_pg_16k(pg_num_16k_t* ptr)
{
    if (find_16k())
        return -1;

    assert((pg_reservoir[last_16k] & (0xF << last_16k_sub)) == (0xF << last_16k_sub));
    
    *ptr = (pg_num_16k_t)((last_16k << 1) | (last_16k_sub >> 2));
    pg_reservoir[last_16k] &= ~(0xF << last_16k_sub);
    last_16k_sub += 4;
    
    return 0;
}

//Allocates a page frame of PF_Size. 
//Writes the 4K page number to ptr.
int pfa_pf_alloc(PF_Size sz, pg_num_4k_t* ptr)
{
    switch (sz) {
        case PF_4K:
        //If somehow the stack is empty, pull from reservoir
        if (!stack_4k_ptr)
            fetch_pg_4k(ptr);
        else
            *ptr = stack_pg_4k[--stack_4k_ptr];

        if (stack_4k_ptr < SZ_4_UDF)
            flags.refill_4 = 1;
        break;

        case PF_16K:
        if (!stack_16k_ptr)
            fetch_pg_16k((pg_num_16k_t*)ptr);
        else
            *ptr = stack_pg_16k[--stack_16k_ptr];
        
        if (stack_16k_ptr < SZ_16_UDF)
            flags.refill_16 = 1;

        *ptr <<= 2; //adjust to 4k num
        break;

        default:
        panic("This page size is not implemented yet!");
    }
    return 0;
}

//Initializes the page reservoir, a bitmap of physical memory
//Each bit represents a page, a 4096 byte region of memory
//1 - free
//0 - used
static void pg_reservoir_init(size_t kmmap_len, Memarea* kmmap)
{
    size_t cur, cursize, i;
    size_t phys_mem = 0;

    for (i = 0; i < kmmap_len; i++) {
        if (kmmap[i].type != MEM_FREE)
            continue;
        cur = (size_t)kmmap[i].addr + kmmap[i].size;
        phys_mem = phys_mem < cur ? cur : phys_mem;
    }

    reservoir_size = phys_mem / (8 * PG_SIZE);

    //Allocates memory to store the map. Kind of wonky, but works
    //Really, this should limit allocation to the kernel's
    //dedicated memory region, and perhaps use a pointer to
    //the end of the binary to demark it, but I'm being lazy
    for (i = 0; i < kmmap_len; i++) {
        if (kmmap[i].type == MEM_FREE) {
            cur = (size_t)(kmmap[i].addr);
            cursize = kmmap[i].size;
            if (cursize < reservoir_size)
                continue;
            if ((cur > phys(KERN_TOP)) || (cur + cursize) < phys(KERN_BASE)) {
                if (!cur && (cursize - PG_SIZE) < reservoir_size)
                    continue;
                else if (!cur)
                    cur = PG_SIZE;
                pg_reservoir = (pg_map_t*)cur;
                break;
            }
        }
    }

    //Build the reservoir
    for (i = 0; i < reservoir_size + 1; pg_reservoir[i++] = -1);

    //Allocate the first 5 Mb for the kernel and LMA
    //The region will be handled by an internal manager
    //Most of this region will be swappable later
    pfa_mask_region(0, phys(KERN_TOP) / PG_SIZE);

    //Allocate all regions which are not free
    //These regions will likely not be swappable or
    //usable in any way; they are "dead" memory
    for (i = 0; i < kmmap_len; i++) {
        if (kmmap[i].type != MEM_FREE) {
            cur = (size_t)kmmap[i].addr;
            cursize = cur + kmmap[i].size;
            if (cur > phys_mem || cursize > phys_mem) 
                continue;
            cur = cur % PG_SIZE ? (cur / PG_SIZE) - 1 : (cur / PG_SIZE);
            cursize = cursize % PG_SIZE ? (cursize / PG_SIZE) + 1 : (cursize / PG_SIZE);
            pfa_mask_region(cur, cursize);
        }
    }
}

static void stack_4k_init()
{
    last_4k = 0;
    last_4k_sub = 0;

    pg_num_4k_t dummy;
    
    if (fetch_pg_4k(&dummy))
        panic("No 4k page found during init!");

    for (stack_4k_ptr = 0; stack_4k_ptr < SZ_4_GD; stack_4k_ptr++) {
        if (fetch_pg_4k((stack_pg_4k + stack_4k_ptr))) {
            panic("Ran out of 4k pages in stack init.");
        }
    }
}

static void stack_16k_init()
{
    last_16k = 0;
    last_16k_sub = 0;

    pg_num_16k_t dummy;
    
    if (fetch_pg_16k(&dummy))
        panic("No 16k region found during init!");

    for (stack_16k_ptr = 0; stack_16k_ptr < SZ_16_GD; stack_16k_ptr++) {
        if (fetch_pg_16k((stack_pg_16k + stack_16k_ptr))) {
            panic("Ran out of 16k regions in stack init.");
        }
    }
}

//Initializes the Page Frame Allocator. This system is
//required by the Virtual Memory Manager to function.
void pfa_init(size_t kmmap_len, Memarea* kmmap)
{
    pg_reservoir_init(kmmap_len, kmmap);
    stack_4k_init();
    stack_16k_init();
}