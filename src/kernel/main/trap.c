#include "terminal.h"
#include "io.h"
#include "trap.h"
#include "vmm.h"
#include "mem.h"
#include "panic.h"

void page_fault(Trap_Frame* tf)
{
    PF_Code* code = &(tf->error_code);
    if (!code->user) {
        uintptr_t va = r_cr2();
        PD_Entry* pd = KERN_PD;
        int tmp1 = pd[va >> 22].addr_4_19 << 4;
        int tmp2 = (pd[va >> 22].addr_0_3);
        PT_Entry* pt = ((pd[va >> 22].addr_4_19 << 4) | (pd[va >> 22].addr_0_3)) << 12;
        vmm_pg_alloc_4k(pt, va >> 12, 4);
    }
}

//C entry point for all exceptions.
void trap(Trap_Frame* tf)
{
    switch (tf->trap_no) {
        case FLT_PF:
        page_fault(tf);
        return;

        default:
        panic("Unhandled exception.");
    }
}