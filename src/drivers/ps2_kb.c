#include "ps2.h"
#include "ps2_kb.h"

extern PS2_Tab_Entry PS2_TABLE[];
extern char PS2_ASCII_TABLE[];
static e_ps2_locks locks = 0;

static char apply_mod_lock(char c, e_ps2_mods mods, e_ps2_locks locks)
{
    char nc = c;
    bool shft = mods & (PS2_MOD_LSHFT | PS2_MOD_RSHFT);
    if ((c >= 'a') && (c <= 'z')) {
        if (locks & PS2_LOCK_CAPS) {
            if (!shft)
                nc -= 0x20;
        } else if (shft)
            nc -= 0x20;
    } else if (shft) switch (c) {
        case '`': nc = '~'; break;
        case '1': nc = '!'; break;
        case '2': nc = '@'; break;
        case '3': nc = '#'; break;
        case '4': nc = '$'; break;
        case '5': nc = '%'; break;
        case '6': nc = '^'; break;
        case '7': nc = '&'; break;
        case '8': nc = '*'; break;
        case '9': nc = '('; break;
        case '0': nc = ')'; break;
        case '-': nc = '_'; break;
        case '=': nc = '+'; break;
        case '[': nc = '{'; break;
        case ']': nc = '}'; break;
        case '\\': nc = '|'; break;
        case ';': nc = ':'; break;
        case '\'': nc = '"'; break;
        case ',': nc = '<'; break;
        case '.': nc = '>'; break;
        case '/': nc = '?'; break;
        default: break;
    } 
    return nc;
}

void ps2_kb_get_key(PS2_Key_Info* key_info)
{
    bool release = false;
    PS2_Tab_Entry scan_code = {{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0x0};
    for (uint8_t* k_ptr = &(scan_code.code); ps2_get_byte(k_ptr); k_ptr++) {
        if (*k_ptr == PS2_KEY_RELEASE_BYTE) {
            release = true;
            k_ptr--;
        }
    }
    e_ps2_keys key = 0;
    for (; key <= PS2_K_NUM_PERIOD; key++) {
        if (
            PS2_TABLE[key].code[0] == scan_code.code[0]
            && PS2_TABLE[key].code[1] == scan_code.code[1]
            && PS2_TABLE[key].code[2] == scan_code.code[2]
            && PS2_TABLE[key].code[3] == scan_code.code[3]
            && PS2_TABLE[key].code[4] == scan_code.code[4]
            && PS2_TABLE[key].code[5] == scan_code.code[5]
        ) {
            PS2_TABLE[key].pressed = !release;
            break;
        }
    }

    if (!release) switch (key) {
        case PS2_K_CAPSLK: locks ^= PS2_LOCK_CAPS; break;
        case PS2_K_NUMLK: locks ^= PS2_LOCK_NUM; break;
        case PS2_K_SCRLK: locks ^= PS2_LOCK_SCRL; break;
        default: break;
    }

    if (key_info) {
        key_info->key = key;
        key_info->released = release;
        key_info->mods = (
            (PS2_TABLE[PS2_K_LSHIFT].pressed << PS2_MOD_LSHFT)
            | (PS2_TABLE[PS2_K_RSHIFT].pressed << PS2_MOD_RSHFT)
            | (PS2_TABLE[PS2_K_LALT].pressed << PS2_MOD_LALT)
            | (PS2_TABLE[PS2_K_RALT].pressed << PS2_MOD_RALT)
            | (PS2_TABLE[PS2_K_LCTRL].pressed << PS2_MOD_LCTRL)
            | (PS2_TABLE[PS2_K_RCTRL].pressed << PS2_MOD_RCTRL)
        );
        key_info->locks = locks;
        key_info->ascii = apply_mod_lock(PS2_ASCII_TABLE[key], key_info->mods, locks);
    }
}

e_ps2_kb_response ps2_kb_echo()
{
    e_ps2_kb_response response;
    uint8_t sentry = 0;
    do {
        ps2_send_byte(PS2_KB_COM_ECHO);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response == PS2_KB_RESEND);
    return response;
}

void ps2_kb_set_scan(uint8_t set)
{
    e_ps2_kb_response response;
    uint8_t sentry = 0;
    if (set < 1 || set > 3)
        return;
    do {
        ps2_send_byte(PS2_KB_COM_SETSCAN);
        ps2_send_byte(set);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response != PS2_KB_ACK);
}

void ps2_kb_enable_scan()
{
    e_ps2_kb_response response;
    uint8_t sentry = 0;
    do {
        ps2_send_byte(PS2_KB_COM_EN_SCANNING);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response != PS2_KB_ACK);
}

void ps2_kb_disable_scan()
{
    e_ps2_kb_response response;
    uint8_t sentry = 0;
    do {
        ps2_send_byte(PS2_KB_COM_DIS_SCANNING);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response != PS2_KB_ACK);
}

void ps2_kb_set_default()
{
    e_ps2_kb_response response;
    uint8_t sentry = 0;
    do {  
        ps2_send_byte(PS2_KB_COM_DEFAULT);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response != PS2_KB_ACK);
}

uint8_t ps2_kb_resend()
{
    e_ps2_kb_response response;
    uint8_t sentry = 0;
    do {
        ps2_send_byte(PS2_KB_COM_RESEND);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response == PS2_KB_RESEND);
    return response;
}

e_ps2_kb_response ps2_kb_reset()
{
    uint8_t response;
    uint8_t sentry = 0;
    do {
        ps2_send_byte(PS2_KB_COM_RESET);
        ps2_get_byte(&response);
        if (++sentry == 4)
            panic("Keyboard malfunction.");
    } while (response == PS2_KB_RESEND);
    return response;
}

void ps2_kb_init()
{
    // if (ps2_kb_reset() == PS2_KB_TEST_FAIL)
    //     panic("Keyboard self-test failed.");
    // ps2_kb_disable_scan();
    // ps2_kb_set_scan(2);
    // ps2_kb_enable_scan();
}