#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include "terminal.h"
#include "vgatext.h"
#include "string.h"
#include "panic.h"
#include "assert.h"
#include "multiboot.h"
#include "kmmap.h"

//Kernel C entry; passed GRUB info for parsing
void kern_main(uint32_t magic, multiboot_info* mbi)
{
    assert(magic == MULTIBOOT_MAGIC);

    kmmap_init(mbi->mmap_addr, mbi->mmap_length);

    vga_text_init();
    terminal_init();

    char t[5] = {1, 2, 3, 4, 5};
    char s[5] = {2, 3, 4, 5, 6};

    char result = memcmp(t, s, 5);
    char* ptr3 = memchr(t, 0x3, 4);

    tputc(0x31 + result);
    tputc(0x30 + *ptr3);

    tputc('\n');
    tprintf("testing ... ! : %s ... %c ... %s \nSo you think you can beat me, %x?", "it worked!", '\n', "yep, totally", 291);

    tputc('\n');
    tputc('\n');
    tcputs(VGA_DGREY, VGA_TEAL, "Yo we doing colors now!\n");

    tputs("test\n");
    
    tcputs(VGA_GREEN, VGA_MAGENTA, "Yo we doing colors now!\n");
    tcputs(VGA_BLUE, VGA_ORANGE, "Yo we doing colors now!\n");



    assert(t == s);
    return;
}