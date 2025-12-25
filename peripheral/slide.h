#ifndef _SLIDE_H_
#define _SLIDE_H_

#include <stdint.h>
#include <stdbool.h>

//滑动状态检测机
typedef enum{
	SLIDE_IDLE = 0,
	SLIDE_DETECTING,
	SLIDE_COMPLETE
}slide_state_e;

// 滑动方向
typedef enum {
    SLIDE_NONE,
    SLIDE_TO_FORWARD,
    SLIDE_TO_BACKWARD
} slide_direction_e;

void slide_init(void);
void slide_task(void);

#endif