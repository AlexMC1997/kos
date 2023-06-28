#include "console.h"
#include "terminal.h"
#include "pfa.h"
#include "string.h"
#include "kmm.h"

static const vga_color CONSOLE_MSG_COLOR = VGA_GREY;

void console_show_prompt()
{
    tcputs(VGA_BLACK, VGA_GREEN, "kos");
    tcputc(VGA_BLACK, CONSOLE_MSG_COLOR, '$');
    tcputs(VGA_BLACK, VGA_CYAN, "control");
    tcputs(VGA_BLACK, CONSOLE_MSG_COLOR, "> ");
}

void console_getcmd(char* buf)
{
    size_t end = 0;
    console_show_prompt();
    end = tgets(CMD_SIZE, buf);
    buf[end - 1] = '\0';
}

void console_main()
{
    tcputs(VGA_BLACK, CONSOLE_MSG_COLOR, "\nKOS control console started.\nWelcome to KOS.\n\n");
    char cmd[CMD_SIZE + 1];
    cmd[CMD_SIZE] = '\0';
    while (1) {
        console_getcmd(cmd);
        if (!strcmp(cmd, "memstat")) {
            size_t free_mem = pfa_memstat();
            tprintf("Bytes free: %u\n", free_mem);
            for (size_t i = 0; i < 15; i++) {
                uint8_t* tmp = kmalloc(MEM_64K);
                for (size_t j = 0; j < 0xFFFF; j+=4096) {
                    tmp[j] = 100;
                }
            }
        } else if (!strcmp(cmd, "list")) {
            list_main();
        }
    }
}