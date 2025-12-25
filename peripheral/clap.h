#ifndef _CLAP_H_
#define _CLAP_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    CLAP_ZERO = 0,    // 无按键
    CLAP_SINGLE = 1,    // 连拍1次
    CLAP_DOUBLE = 2,    // 连拍2次
    CLAP_TRIPLE = 3,     // 连拍3次
	CLAP_INVALID
} clap_count_e;

void clap_init(void);
void clap_task(void);

#endif