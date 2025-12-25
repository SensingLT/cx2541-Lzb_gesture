#ifndef __ADC_H__
#define __ADC_H__

#include <stdbool.h>
#include <stdint.h>

void Adc_Init(void);

//返回最后更新的Tick值
uint32_t Adc_Get(uint16_t *adc);

#endif //__ADC_H__
