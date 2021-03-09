#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "vgatext.h"
#include "terminal.h"
#include "string.h"

#define cursor_val (t_cursor[1] * VGA_COL_MAX) + t_cursor[0]

bool term_initialized = 0;

static uint16_t t_cursor[2];
static vga_attr term_color;

//clears one row of the terminal; begins at 0
void clear_line(uint16_t row)
{
    uint16_t end = ((row + 1) * VGA_COL_MAX);
    for (uint16_t i = row * VGA_COL_MAX; i < end; i++) {
        vga_putc(term_color, ' ', i);
    }
}
//clears terminal screen
void clear_term(void)
{
    for (uint16_t i = 0; i < VGA_COL_MAX; i++) {
        clear_line(i);
    }
    t_cursor[0] = 0;
    t_cursor[1] = 0;
}

//scrolls terminal by 1 row
void term_scroll(void)
{
    const size_t end = (2*(VGA_COL_MAX * (VGA_ROW_MAX - 1)));
    uint8_t* p = (uint8_t*)(VGA_START + (VGA_COL_MAX * 2));
    memmove((uint8_t*)VGA_START, p, end);

    clear_line(VGA_ROW_MAX - 1);
}

//prints char to terminal
void tputc(char c)
{
    switch (c) {
        case '\n':
        t_cursor[0] = VGA_COL_MAX;
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
        t_cursor[0]++;
    }
    
    //handles new lines and scrolling
    if (t_cursor[0] >= VGA_COL_MAX) {
        t_cursor[0] = 0;
        t_cursor[1]++;
    }
    if (t_cursor[1] >= VGA_ROW_MAX) {
        t_cursor[1] = VGA_ROW_MAX - 1;
        term_scroll();
    }

    vga_mv_cursor(cursor_val);
}

//prints colored char to terminal
void tcputc(vga_color bg, vga_color fg, char c)
{
    vga_attr tmp = term_color;
    term_color = vga_char_attr(bg, fg);
    tputc(c);
    term_color = tmp;
}

//prints len chars to terminal
void twrite(const char* s, size_t len)
{
    for (uint32_t ind = 0; ind < len; ind++)
        tputc(s[ind]);
}

//prints null-terminated string to terminal
void tputs(const char* s)
{
    twrite(s, strlen(s));
}

//prints colored null-terminated string to terminal
void tcputs(vga_color bg, vga_color fg, const char* s)
{
    vga_attr tmp = term_color;
    term_color = vga_char_attr(bg, fg);
    twrite(s, strlen(s));
    term_color = tmp;
}

//prints formatted output to terminal
void tprintf(const char* format, ...)
{
    char c;
    unsigned int tmp, tmp2, tmp3;
    tf_arg arg;
    va_list vl;
    
    char* fmt = (char*)format;
    int alpha = 0x60;
    bool spec = false;
    bool sgn = true;

    va_start(vl, format);

    for (; (c = *fmt); fmt++) {
        if (spec) { //process format specifier
            switch (c) {
                case 'l': //does nothing on IA32
                break;

                case 's':
                arg.s = (const char*)va_arg(vl, int);
                tputs(arg.s);
                goto reset;

                case 'c':
                arg.dhh = va_arg(vl, int);
                tputc(arg.dhh);
                goto reset;

                case 'u':
                sgn = false; /* fall through */
                case 'd':
                arg.d = va_arg(vl, int);

                if (!arg.d) {
                    tputc('0');
                    goto reset;
                }
                
                tmp = 1000000000;

                if ((int)arg.d < 0 && sgn) {
                    arg.d = -arg.d;
                    tputc('-');
                }

                while (arg.d < tmp)
                    tmp = (tmp == 1) ? 0 : tmp / 10;
                while (tmp) {
                    tputc(0x30 + (arg.d / tmp));
                    arg.d %= tmp;
                    tmp = (tmp == 1) ? 0 : tmp / 10;
                }
                goto reset;
                
                case 'X':
                alpha = 0x40; /* fall through */
                case 'x':
                arg.x = va_arg(vl, int);
                tmp = 28;

                tputc('0');
                tputc('x');

                for (; !((arg.x >> tmp) & 0xF); tmp -= 4);
                for (; tmp + 4; tmp-=4) {
                    tmp2 = (arg.x >> tmp) & 0xF;
                    if (tmp2 > 9)
                        tputc(alpha + (tmp2 % 9));
                    else 
                        tputc(0x30 + tmp2);
                }
                goto reset;

                reset:
                default:
                alpha = 0x60;
                sgn = true;
                spec = false;
            }
        } else switch (c) {
            case '%':
            spec = true;
            break;

            default:
            tputc(c);
            break;
        }
    }
    
    va_end(vl);
}

//initializes terminal
int8_t terminal_init(void)
{
    term_color = vga_char_attr(VGA_BLACK, VGA_WHITE);

    clear_term();
    goto notest;
    
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
            tputs("Testing!");
            b = true;
        }
    }

    notest:
    term_initialized = 1;
    tputs("Terminal initialized.\n");

    return 0;
}