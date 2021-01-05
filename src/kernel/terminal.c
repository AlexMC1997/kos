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

//scrolls terminal by 1 row
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

//prints char to terminal
int8_t tputc(char c)
{
    switch (c) {
        case '\n':
        tcursor[0] = VGA_COL_MAX;
        break;

        case '\t':
        tputc(' ');
        tputc(' ');
        tputc(' ');
        tputc(' ');
        break;

        default:
        if (c < 0x20)
            break;
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

//prints len chars to terminal
int8_t twrite(char* s, size_t len)
{
    for (uint32_t ind = 0; ind < len; ind++)
        tputc(s[ind]);
    return 0;
}

//prints null-terminated string to terminal
int8_t tputs(char* s)
{
    return twrite(s, strlen(s));
}

//initializes terminal
int8_t terminal_init(void)
{
    term_color = vga_char_attr(VGA_BLACK, VGA_WHITE);

    clear_term();
    
    //TESTING
    vga_color clr = VGA_WHITE;
    bool b = false;
    for (;;) {
        term_color = vga_char_attr(VGA_BLACK, clr);
        if (clr == 15)
            clr = 0;
        clr++;
        if (b) {
            tputc('\n');
            b = false;
        } else {
            tputs("Terminal\tinitialized.");
            b = true;
        }
    }


    return 0;
}