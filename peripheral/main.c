#include "PT32Y003x.h"
#include <stdbool.h>
#include <string.h>
#include "tick.h"
#include "wdg.h"
#include "adc.h"
#include "uart.h"
#include "crc.h"
#include "protocol.h"
#include "config.h"
#include "clap.h"
#include "slide.h"
#include "public.h"

// 复位控制代码，必须使用 
void NRST_PBO_SetZero(void) 
{ 
    GPIO_InitTypeDef GPIO_InitStructure; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OutPP; 
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NoPull; 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            //nRST -- PBO 
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    GPIO_DigitalRemapConfig(AFIOB, GPIO_Pin_0, AFIO_AF_1, ENABLE); 
    GPIOB->MASKL[0x01] = 0; 
    PWR->PVDR = 0x07;                                 //LVD-2.5V复位 
}


int main (void) {
	NRST_PBO_SetZero();
	Tick_Init();
	Uart_Init(9600);
	Wdg_Init(WDG_COUNTER_PER_SECOND); //timeout=1s 设置看门狗重装载值
#if(DETECT_MODE > 0)
		clap_init();
#else
		slide_init();
#endif
	uint8_t revMsg[UART_MAX_REV_LEN];
	while (1) {	
		#if(DETECT_MODE > 0)
			static uint32_t clapTick = 0;
			if (Tick_Passed(&clapTick, 5)) {
				clap_task();
			}
		#else
			static uint32_t slideTick = 0;
			if (Tick_Passed(&slideTick, 3)) {
				slide_task();
			}
		#endif	
		
//		static uint32_t dbgTick = 0;
//		if (Tick_Passed(&dbgTick, 1)) {
//			int msgLen = Uart_GetRevMsg(revMsg, UART_MAX_REV_LEN);
//			if (msgLen > 0) {
//				if (!Protocol_HandleMsg(revMsg, msgLen)) {
//					if (msgLen < UART_MAX_REV_LEN) {
//						revMsg[msgLen] = 0;
//					}
//					DBG_LN("unhandled msg[len = %d]: %s", msgLen, revMsg);
//				}
//			}
//		}
		Wdg_Feed();
	}
}




#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(u8* file, u32 line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    Uart_SendStr("Wrong parameters value: file %s on line %lu\r\n", file, line);
    /* Infinite loop */
    while (1) {
    }
}
#endif


