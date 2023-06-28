#include "terminal.h"
#include "io.h"
#include "trap.h"
#include "vmm.h"
#include "mem.h"
#include "panic.h"
#include "string.h"
#include "gdt.h"
#include "pic.h"
#include "ps2.h"
#include "ps2_kb.h"

void page_fault(Trap_Frame* tf)
{
    PF_Code* code = (PF_Code*)&(tf->error_code);
    if (!code->user) {
        uintptr_t va = r_cr2();
        PD_Entry* pd = KERN_PD;
        uintptr_t tmp = va >> 22;
        PT_Entry* pt = (PT_Entry*)(pd_addr_v(pd[tmp]) << 12);
        vmm_pg_alloc_4k(pt, va >> 12, 1);
    }
}

void keyboard_int()
{
    PS2_Key_Info info;
    ps2_kb_get_key(&info);

    //temporary - sends key directly to terminal
    if (info.key != -1)
        ttake_key(info);

    pic_eoi(1);
}

//C entry point for all exceptions.
int trap(Trap_Frame tf)
{
    switch (tf.trap_no) {
        case FLT_PF:
        page_fault(&tf);
        return -1;
        break;
        
        case 0x21:
        keyboard_int();
        return 0;
        break;

        case ABRT_DOUBLE_FAULT:
        case FLT_INV_TSS:
        case FLT_NO_SEG:
        case FLT_SSF:
        case FLT_GPF:
        case FLT_ALGN_CHK:
        case FLT_SEC_EX:
        return -1;
        break;

        default:
        pic_eoi(15);
        tprintf("Unhandled exception. Exception #: %u\n", tf.trap_no);
    }
}