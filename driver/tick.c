#include "tick.h"
//#include "at32f4xx_it.h"
#include "PT32Y003x.h" 


static volatile uint32_t gTick = 0;

uint32_t Tick_Get() {
    return gTick;
}

uint32_t Tick_Since(uint32_t baseTick) {
    return gTick - baseTick;
}

//是否从pBaseTick开始，已经过了tickSpan tick，如果是，更新pBaseTick
bool Tick_Passed(uint32_t* pBaseTick, uint32_t tickSpan) {
    if (Tick_Since(*pBaseTick) >= tickSpan) {
        *pBaseTick = gTick;
        return true;
    }
    return false;
}

void Tick_Delay(uint32_t tickSpan) {
    uint32_t from = gTick;
    while (gTick - from < tickSpan);
}


/**
  * @brief  定时器2,10ms时钟节拍
  * @param  None
  * @retval None
  */
void Tick_Init(void) {
    NVIC_InitTypeDef NVIC_InitStruct; //定义一个NVIC_InitTypeDef类型的结构体
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;//定义一个NVIC_InitTypeDef类型的结构体

    TIM_TimeBaseInitStruct.TIM_Prescaler = 4800-1; //48M/4800=0.01MHZ
    TIM_TimeBaseInitStruct.TIM_AutoReload = 100; //   1/（0.01MHZ）*100=10ms
    TIM_TimeBaseInitStruct.TIM_Direction = TIM_Direction_Up; //向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct); //初始化TIM2

    TIM_ITConfig(TIM2,TIM_IT_ARI,ENABLE); //定时中断初始化

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn; //定时中断源设置
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00; //中断优先级设置
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能NVIC控制器
    NVIC_Init(&NVIC_InitStruct); //初始化NVIC

    TIM_Cmd(TIM2, ENABLE); //开启TIM2
}


/**
* @brief TIMER2中断服务函数
* @param None
* @retval None
*/
void TIM2_Handler(void) {
    if (TIM_GetFlagStatus(TIM2, TIM_FLAG_ARF) != RESET) {
        TIM_ClearFlag(TIM2, TIM_FLAG_ARF);
        gTick++;;
    }
}

