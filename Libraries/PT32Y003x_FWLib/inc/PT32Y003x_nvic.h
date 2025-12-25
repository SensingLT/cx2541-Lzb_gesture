  /******************************************************************************
  * @file    PT32Y003x_misc.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the MISC firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_NVIC_H
#define PT32Y003x_NVIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/** @addtogroup MISC
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/

/** @brief  NVIC Init Structure definition **/
typedef struct
{
	u8 NVIC_IRQChannel;             /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of @ref IRQn_Type
                                            (For the complete PT32 Devices IRQ Channels list,
                                            please refer to pt32f0xx.h file) */

	u8 NVIC_IRQChannelPriority;     /*!< Specifies the priority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 3.  */

	FunctionalState NVIC_IRQChannelCmd;  /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled.
                                            This parameter can be set either to ENABLE or DISABLE */
} NVIC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup MISC_System_Low_Power **/
#define NVIC_LP_SEVONPEND            ((u8)0x10)
#define NVIC_LP_SLEEPDEEP            ((u8)0x04)
#define NVIC_LP_SLEEPONEXIT          ((u8)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
                        ((LP) == NVIC_LP_SLEEPDEEP) || \
                        ((LP) == NVIC_LP_SLEEPONEXIT))
                        
/** @defgroup MISC_Preemption_Priority_Group **/
#define IS_NVIC_PRIORITY(PRIORITY)  ((PRIORITY) < 0x04)

/** @defgroup MISC_SysTick_clock_source **/
#define SysTick_CLKSource_HCLK_Div8    ((u32)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((u32)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || ((SOURCE) == SysTick_CLKSource_HCLK_Div8))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SystemLPConfig(u8 LowPowerMode, FunctionalState NewState);


/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif


