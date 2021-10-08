#ifndef _PANIC_H
#define _PANIC_H

#include <stdint.h>

typedef enum {
    VGA_TEXT
} panic_video_e;

extern uint8_t PANIC_VIDEO_MODE;
void panic(char* panicmsg);

#endif