#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include "terminal.h"
#include "vga.h"


void kern_main(void)
{
    vga_init();
    terminal_init();
    return;
}