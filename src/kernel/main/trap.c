#include "terminal.h"
#include "io.h"
#include "trap.h"
#include "vmm.h"
#include "mem.h"
#include "panic.h"
#include "string.h"

void page_fault(Trap_Frame* tf)
{
    PF_Code* code = (PF_Code*)&(tf->error_code);
    if (!code->user) {
        uintptr_t va = r_cr2();
        PD_Entry* pd = KERN_PD;
        PT_Entry* pt = (PT_Entry*)(pd_addr_v(pd[va >> 22]) << 12);
        vmm_pg_alloc_4k(pt, va >> 12, 1);
    }
}

//C entry point for all exceptions.
void trap(Trap_Frame tf)
{
    switch (tf.trap_no) {
        case FLT_PF:
        // tprintf("Page fault. Address: %x\n", r_cr2());
        page_fault(&tf);
        break;

        default:
        panic("Unhandled exception.");
    }
}