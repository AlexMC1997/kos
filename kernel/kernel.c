#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>


void kern_main(void)
{
    asm("movl $0x50, %eax");
    asm("addl $0x50, %eax");
    return;
}