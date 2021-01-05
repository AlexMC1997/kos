#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "vga.h"
#include "terminal.h"
#include "string.h"

#define cursor_val (tcursor[1] * VGA_COL_MAX) + tcursor[0]

uint16_t tcursor[2];
uint16_t vgamax;
vga_attr term_color;

//clears screen
void clear_term()
{
    for (uint16_t i = 0; i < (VGA_COL_MAX * VGA_ROW_MAX)+1; i++) {
        vga_putc(term_color, ' ', i);
    }
    tcursor[0] = 0;
    tcursor[1] = 0;
}

void term_scroll()
{
    uint16_t p = (uint16_t)VGA_COL_MAX;
    vga_char c;
    for (; p < (VGA_COL_MAX * VGA_ROW_MAX); p++) {
        c = vga_getc(p);
        vga_putc((vga_attr)(c >> 8), (char)c, p - VGA_COL_MAX);
    }
    p = VGA_COL_MAX * (VGA_ROW_MAX - 1);
    for (; p < (VGA_COL_MAX * VGA_ROW_MAX); p++)
        vga_putc(term_color, ' ', p);
}

int8_t tputc(char c)
{
    switch (c) {
        case '\n':
        tcursor[0] = VGA_COL_MAX;
        break;

        default:
        vga_putc(term_color, c, cursor_val);
        tcursor[0]++;
    }
    
    //handles new lines and scrolling
    if (tcursor[0] >= VGA_COL_MAX) {
        tcursor[0] = 0;
        tcursor[1]++;
    }
    if (tcursor[1] >= VGA_ROW_MAX) {
        tcursor[1] = VGA_ROW_MAX - 1;
        term_scroll();
    }

    vga_mv_cursor(cursor_val);
    return 0;
}

int8_t twrite(char* s, size_t len)
{
    for (uint32_t ind = 0; ind < len; ind++)
        tputc(s[ind]);
    return 0;
}

int8_t tputs(char* s)
{
    return twrite(s, strlen(s));
}

int8_t terminal_init(void)
{
    vgamax = (uint16_t)((VGA_END - VGA_START) / 2);
    term_color = vga_char_attr(VGA_BLACK, VGA_WHITE);

    clear_term();
    
    //TESTING
    vga_color clr = VGA_WHITE;
    bool b = false;
    for (int i = 1; i; i++) {
        term_color = vga_char_attr(VGA_BLACK, clr);
        if (clr == 15)
            clr = 0;
        clr++;
        if (b) {
            tputc('\n');
            b = false;
        } else {
            tputs("Terminal initialized.");
            b = true;
        }
    }


    return 0;
}