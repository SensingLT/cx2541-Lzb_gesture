#ifndef __WDG_H__
#define __WDG_H__

#include <stdbool.h>
#include <stdint.h>


#define WDG_COUNTER_PER_SECOND 32768

#define WDG_MS_TO_COUNTER(ms) ((u32)((ms)*WDG_COUNTER_PER_SECOND/1000))


void Wdg_Init(uint32_t ms);

void Wdg_Feed(void);

#endif //__WDG_H__
