
  /******************************************************************************
  * @file    PT32Y003x_tim.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the TIM firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_TIM_H
#define PT32Y003x_TIM_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

/** @addtogroup TIM **/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define IS_TIM_ALL_PERIPH(PERIPH)            (((PERIPH) == TIM2) ||((PERIPH) == TIM3)||((PERIPH) == TIM4))

typedef struct
{
	u16	TIM_AutoReload;           /*!< Period (Value for MR0 register)             */
	u16	TIM_Prescaler;             /*!< Prescaler (Value for PR register)           */
	u32	TIM_Direction;           /*!< Counter mode up-counting or down-counting   */
} TIM_TimeBaseInitTypeDef;
  
#define TIM_Direction_Up               0x00000000
#define TIM_Direction_Down             TIM_CR2_DIR
#define IS_TIM_Direction(SEL)          (((SEL) == TIM_Direction_Up) ||\
                                        ((SEL) == TIM_Direction_Down))

#define TIM_IT_ARI      TIM_CR2_ARI
#define IS_TIM_IT(SEL)         ((SEL) == TIM_IT_ARI)

#define TIM_FLAG_ARF  TIM_SR_ARF
#define IS_TIM_FLAG(SEL)       ((SEL) == TIM_FLAG_ARF)




/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------------------------------------*/
void TIM_TimeBaseInit(TIMx_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TimeBaseInit);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TimeBaseInit);
void TIM_SetPrescaler(TIMx_TypeDef* TIMx, u16 Prescaler);
void TIM_SetAutoReload(TIMx_TypeDef* TIMx, u16 Reload);
void TIM_SetCounter(TIMx_TypeDef* TIMx, u16 Counter);
u16 TIM_GetCounter(TIMx_TypeDef* TIMx);
u16 TIM_GetPrescaler(TIMx_TypeDef* TIMx);
void TIM_Cmd(TIMx_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIMx_TypeDef* TIMx, u32 TIM_IT, FunctionalState NewState);
FlagStatus TIM_GetFlagStatus(TIMx_TypeDef* TIMx, u32 TIM_FLAG);
void TIM_ClearFlag(TIMx_TypeDef* TIMx, u32 TIM_FLAG);
/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif


