  /******************************************************************************
  * @file    PT32Y003x_misc.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides all the miscellaneous firmware functions (add-on
  *          to CMSIS functions).
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

  
/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_nvic.h"


/** @defgroup MISC
  * @brief MISC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
	u32 tmppriority = 0x00;
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
	assert_param(IS_NVIC_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPriority));
	if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
	{
		/* Compute the Corresponding IRQ Priority --------------------------------*/
		tmppriority = NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02];
		tmppriority &= (u32)(~(((u32)0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8)));
		tmppriority |= (u32)((((u32)NVIC_InitStruct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8));
		NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02] = tmppriority;
		/* Enable the Selected IRQ Channels --------------------------------------*/
		NVIC->ISER[0] = (u32)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (u8)0x1F);
	}
	else
	{
		/* Disable the Selected IRQ Channels -------------------------------------*/
		NVIC->ICER[0] = (u32)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (u8)0x1F);
	}
}


/**
  * @brief  Selects the condition for the system to enter low power mode.
  * @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
  *          This parameter can be one of the following values:
  *            @arg NVIC_LP_SEVONPEND: Low Power SEV on Pend.
  *            @arg NVIC_LP_SLEEPDEEP: Low Power DEEPSLEEP request.
  *            @arg NVIC_LP_SLEEPONEXIT: Low Power Sleep on Exit.
  * @param  NewState: new state of LP condition.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLPConfig(u8 LowPowerMode, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_NVIC_LP(LowPowerMode));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		SCB->SCR |= LowPowerMode;
	}
	else
	{
		SCB->SCR &= (u32)(~(u32)LowPowerMode);
	}
}

/**
  * @}
  */

