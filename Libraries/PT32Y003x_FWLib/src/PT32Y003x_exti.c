  /******************************************************************************
  * @file    PT32Y003x_exti.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the functionality of EXTI peripherals
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_exti.h"


/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Enables or disables the specified exti interrupts.
  * @param  EXTIx: where x can be (A, B, C, D, E or F) to select the EXTI peripheral.
  * @param  NewState: new state of the specified EXTI interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EXTI_ITConfig(EXTI_TypeDef* EXTIx, u32 EXTI_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_EXTI_ALL_PERIPH(EXTIx));
	assert_param(IS_EXTI_IT(EXTI_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		EXTIx->IES |= EXTI_IT;
	}
	else
	{
		EXTIx->IEC |= EXTI_IT;
	}
}

/**
  * @brief Exti interrupts trigger types configuration
  * @param  EXTIx: where x can be (A, B, C, D, E or F) to select the EXTI peripheral.
  * @param  EXTI_Pin: specifies the port bit to be written. 
  * @param  TriggerType: the source of EXTI Trigger.
	*    @arg EXTI_Trigger_Rising: set rising as the EXTI Trigger source
	*    @arg EXTI_Trigger_Falling: set falling as the EXTI Trigger source
	*    @arg EXTI_Trigger_RisingFalling: set rising and falling as the EXTI Trigger source
	*    @arg EXTI_Trigger_HighLevel: set high level as the EXTI Trigger source
	*    @arg EXTI_Trigger_LowLevel: set low level as the EXTI Trigger source
  * @retval None
  */
void EXTI_TriggerTypeConfig(EXTI_TypeDef* EXTIx, u32 EXTI_Pin, EXTI_Trigger TriggerType)
{
	/* Check the parameters */
	assert_param(IS_EXTI_ALL_PERIPH(EXTIx));
	assert_param(IS_EXTI_Pin(EXTI_Pin));
	assert_param(IS_EXTI_Trigger(TriggerType));
	switch( TriggerType )
	{
		case EXTI_Trigger_Rising :
			EXTIx->ITS = EXTI_Pin;
			EXTIx->PTS =  EXTI_Pin;
			EXTIx->ITDC = EXTI_Pin;
			break;
		case EXTI_Trigger_Falling :
			EXTIx->ITS = EXTI_Pin;
			EXTIx->PTC =  EXTI_Pin;
			EXTIx->ITDC = EXTI_Pin;
			break;
		case EXTI_Trigger_RisingFalling :
			EXTIx->ITDS = EXTI_Pin;
			break;
		case EXTI_Trigger_HighLevel :
			EXTIx->ITC = EXTI_Pin;
			EXTIx->PTS =  EXTI_Pin;
			EXTIx->ITDC = EXTI_Pin;
			break;
		case EXTI_Trigger_LowLevel :
			EXTIx->ITC = EXTI_Pin;
			EXTIx->PTC =  EXTI_Pin;
			EXTIx->ITDC = EXTI_Pin;
		
			break;
	}
}

/**
  * @brief  Clears the EXTI's pending flags.
  * @param  EXTIx: where x can be (A, B, C or F) to select the EXTI peripheral.
  * @param  EXTI_IT_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  * @retval None
  */
void EXTI_ClearFlag(EXTI_TypeDef* EXTIx, u32 EXTI_IT_FLAG) 
{
	/* Check the parameters */
	assert_param(IS_EXTI_ALL_PERIPH(EXTIx));
	assert_param(IS_EXTI_FLAG(EXTI_IT_FLAG));
	EXTIx->IF |= EXTI_IT_FLAG;
}

/**
  * @brief  Checks whether the specified EXTI IT is set or not.
  * @param  EXTIx: where x can be (A, B, C or F) to select the EXTI peripheral.
  * @param  EXTI_IT: specifies the flag to get.
  *          This parameter can be one of the following values:
  *    @arg EXTI_IT_0  specifies the interrupt source for EXTIx0 interrupt
  *    @arg EXTI_IT_1  specifies the interrupt source for EXTIx1 interrupt
  *    @arg EXTI_IT_2  specifies the interrupt source for EXTIx2 interrupt
  *    @arg EXTI_IT_3  specifies the interrupt source for EXTIx3 interrupt
  *    @arg EXTI_IT_4  specifies the interrupt source for EXTIx4 interrupt
  *    @arg EXTI_IT_5  specifies the interrupt source for EXTIx5 interrupt
  *    @arg EXTI_IT_6  specifies the interrupt source for EXTIx6.interrupt
  *    @arg EXTI_IT_7  specifies the interrupt source for EXTIx7 interrupt
  *    @arg EXTI_IT_8  specifies the interrupt source for EXTIx8 interrupt
  *    @arg EXTI_IT_9  specifies the interrupt source for EXTIx9 interrupt
  *    @arg EXTI_IT_10 specifies the interrupt source for EXTIx10 interrupt
  *    @arg EXTI_IT_11 specifies the interrupt source for EXTIx11 interrupt
  *    @arg EXTI_IT_12 specifies the interrupt source for EXTIx12 interrupt
  *    @arg EXTI_IT_13 specifies the interrupt source for EXTIx13 interrupt
  *    @arg EXTI_IT_14 specifies the interrupt source for EXTIx14 interrupt
  *    @arg EXTI_IT_15 specifies the interrupt source for EXTIx15 interrupt
  *    @arg EXTI_IT_All specifies the interrupt source for All interrupt
  * @retval ITStatus:interrupts status,the value can be 'SET' or 'RESET'.
  */
ITStatus EXTI_GetITStatus(EXTI_TypeDef* EXTIx, u32 EXTI_IT)
{
	ITStatus bitstatus = RESET;
	u32 enablestatus = 0;
	/* Check the parameters */
	assert_param(IS_EXTI_ALL_PERIPH(EXTIx));
	assert_param(IS_EXTI_IT(EXTI_IT));

	enablestatus = (u32)(EXTIx->IES & EXTI_IT);
	if (((u32)(EXTIx->IF & EXTI_IT) != (u32)RESET) && (enablestatus != (u32)RESET))
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	return  bitstatus;
}


/**
  * @}
  */

