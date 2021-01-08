#ifndef _PANIC_H
#define _PANIC_H

#include <stdint.h>

typedef enum __panic_video {
    VGA_TEXT
} panic_video;

extern uint8_t PANIC_VIDEO_MODE;
void panic(char* panicmsg);

#endif