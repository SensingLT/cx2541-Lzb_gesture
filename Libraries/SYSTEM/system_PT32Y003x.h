/**
  ******************************************************************************
  * @file    system_PT32x03x.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2021/5/28
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 当前的固件仅供指导, 目的是向客户提供有关其产品的编码信息,以节省他们的时间。 
  * 对于因此类固件的内容/或客户使用其中包含的编码信息而引起的任何索赔,
  * Pai-IC不对任何直接， 间接或继发的损害负责。
  * 
  * (C) 版权所有Pai-IC Microelectronics  
  ******************************************************************************
  */


  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SYSTEM_PT32Y003x_H
#define SYSTEM_PT32Y003x_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

#define RCC_Freq_HSI   48000000UL
#define RCC_Freq_LSI   32768UL
#define RCC_Freq_HSE   25000000UL





/* Exported macro ------------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
u32 CLOCK_GetSYSCLK(void);
//u32 RCC_GetClockFreq(u8 RCC_Clock);
void CLOCK_Cmd(void);	
void CLOCK_PLLConfig(void);     
void CLOCK_SystemClockConfig(void);   
void CLOCK_MCOConfig(void);
void SystemInit(void);
#ifdef __cplusplus
}
#endif

#endif /*system_PT32x03x_h*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) 版权所有 Pai-IC Microelectronics *****END OF FILE****/

