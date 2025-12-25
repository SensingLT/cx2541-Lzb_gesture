  /******************************************************************************
  * @file    PT32X03X_rcc.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the SYS firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_RCC_H
#define PT32Y003x_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

/** @defgroup RCC_Clock_Frequency_Selection
  * @{
  */
#define RCC_SYSCLK									 ((u8)0x01)
#define RCC_HCLK										 ((u8)0x02)
#define RCC_PCLK										 ((u8)0x03)
#define IS_RCC_Clock(SEL)   				 (((SEL) == RCC_SYSCLK)  || ((SEL) == RCC_HCLK)  || ((SEL) == RCC_PCLK))
/**
  * @}
  */ 

/** @defgroup RCC_clock_output_source
  * @{
  */
#define RCC_ClockOutput_HSI			(RCC_MCOR_COS&0x00)
#define RCC_ClockOutput_HSE			(RCC_MCOR_COS&0x10)
#define RCC_ClockOutput_PLL			(RCC_MCOR_COS&0x20)
#define RCC_ClockOutput_LSI			(RCC_MCOR_COS&0x30)
#define RCC_ClockOutput_SYS			(RCC_MCOR_COS&0x40)
#define RCC_ClockOutput_None		(RCC_MCOR_COS&0x70)
#define IS_RCC_ClockOutputSource(SEL)   	(((SEL) == RCC_ClockOutput_HSI)   || \
																					 ((SEL) == RCC_ClockOutput_HSE)   || \
																					 ((SEL) == RCC_ClockOutput_PLL)   || \
																					 ((SEL) == RCC_ClockOutput_LSI)   || \
																					 ((SEL) == RCC_ClockOutput_SYS)   || \
																					 ((SEL) == RCC_ClockOutput_None))
/**
  * @}
  */ 

/** @defgroup RCC_system_clock_switch_source
  * @{
  */
#define RCC_SystemClock_HSI	(RCC_CFGR_SCW&0x00)
#define RCC_SystemClock_HSE	(RCC_CFGR_SCW&0x01)
#define RCC_SystemClock_PLL	(RCC_CFGR_SCW&0x02)
#define IS_RCC_SystemClock(SEL)  (((SEL) == RCC_SystemClock_HSI) ||\
                                  ((SEL) == RCC_SystemClock_HSE) ||\
                                  ((SEL) == RCC_SystemClock_PLL))
																	 
#define RCC_ClockSource_HSI					(0x00) 	//Internal Hight CLK Source
#define RCC_ClockSource_HSE 				(0x01) 	//Extern Hight CLK  Source
#define RCC_ClockSource_HSEExternal			(0x02) 	//Extern Hight CLK Source
#define RCC_ClockSource_PLL					(0x03)	//Extern Low CLK Source
#define RCC_ClockSource_LSI					(0x04) 	//Internal Low CLK Source
#define IS_RCC_ClockSource(SEL) 			(((SEL) == RCC_ClockSource_HSI)   || \
                                             ((SEL) == RCC_ClockSource_HSE) 	|| \
                                             ((SEL) == RCC_ClockSource_PLL) 	|| \
                                             ((SEL) == RCC_ClockSource_LSI))
/**
  * @}
  */ 											 
								
/** @defgroup RCC_Reset_State_Flag
  * @{
  */
#define	RCC_FLAG_SFR        RCC_RSR_SFR
#define	RCC_FLAG_IWDG       RCC_RSR_IWDR
#define	RCC_FLAG_CPU        RCC_RSR_CPU
#define	RCC_FLAG_HSE        RCC_RSR_HSE
#define	RCC_FLAG_POR        RCC_RSR_POR
#define	RCC_FLAG_PIN        RCC_RSR_PIN
#define	RCC_FLAG_PVD        RCC_RSR_PVD
#define RCC_FLAG_RDY        RCC_HSECR1_RDY
#define RCC_FLAG_HSEDE      RCC_CFGR_HSEDE
#define RCC_FLAG_ALL        (RCC_FLAG_SFR|RCC_FLAG_IWDG|RCC_FLAG_CPU|RCC_FLAG_HSE|RCC_FLAG_POR|RCC_FLAG_PIN|RCC_FLAG_PVD)
#define IS_RCC_FLAG(SEL)       ((SEL == RCC_FLAG_SFR)   ||\
								(SEL == RCC_FLAG_IWDG)  ||\
                                (SEL == RCC_FLAG_CPU)   ||\
                                (SEL == RCC_FLAG_HSE)   ||\
                                (SEL == RCC_FLAG_PVD)   ||\
                                (SEL == RCC_FLAG_POR)   ||\
                                (SEL == RCC_FLAG_PIN)   ||\
                                (SEL == RCC_FLAG_RDY)   ||\
                                (SEL == RCC_FLAG_HSEDE) ||\
                                (SEL == RCC_FLAG_ALL))
