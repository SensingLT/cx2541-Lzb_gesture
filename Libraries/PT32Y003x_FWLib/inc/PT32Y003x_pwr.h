/**
  ******************************************************************************
  * @file    PT32X03x_pwr.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief   This file contains all the functions prototypes for the PWR firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_PWR_H
#define PT32Y003x_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */ 

/** @defgroup PWR_PVD_detection_level 
  * @brief   
  * @{
  */ 
#define PWR_PVDLevel_0		(PWR_PVDR_PLS&0x00)		
#define PWR_PVDLevel_1		(PWR_PVDR_PLS&0x02)		
#define PWR_PVDLevel_2		(PWR_PVDR_PLS&0x04)		
#define PWR_PVDLevel_3		(PWR_PVDR_PLS&0x06)		
#define PWR_PVDLevel_4		(PWR_PVDR_PLS&0x08)		
#define PWR_PVDLevel_5		(PWR_PVDR_PLS&0x0A)		
#define PWR_PVDLevel_6		(PWR_PVDR_PLS&0x0C)		
#define PWR_PVDLevel_7		(PWR_PVDR_PLS&0x0E)			
#define IS_PWR_PVDLevel(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))
/**
  * @}
  */



/** @defgroup PWR_Sleep_mode_entry 
  * @{
  */
#define PWR_SleepEntry_WFI              ((u8)0x01)
#define PWR_SleepEntry_WFE              ((u8)0x02)
#define IS_PWR_SleepEntry(SEL) 					(((SEL) == PWR_SleepEntry_WFI) || ((SEL) == PWR_SleepEntry_WFE))
 
/**
  * @}
  */

/** @defgroup PWR_DeepSleep_mode_entry 
  * @{
  */
#define PWR_DeepSleepEntry_WFI           ((u8)0x01)
#define PWR_DeepSleepEntry_WFE           ((u8)0x02)
#define IS_PWR_DeepSleepEntry(SEL) 			 (((SEL) == PWR_DeepSleepEntry_WFI) || ((SEL) == PWR_DeepSleepEntry_WFE))
 
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PWR_PVDLevelConfig(u32 PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState); 
void PWR_EnterSleepMode(u8 PWR_SleepEntry);
void PWR_EnterDeepSleepMode(u8 PWR_DeepStandbyEntry);

#ifdef __cplusplus
}
#endif

#endif /* __PT32F0XX_PWR_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) *****END OF FILE****/
