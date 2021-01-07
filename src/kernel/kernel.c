#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include "terminal.h"
#include "vga.h"
#include "string.h"
#include "panic.h"
#include "assert.h"


void kern_main(void)
{
    vga_init();
    terminal_init();

    char t[5] = {1, 2, 3, 4, 5};
    char s[5] = {2, 3, 4, 5, 6};

    char result = memcmp(t, s, 5);
    char* ptr3 = memchr(t, 0x3, 4);

    tputc(0x31 + result);
    tputc(0x30 + *ptr3);

    assert(t == s);
    return;
}