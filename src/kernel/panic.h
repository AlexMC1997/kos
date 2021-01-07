#ifndef __panic
#define __panic

#include <stdint.h>

typedef enum __panic_video {
    VGA_TEXT
} panic_video;

extern uint8_t PANIC_VIDEO_MODE;
void panic(char* panicmsg);

#endif