/**
  * @}
  */																

/** @defgroup RCC_Reset_selection
  * @{
  */
#define RCC_ResetEnable_PDRE    RCC_RCR_PDRE
#define IS_RCC_ResetEnable(SEL)    ((SEL == RCC_ResetEnable_PDRE))
/**
  * @}
  */

/** @defgroup RCC_Key_selection
  * @{
  */
	
#define RCC_AdvancedSoftwareReset_CWR 	(u8)(0x00)
#define RCC_AdvancedSoftwareReset_CPU	(u8)(0x01)
#define RCC_KEY_CWR    									(u16)0xAB56
#define RCC_KEY_CPU    									(u16)0xC57A
#define IS_RCC_AdvancedSoftwareRese(SEL)   ((SEL == RCC_AdvancedSoftwareReset_CWR) || (SEL == RCC_AdvancedSoftwareReset_CPU))
/**
  * @}
  */
/** @defgroup RCC_HCLK_prescaler_value
  * @{
  */
#define IS_RCC_HCLKPrescaler(SEL)   	 ((SEL) <= 31)
/**
  * @}
  */

/** @defgroup RCC_PCLK_prescaler_value
  * @{
  */
#define IS_RCC_PCLKPrescaler(SEL)   	 ((SEL) <= 31)
/**
  * @}
  */

/** @defgroup RCC_clock_output_Prescale_value
  * @{
  */
#define RCC_ClockOutputPrescale_None      	  (RCC_MCOR_COPRE&0x00)
#define RCC_ClockOutputPrescale_2      		  (RCC_MCOR_COPRE&0x01)
#define RCC_ClockOutputPrescale_4      		  (RCC_MCOR_COPRE&0x02)
#define RCC_ClockOutputPrescale_8      		  (RCC_MCOR_COPRE&0x03)
#define RCC_ClockOutputPrescale_16      	  (RCC_MCOR_COPRE&0x04)
#define IS_RCC_ClockOutputPrescale(SEL)   	(((SEL) == RCC_ClockOutputPrescale_None) ||\
                                             ((SEL) == RCC_ClockOutputPrescale_2) 	 ||\
                                             ((SEL) == RCC_ClockOutputPrescale_4) 	 ||\
                                             ((SEL) == RCC_ClockOutputPrescale_8)  	 ||\
                                             ((SEL) == RCC_ClockOutputPrescale_16))
/**
  * @}
  */	

/** @defgroup RCC_system_clock_after_wakeup_selection
  * @{
  */
#define RCC_SystemClockAfterWakeUp_HSI				0x00000000
#define RCC_SystemClockAfterWakeUp_PreviousClock	RCC_CFGR_WKCK
#define IS_RCC_SystemClockAfterWakeUp(SEL)   	(((SEL) == RCC_SystemClockAfterWakeUp_HSI) ||\
												((SEL) == RCC_SystemClockAfterWakeUp_PreviousClock))
/**
  * @}
  */	

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
u32 RCC_GetClockFreq(u8 RCC_Clock);
FlagStatus RCC_GetFlagStatus(u32 RCC_FLAG);
void RCC_ClearFlag(u32 RCC_FLAG);
void RCC_ResetConfig(u32 ResetSource, FunctionalState NewState);
void RCC_ClockSourceConfig(u32 ClockSource,FunctionalState NewState);
void RCC_AdvancedSoftwareReset(u8 RCC_AdvancedSoftwareResetSource);
void RCC_SetSystemClock(u32 SystemClockSwitch);
void RCC_SetSystemClockAfterWakeUp(u32 Clock);
void RCC_PLLClockSourceConfig(u32 PLLClockSource);
void RCC_HCLKSetPrescaler(u32 Prescaler);
void RCC_PCLKSetPrescaler(u32 Prescaler);
u8 RCC_GetSystemClockSelection(void);
void RCC_SetMCOSource(u32 ClockSource);
void RCC_MCOSetPrescaler(u32 PrescaleSelcection);


/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif 

