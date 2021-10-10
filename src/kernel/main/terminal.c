#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "vgatext.h"
#include "terminal.h"
#include "queue.h"
#include "kmm.h"
#include "io.h"

#define cursor_val (t_cursor.row * VGA_COL_MAX) + t_cursor.col

static Term_Cursor t_cursor;
static uint16_t vgamax;
static vga_attr term_color;

static struct Term_Scanner scanner;
static Queue* key_queue;

extern bool term_initialized = false;

//clears one row of the terminal; begins at 0
void clear_line(uint16_t row)
{
    uint16_t end = ((row + 1) * VGA_COL_MAX);
    for (uint16_t i = row * VGA_COL_MAX; i < end; i++) {
        vga_putc(vga_char_attr(VGA_BLACK, VGA_WHITE), ' ', i);
    }
}
//clears terminal screen
void clear_term(void)
{
    for (uint16_t i = 0; i < VGA_COL_MAX; i++) {
        clear_line(i);
    }
    t_cursor.col = 0;
    t_cursor.row = 0;
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
        t_cursor.col = VGA_COL_MAX;
        break;

        case '\t':
        tputc(' ');
        tputc(' ');
        tputc(' ');
        tputc(' ');
        break;

        case '\b':
        t_cursor.col--;
        if (t_cursor.col + 1)
            vga_putc(term_color, ' ', cursor_val);
        break;

        default:
        if (c < 0x20)
            break;
        vga_putc(term_color, c, cursor_val);
        t_cursor.col++;
    }
    
    //handles new lines and scrolling
    if (t_cursor.col >= VGA_COL_MAX) {
        t_cursor.col = 0;
        t_cursor.row++;
    } else if (t_cursor.col < 0) {
        t_cursor.col = 0;
        if (t_cursor.row)
            t_cursor.row--;
    }
    if (t_cursor.row >= VGA_ROW_MAX) {
        t_cursor.row = VGA_ROW_MAX - 1;
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

                for (; !((arg.x >> tmp) & 0xF) && tmp; tmp -= 4);
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

//scans keys from keyboard into the terminal and into a buffer
void tscan_line()
{
    vga_enable_cursor();
    volatile bool scanning;
    scanner.scanning = true;
    PS2_Key_Info* ptr;
    while (scanning = scanner.scanning) {
        cli();
        if (queue_len(key_queue)) {
            ptr = queue_dequeue(key_queue);
            tscan_key(*ptr, PS2_K_ENTER);
            kfree(ptr, MEM_256);
        }
        sti();
    }

    while (ptr = queue_dequeue(key_queue))
        kfree(ptr, MEM_256);
    vga_disable_cursor();
}

//takes a key from keyboard into the key queue
void ttake_key(PS2_Key_Info key_info) {
    if (scanner.scanning) {
        PS2_Key_Info* key = kmalloc(MEM_256);
        *key = key_info;
        queue_enqueue(key_queue, key);
    }
}

//parses a key into characters for input into terminal and buffer
void tscan_key(PS2_Key_Info key_info, e_ps2_keys terminator)
{
    char in;
    if (!key_info.released) {
        if (key_info.key == terminator)
            scanner.scanning = false;
        if (key_info.ascii) {
            in = key_info.ascii;
            tputc(in);
        } else switch (key_info.key) {
            case PS2_K_ENTER:
            case PS2_K_NUM_ENTER:
            in = '\n';
            tputc(in);
            break;

            case PS2_K_TAB:
            in = '\t';
            tputc(in);
            break;

            case PS2_K_BACK:
            if (scanner.buf_ind) {
                in = '\b';
                tputc(in);
                scanner.buf_ind--;
                if (scanner.buffer[scanner.buf_ind] == '\t') {
                    tputc(in);
                    tputc(in);
                    tputc(in);
                }
                scanner.buffer[scanner.buf_ind] = ' ';
            }
            default:
            return;
        }

        if (scanner.buf_ind < TERM_SCANNER_BUF_SZ) {
            scanner.buffer[scanner.buf_ind] = in;
            scanner.buf_ind++;
        }
    } else {
        return;
    }
}

void clear_scanner()
{
    scanner.buf_ind = 0;
    scanner.scanning = false;
    scanner.locks = 0;
    scanner.mods = 0;
    memset(scanner.buffer, '\0', 512);
}

//Gets a character string of up to max size from the user.
//Terminated by new line character
size_t tgets(size_t max, char* restrict buf)
{
    tscan_line();
    size_t n = max > scanner.buf_ind ? scanner.buf_ind : max;
    memcpy(buf, scanner.buffer, n);
    clear_scanner();
    return n;
}

//Gets a character from the user.
char tgetc()
{
    tscan_line();
    char c = scanner.buffer[0];
    clear_scanner();
    return c;
}

//initializes terminal
int8_t terminal_init()
{
    term_color = vga_char_attr(VGA_BLACK, VGA_WHITE);

    scanner.buf_ind = 0;
    scanner.scanning = false;
    memset(scanner.buffer, '\0', 512);
    key_queue = queue_new_empty();

    clear_term();
    term_initialized = true;
    tputs("Terminal initialized.\n");

    return 0;
}