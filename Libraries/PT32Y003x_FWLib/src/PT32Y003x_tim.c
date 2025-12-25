  /******************************************************************************
  * @file    PT32Y003x_tim.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the TIM peripheral:
  *            + TimeBase management
  *            + Output Compare management
  *            + Input Capture management
  *            + Interrupts, flags management
  *            + Clocks management
  *            + Synchronization management
  *            + Specific interface management
  *            + Specific remapping management
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
  

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_tim.h"



/** @defgroup TIM
  * @brief TIM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  TimeBaseInit: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
  * @retval None
  */
void TIM_TimeBaseInit(TIMx_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TimeBaseInit)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
    
    if(TIMx == TIM2 || TIMx == TIM3)
    {
        assert_param(IS_TIM_Direction(TimeBaseInit->TIM_Direction));       
        TIMx->CR2 &= ~TIM_CR2_DIR; 
        TIMx->CR2 |=  (TimeBaseInit->TIM_Direction);
    } 
	/* Set the counter match value */
	TIMx->ARR = TimeBaseInit->TIM_AutoReload;
	/* Set the Prescaler value */
	TIMx->PSC = TimeBaseInit->TIM_Prescaler;    
}


/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TimeBaseInit)
{

	TimeBaseInit->TIM_AutoReload = 0xFFFF;
	TimeBaseInit->TIM_Prescaler = 0x0000;
	TimeBaseInit->TIM_Direction = TIM_Direction_Up;
}


/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  Prescaler: specifies the Prescaler Register value (0~65535)
  * @retval None
  */
void TIM_SetPrescaler(TIMx_TypeDef* TIMx, u16 Prescaler)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	/* Set the Prescaler value */
	TIMx->PSC = Prescaler;
}


/**
  * @brief  Configures the TIMx Reload value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  Reload: specifies the Counter reload value (0~65535)
  * @retval None
  */
void TIM_SetAutoReload(TIMx_TypeDef* TIMx, u16 Reload)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	/* Set the counter reload value */
	TIMx->ARR = Reload;
}

/**
  * @brief  Configures the TIMx Current Value.
  * @param  TIMx: where x can be 2, 3 to select the TIM peripheral
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TIM_SetCounter(TIMx_TypeDef* TIMx, u16 Counter)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	/* Set the Counter Register value */
	TIMx->CNT = Counter;
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @retval Counter Register value.
  */
u16 TIM_GetCounter(TIMx_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	/* Get the Counter Register value */
	return  TIMx->CNT;
}

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @retval Prescaler Register value.
  */
u16 TIM_GetPrescaler(TIMx_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	/* Get the Prescaler Register value */
	return  TIMx->PSC;
}

/**
  * @brief  Enable or Disable TIMx Counter
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  */

void TIM_Cmd(TIMx_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState == ENABLE)
	{
		/* Set the update bit */
		TIMx->CR1 |= TIM_CR1_EN;
	}
	else
	{
		/* Reset the update bit */
		TIMx->CR1 &= ~TIM_CR1_EN;
	}
}

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  TIM_INT: Specify the TIM interrupts sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *        @arg TIM_CR2_ARI 
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  */

void TIM_ITConfig(TIMx_TypeDef* TIMx, u32 TIM_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_IT(TIM_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the interrupt sources */
		TIMx->CR2 |= TIM_IT;
	}
	else
	{
		/* Disable the interrupt sources */
		TIMx->CR2 &= ~TIM_IT;
	}
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  TIM_FLAG: Specify the flag to be checked.
  *         This parameter can be one of the following values:
  *         @arg TIMx_SR_ARF 
  * @return FlagStatus of TIM_FLAG (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(TIMx_TypeDef* TIMx, u32 TIM_FLAG)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_FLAG(TIM_FLAG));
	if ((TIMx->SR & TIM_FLAG) != 0)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
  * @brief  Clears the TIM's pending flags.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
  * @param  TIM_FLAG: Specify the flag to be cleared.
  *         This parameter can be one of the following values:
  *         @arg TTIMx_SR_ARF
  * @retval None
  */
void TIM_ClearFlag(TIMx_TypeDef* TIMx, u32 TIM_FLAG)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_FLAG(TIM_FLAG));
	/* Clear the flags */
	TIMx->SR |= TIM_FLAG;
}


/**
  * @}
  */
  

