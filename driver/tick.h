#ifndef __TICK_H__
#define __TICK_H__

#include <stdbool.h>
#include <stdint.h>

//1 tick有多少个ms
#define TICK_MS  10

//1s有多少个tick
#define SECOND_TICK_NUM 100

#define MS_TO_TICK(ms) ((ms)/TICK_MS)

#define TICK_TO_MS(tick) ((tick) * TICK_MS)

void Tick_Init();

uint32_t Tick_Get();

uint32_t Tick_Since(uint32_t baseTick);

//是否从pBaseTick开始，已经过了tickSpan tick，如果是，更新pBaseTick
bool Tick_Passed(uint32_t* pBaseTick, uint32_t tickSpan);


void Tick_Delay(uint32_t tickSpan);

#endif