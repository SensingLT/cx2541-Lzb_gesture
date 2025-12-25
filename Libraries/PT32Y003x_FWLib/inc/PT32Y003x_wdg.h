  /******************************************************************************
  * @file    PT32Y003x_wdg.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the WDG firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
    

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003X_WDG_H
#define PT32Y003X_WDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

#define KR_KEY_DISABLE   		((u32)0xFFFFFFFF)

/** @addtogroup WDG
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define IS_WDG_ALL_PERIPH(SEL)     (((SEL) == IWDG))

///** @defgroup IS_WDG_Lock **/
#define IWDG_LockKey_UnLock       (IWDG_LOCK_KEY&0x1ACCE551)
#define IWDG_LockKey_Lock      (IWDG_LOCK_KEY&0xFFFFFFFF)
                       

/** @defgroup WDG_FLAG
* @{ 
*/
typedef enum
{
	WDG_FLAG_HungryDog   = 0x00,
	WDG_FLAG_LockStatus,         	
}WDG_FLAG;
#define IS_WDG_FLAG(SEL)		(((SEL) == WDG_FLAG_HungryDog) || \
                                ((SEL) == WDG_FLAG_LockStatus))

#define WDG_StatusBit       ((u32)0x00000001)        


/** @defgroup WDG_ReloadValue
* @{ 
*/
#define IS_WDG_ReloadValue(SEL) ((SEL) <= 0xFFFFFFFF)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void WDG_Cmd(IWDG_TypeDef* WDGx, FunctionalState NewState);
void WDG_ResetCmd(IWDG_TypeDef* WDGx, FunctionalState NewState);
void WDG_LockCmd(IWDG_TypeDef* WDGx, FunctionalState NewState);
FlagStatus WDG_GetFlagStatus(IWDG_TypeDef* WDGx, u32 WDG_FLAG);
void WDG_SetReload(IWDG_TypeDef* WDGx, u32 Reload);
void WDG_ReloadCounter(IWDG_TypeDef* WDGx);
void WDG_DBGPendingCmd(IWDG_TypeDef* WDGx, FunctionalState NewState);
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif 






