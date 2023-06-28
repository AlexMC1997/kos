#ifndef _PS2_KB_H
#define _PS2_KB_H

#include "stdint.h"
#include "stdbool.h"

#define PS2_KEY_RELEASE_BYTE 0xF0

typedef enum ps2_keys {
    PS2_K_ESC,
    PS2_K_F1,
    PS2_K_F2,
    PS2_K_F3,
    PS2_K_F4,
    PS2_K_F5,
    PS2_K_F6,
    PS2_K_F7,
    PS2_K_F8,
    PS2_K_F9,
    PS2_K_F10,
    PS2_K_F11,
    PS2_K_F12,
    PS2_K_PRTSC,
    PS2_K_SCRLK,
    PS2_K_PAUSE,
    PS2_K_TICK,
    PS2_K_1,
    PS2_K_2,
    PS2_K_3,
    PS2_K_4,
    PS2_K_5,
    PS2_K_6,
    PS2_K_7,
    PS2_K_8,
    PS2_K_9,
    PS2_K_0,
    PS2_K_DASH,
    PS2_K_EQUALS,
    PS2_K_BACK,
    PS2_K_INSERT,
    PS2_K_HOME,
    PS2_K_PGUP,
    PS2_K_NUMLK,
    PS2_K_NUM_SLASH,
    PS2_K_NUM_STAR,
    PS2_K_NUM_MINUS,
    PS2_K_TAB,
    PS2_K_Q,
    PS2_K_W,
    PS2_K_E,
    PS2_K_R,
    PS2_K_T,
    PS2_K_Y,
    PS2_K_U,
    PS2_K_I,
    PS2_K_O,
    PS2_K_P,
    PS2_K_LBRACK,
    PS2_K_RBRACK,
    PS2_K_BACKSLASH,
    PS2_K_DELETE,
    PS2_K_END,
    PS2_K_PGDWN,
    PS2_K_NUM_7,
    PS2_K_NUM_8,
    PS2_K_NUM_9,
    PS2_K_NUM_PLUS,
    PS2_K_CAPSLK,
    PS2_K_A,
    PS2_K_S,
    PS2_K_D,
    PS2_K_F,
    PS2_K_G,
    PS2_K_H,
    PS2_K_J,
    PS2_K_K,
    PS2_K_L,
    PS2_K_SEMICOLON,
    PS2_K_APOSTROPHE,
    PS2_K_ENTER,
    PS2_K_NUM_4,
    PS2_K_NUM_5,
    PS2_K_NUM_6,
    PS2_K_LSHIFT,
    PS2_K_Z,
    PS2_K_X,
    PS2_K_C,
    PS2_K_V,
    PS2_K_B,
    PS2_K_N,
    PS2_K_M,
    PS2_K_COMMA,
    PS2_K_PERIOD,
    PS2_K_SLASH,
    PS2_K_RSHIFT,
    PS2_K_UP,
    PS2_K_NUM_1,
    PS2_K_NUM_2,
    PS2_K_NUM_3,
    PS2_K_NUM_ENTER,
    PS2_K_LCTRL,
    PS2_K_LWIN,
    PS2_K_LALT,
    PS2_K_SPACE,
    PS2_K_RALT,
    PS2_K_RWIN,
    PS2_K_MENUS,
    PS2_K_RCTRL,
    PS2_K_LEFT,
    PS2_K_DOWN,
    PS2_K_RIGHT,
    PS2_K_NUM_0,
    PS2_K_NUM_PERIOD,
    PS2_K_DELIMIT
} e_ps2_keys;

typedef enum ps2_kb_response {
    PS2_KB_ACK = 0xFA,
    PS2_KB_RESEND = 0xFE,
    PS2_KB_TEST_PASS = 0xAA,
    PS2_KB_TEST_FAIL = 0xFC,
    PS2_KB_TEST_FAIL2 = 0xFD,
    PS2_KB_ECHO = 0xEE,
    PS2_KB_ERROR = 0xFF,
} e_ps2_kb_response;

typedef enum ps2_kb_command {
    PS2_KB_COM_LED = 0xED,
    PS2_KB_COM_ECHO = 0xEE,
    PS2_KB_COM_SETSCAN = 0xF0,
    PS2_KB_COM_ID = 0xF2,
    PS2_KB_COM_SETTYPE,
    PS2_KB_COM_EN_SCANNING,
    PS2_KB_COM_DIS_SCANNING,
    PS2_KB_COM_DEFAULT,
    PS2_KB_COM_TAUTO,
    PS2_KB_COM_MKREL,
    PS2_KB_COM_MKONLY,
    PS2_KB_COM_KTAUTOMKREL,
    PS2_KB_COM_KMKREL,
    PS2_KB_COM_RESEND,
    PS2_KB_COM_RESET
} e_ps2_kb_command;

typedef enum ps2_mods {
    PS2_MOD_LSHFT = 1,
    PS2_MOD_RSHFT = 2,
    PS2_MOD_LCTRL = 4,
    PS2_MOD_RCTRL = 8,
    PS2_MOD_LALT = 16,
    PS2_MOD_RALT = 32,
} e_ps2_mods;

typedef enum ps2_locks {
    PS2_LOCK_CAPS = 1,
    PS2_LOCK_SCRL = 2,
    PS2_LOCK_NUM = 4,
} e_ps2_locks;

typedef struct {
    uint8_t code[7];
    uint8_t pressed;   
} PS2_Tab_Entry;

typedef struct PS2_Key_Info {
    e_ps2_keys key;
    char ascii;
    bool released;
    e_ps2_mods mods;
    e_ps2_locks locks;
} PS2_Key_Info;

void ps2_kb_get_key();
void ps2_kb_init();

#endif