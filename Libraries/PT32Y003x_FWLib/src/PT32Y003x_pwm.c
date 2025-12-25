  /******************************************************************************
  * @file    PT32Y003x_pwm.c
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
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_pwm.h"

/** @defgroup PWM
  * @brief PWM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TimeBaseInit_CR1_MASK   ((u32)0xFFFFF9FB)

#define Init_CAPRCH1_MASK   ((u32)0XFFF8FFF8)
#define Init_CAPRCH2_MASK   ((u32)0XFF8FFF8F)
#define Init_CAPRCH3_MASK   ((u32)0XF8FFF8FF)
#define Init_CAPRCH4_MASK   ((u32)0X8FFF8FFF)

#define Init_OCMRCH1_MASK   ((u32)0XEEEEFFF8)
#define Init_OCMRCH2_MASK   ((u32)0XDDDDFF8F)
#define Init_OCMRCH3_MASK   ((u32)0XBBBBF8FF)
#define Init_OCMRCH4_MASK   ((u32)0X77778FFF)

#define Init_CR3CH1_MASK    ((u32)0XFFFFFFFC)
#define Init_CR3CH2_MASK    ((u32)0XFFFFFFCF)
#define Init_CR3CH3_MASK    ((u32)0XFFFFFCFF)
#define Init_CR3CH4_MASK    ((u32)0XFFFFCFFF)

#define Init_BDTR_MASK 		  ((u32)0X010F0FFF)
#define Init_BKICR_MASK 		((u32)0XFFFFFFCE)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the PWMx Time Base Unit peripheral according to
  *         the specified parameters in the TimeBaseInit.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  TimeBaseInit: pointer to a PWM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for
  *         the specified PWM peripheral.
  * @retval None
  */
void PWM_TimeBaseInit(PWM_TypeDef* PWMx, PWM_TimeBaseInitTypeDef* TimeBaseInit)
{
	u32  tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_ClockSource(TimeBaseInit->PWM_ClockSource));
	assert_param(IS_PWM_Direction(TimeBaseInit->PWM_Direction));
	assert_param(IS_PWM_CenterAlignedMode(TimeBaseInit->PWM_CenterAlignedMode));
	/* Set the counter reload value */
	PWMx->ARR = TimeBaseInit->PWM_AutoReloadValue;
	/* Set the PWM clcok  */
	tmpreg = PWMx->CR1;
	tmpreg &= TimeBaseInit_CR1_MASK;
	tmpreg |=  (TimeBaseInit->PWM_ClockSource | TimeBaseInit->PWM_Direction | TimeBaseInit->PWM_CenterAlignedMode);
	PWMx->CR1 = tmpreg;
	/* Set the Prescaler value */
	PWMx->PSC = TimeBaseInit->PWM_Prescaler;
}

/**
  * @brief  Fills each TimeBaseInit member with its default value.
  * @param  TimeBaseInit: pointer to a PWM_TimeBaseInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void PWM_TimeBaseStructInit(PWM_TimeBaseInitTypeDef* TimeBaseInit)
{
	/* Set the default configuration */
	TimeBaseInit->PWM_AutoReloadValue = 0xFFFF;
	TimeBaseInit->PWM_ClockSource = PWM_ClockSource_PCLK;
	TimeBaseInit->PWM_Prescaler = 0x0000;
	TimeBaseInit->PWM_Direction = PWM_Direction_Up;
	TimeBaseInit->PWM_CenterAlignedMode = PWM_CenterAlignedMode_Disable;
}

/**
  * @brief  Initializes the PWMx peripheral output compare function according to
  *         the specified parameters in the OutInit.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  OutInit: pointer to a PWM_OCInitTypeDef
  *         structure that contains the configuration information for
  *         the specified PWM peripheral.
  * @retval None
  */
void PWM_OCInit(PWM_TypeDef* PWMx, PWM_OCInitTypeDef* OutInit)
{
	u8 ch = 0;
	u32 tmpreg1 = 0;
	u32 tmpreg2 = 0;
	u32 tmpreg3 = 0;
	u32 tmpreg4 = 0;
	u32 tmpreg5= 0;
	
	PWM_OCInitTypeDef tmpreg;
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_Channel(OutInit->PWM_Channel));
	assert_param(IS_PWM_OCMode(OutInit->PWM_OCMode));
	assert_param(IS_PWM_OCIdleState(OutInit->PWM_OCIdleState));
	assert_param(IS_PWM_OCNIdleState(OutInit->PWM_OCNIdleState));
	assert_param(IS_PWM_OCOutput(OutInit->PWM_OCOutput));
	assert_param(IS_PWM_OCNOutput(OutInit->PWM_OCNOutput));
	assert_param(IS_PWM_OCPolarity(OutInit->PWM_OCPolarity));
	assert_param(IS_PWM_OCNPolarity(OutInit->PWM_OCNPolarity));

	ch = OutInit->PWM_Channel;
	/* Set the CHx Compare value */    
	tmpreg = *OutInit;

	tmpreg1=PWMx->OCMR;
	tmpreg2=PWMx->CR3;
	
	tmpreg3=(tmpreg.PWM_OCIdleState|tmpreg.PWM_OCNIdleState |tmpreg.PWM_OCOutput|tmpreg.PWM_OCNOutput);
	tmpreg3=(tmpreg3<<ch);
  tmpreg4=(tmpreg.PWM_OCPolarity |tmpreg.PWM_OCNPolarity);
  tmpreg4=(tmpreg4<<(ch*4));
	tmpreg5=(tmpreg.PWM_OCMode<<(ch*4));
	tmpreg3|=tmpreg5;
			
	if(ch == PWM_Channel_1)
	{
		tmpreg1&=Init_OCMRCH1_MASK;
		tmpreg2&=Init_CR3CH1_MASK;
		PWMx->OCR1 = OutInit->PWM_OCValue;
	}
	else if(ch == PWM_Channel_2)
	{ 
		tmpreg1&=Init_OCMRCH2_MASK;
		tmpreg2&=Init_CR3CH2_MASK;
		PWMx->OCR2 = OutInit->PWM_OCValue;
	}
	else if(ch == PWM_Channel_3)
	{
		tmpreg1&=Init_OCMRCH3_MASK;
		tmpreg2&=Init_CR3CH3_MASK;
		PWMx->OCR3 = OutInit->PWM_OCValue;
	}
	else if(ch == PWM_Channel_4)
	{
		tmpreg1&=Init_OCMRCH4_MASK;
		tmpreg2&=Init_CR3CH4_MASK;
		PWMx->OCR4 = OutInit->PWM_OCValue;
	}
	tmpreg1|=tmpreg3;
	tmpreg2|=tmpreg4;
	PWMx->OCMR=tmpreg1;
	PWMx->CR3=tmpreg2;
}

/**
  * @brief  Fills each OutInit member with its default value.
  * @param  OutInit: pointer to a PWM_OCInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void PWM_OCStructInit(PWM_OCInitTypeDef* OutInit)
{
	/* Set the default configuration */
	OutInit->PWM_OCMode=TIM_OCMode_Timing;
	OutInit->PWM_OCIdleState=PWM_OCIdleState_High;
	OutInit->PWM_OCNIdleState=PWM_OCNIdleState_High;
	OutInit->PWM_OCOutput=PWM_OCOutput_Enable;
	OutInit->PWM_OCNOutput=PWM_OCNOutput_Enable;
	OutInit->PWM_OCPolarity=PWM_OCPolarity_High;
	OutInit->PWM_OCNPolarity=PWM_OCNPolarity_Low;
}

/**
  * @brief  Initializes the PWMx peripheral input capture function according to
  *         the specified parameters in the CapInit.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  CapInit: pointer to a PWM_ICInitTypeDef
  *         structure that contains the configuration information for
  *         the specified PWM peripheral.
  * @retval None
  */
void PWM_ICInit(PWM_TypeDef* PWMx, PWM_ICInitTypeDef* CapInit)
{
	u8 ch = 0;
	u32 tmpreg1 = 0;	
	u32 tmpreg2 = 0;	
	PWM_ICInitTypeDef tmpreg;
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_Channel(CapInit->PWM_Channel));
	assert_param(IS_PWM_ICRiseCapture(CapInit->PWM_ICRiseCapture));
	assert_param(IS_PWM_ICFallCapture(CapInit->PWM_ICFallCapture));
	assert_param(IS_PWM_ICResetCounter(CapInit->PWM_ICResetCounter));
	assert_param(IS_PWM_ICSource(CapInit->PWM_ICSource));

	ch=CapInit->PWM_Channel;
	tmpreg = *CapInit;   
	tmpreg1=PWMx->CAPR;
	
	tmpreg2=(tmpreg.PWM_ICRiseCapture|tmpreg.PWM_ICFallCapture |tmpreg.PWM_ICResetCounter|tmpreg.PWM_ICSource);
	tmpreg2=(tmpreg2<<(ch*4));
	
	if(ch == PWM_Channel_1)
	{
		tmpreg1&=Init_CAPRCH1_MASK;
	}
	else if(ch == PWM_Channel_2)
	{
		tmpreg1&=Init_CAPRCH2_MASK;
	}
	else if(ch == PWM_Channel_3)
	{
		tmpreg1&=Init_CAPRCH3_MASK;
	}
	else if(ch == PWM_Channel_4)
	{
		tmpreg1&=Init_CAPRCH4_MASK;
	}
	
	tmpreg1|=tmpreg2;
	PWMx->CAPR=tmpreg1;
}
/**
  * @brief  Fills each CapInit member with its default value.
  * @param  CapInit: pointer to a PWM_ICInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void PWM_ICStructInit(PWM_ICInitTypeDef* CapInit)
{
	/* Set the default configuration */
	CapInit->PWM_Channel = PWM_Channel_1;
	CapInit->PWM_ICRiseCapture = PWM_ICRiseCapture_Enable;
	CapInit->PWM_ICFallCapture = PWM_ICFallCapture_Enable;
	CapInit->PWM_ICResetCounter = PWM_ICResetCounter_Enable;
	CapInit->PWM_ICSource = PWM_ICSource_ICS1;
}

/**
  * @brief  Initializes the PWMx peripheral brake and dead time function according to
  *         the specified parameters in the BDTRInit.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  BDTRInit: pointer to a PWM_BDTRInitTypeDef
  *         structure that contains the configuration information for
  *         the specified PWM peripheral.
  * @retval None
  */
void PWM_BDTRInit(PWM_TypeDef* PWMx, PWM_BDTRInitTypeDef* BDTRInit)
{
	u32 tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_DeadTime(BDTRInit->PWM_DeadTime));
	assert_param(IS_PWM_Break(BDTRInit->PWM_Break));
	assert_param(IS_PWM_BreakPolarity(BDTRInit->PWM_BreakPolarity));
	assert_param(IS_PWM_BreakSoftwareControl(BDTRInit->PWM_BreakSoftwareControl));
	assert_param(IS_PWM_BreakInput(BDTRInit->PWM_BreakInput));
  assert_param(IS_PWM_BreakSource(BDTRInit->PWM_BreakSource));
  
	tmpreg = PWMx->BDTR;
	tmpreg &= (u32)(~Init_BDTR_MASK);
	tmpreg |= (BDTRInit->PWM_DeadTime |\
	       BDTRInit->PWM_Break |\
			   BDTRInit->PWM_BreakPolarity |\
			   BDTRInit->PWM_BreakSoftwareControl |\
			   BDTRInit->PWM_BreakInput);
	
	PWMx->BDTR = tmpreg;
	tmpreg = PWMx->BKICR;
	tmpreg &=Init_BKICR_MASK;
	tmpreg |= (BDTRInit->PWM_BreakSource);
	PWMx->BKICR = tmpreg;    
}

/**
  * @brief  Fills each BDTRInit member with its default value.
  * @param  BDTRInit: pointer to a PWM_BDTRInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void PWM_BDTRStructInit(PWM_BDTRInitTypeDef* BDTRInit,u32 DeadTime)
{
	/* Set the default configuration */
	BDTRInit->PWM_DeadTime=DeadTime;
	BDTRInit->PWM_Break = PWM_Break_Enable;
	BDTRInit->PWM_BreakPolarity = PWM_BreakPolarity_Low;
	BDTRInit->PWM_BreakSoftwareControl = PWM_BreakSoftwareControl_Disable;
	BDTRInit->PWM_BreakInput = PWM_BreakInput_TIMIdle;
  BDTRInit->PWM_BreakSource = NULL;
}

/**
  * @brief  Set interrupt auto reload value for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  value: TIM interrupt auto reload value.
  * @retval None
  */
void PWM_SetInterruptAutoreload(PWM_TypeDef* PWMx, u8 value)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_RepeatTimes(value) );
	/* Set the PWM INT_RepeatTimes */
	PWMx->ITARR = value;
}

/**
  * @brief  Set auto reload value for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  value: Auto reload value.
  * @retval None
  */
void PWM_SetAutoreload(PWM_TypeDef* PWMx, u16 value)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	PWMx->ARR = value;
}

/**
  * @brief  Set value of Prescaler for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  value: Prescaler value.
  * @retval None
  */
void PWM_SetPrescaler(PWM_TypeDef* PWMx, u16 value)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	PWMx->PSC = value;
}

/**
  * @brief  Set value of output compare for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  value: output compare value.
  * @retval None
  */
void PWM_SetOCxValue(PWM_TypeDef* PWMx, u8 PWM_Channel, u16 value)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_Channel(PWM_Channel));
	if(PWM_Channel== PWM_Channel_1)	PWMx->OCR1 = value;
	if(PWM_Channel == PWM_Channel_2)	PWMx->OCR2 = value;
	if(PWM_Channel == PWM_Channel_3)	PWMx->OCR3 = value;
	if(PWM_Channel == PWM_Channel_4)	PWMx->OCR4 = value;
}

/**
  * @brief  Set value of input capture for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  value: input capture value.
  * @retval None
  */
void PWM_SetICxValue(PWM_TypeDef* PWMx, u8 PWM_Channel, u16 value)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_Channel(PWM_Channel));
	if(PWM_Channel== PWM_Channel_1)	PWMx->ICR1 = value;
	if(PWM_Channel == PWM_Channel_2)	PWMx->ICR2 = value;
	if(PWM_Channel == PWM_Channel_3)	PWMx->ICR3 = value;
	if(PWM_Channel == PWM_Channel_4)	PWMx->ICR4 = value;
}


/**
  * @brief  Get value of input capture channel for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  PWM_Channel: the input capture channel of PWM peripheral.
	*          This parameter can be one of the following values:
  *        @arg PWM_Channel_1: input capture channel 1 of PWM peripheral
  *        @arg PWM_Channel_2: input capture channel 2 of PWM peripheral
  *        @arg PWM_Channel_3: input capture channel 3 of PWM peripheral
  *        @arg PWM_Channel_4: input capture channel 4 of PWM peripheral
  * @retval the value of input capture channel 
  */
u16 PWM_GetICxValue(PWM_TypeDef* PWMx, u8 PWM_Channel)
{
	u16 value=0;
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_Channel(PWM_Channel));
	if(PWM_Channel== PWM_Channel_1)	value=PWMx->ICR1;
	if(PWM_Channel == PWM_Channel_2)	value=PWMx->ICR2;
	if(PWM_Channel == PWM_Channel_3)	value=PWMx->ICR3;
	if(PWM_Channel == PWM_Channel_4)	value=PWMx->ICR4;
	return value;
}

/**
  * @brief  Get counter value for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @retval counter value 
  */
u16 PWM_GetCounter(PWM_TypeDef* PWMx)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	return PWMx->CNT;
}

/**
  * @brief  Get auto reload value for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @retval auto reload value 
  */
u16 PWM_GetAutoreload(PWM_TypeDef* PWMx)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	return PWMx->ARR;
}

/**
  * @brief  Get prescaler value for PWM peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @retval prescaler value 
  */
u16 PWM_GetPrescaler(PWM_TypeDef* PWMx)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	return PWMx->PSC;
}

/**
  * @brief  Configures the PWMx event to be generate by software.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  PWM_EventSource: specifies the event source.
  *   This parameter can be one or more of the following values:
  *     @arg PWM_EventSource_Update: Timer update Event source
  *     @arg PWM_EventSource_Break: Timer Break event source
  * @retval None
  */
void PWM_GenerateEvent(PWM_TypeDef* PWMx,u32 PWM_EventSource)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_EventSource(PWM_EventSource));
	if(PWM_EventSource==PWM_EventSource_Update)
	{
		PWMx->CR1 |= PWM_CR1_UG;
	}
	if(PWM_EventSource==PWM_EventSource_Break)
	{
		PWMx->BDTR |= PWM_BDTR_BKSC;
	}
}

/**
  * @brief  Enable or Disable PWMx peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  NewState: new state of the PWMx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWM_Cmd(PWM_TypeDef* PWMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState == ENABLE)
	{
		/* Set the update bit */
		PWMx->CR1 |= PWM_CR1_EN;
	}
	else
	{
		/* Reset the update bit */
		PWMx->CR1 &= (~PWM_CR1_EN);
	}
}

/**
  * @brief  Enables or disables the specified PWM interrupts.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  PWM_IT: Specify the TIM interrupts sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *        @arg PWM_IT_ARI: Auto reload interrupt
  *        @arg PWM_IT_OC1I: output compare 1 interrupt
  *        @arg PWM_IT_OC2I: output compare 2 interrupt
  *        @arg PWM_IT_OC3I: output compare 3 interrupt
  *        @arg PWM_IT_OC4I: output compare 4 interrupt
  *        @arg PWM_IT_IC1I: input capture 1 interrupt 
  *        @arg PWM_IT_IC2I: input capture 2 interrupt 
  *        @arg PWM_IT_IC3I: input capture 3 interrupt 
  *        @arg PWM_IT_IC4I: input capture 4 interrupt 
  *        @arg PWM_IT_BKI: break interrupt 
  *        @arg PWM_IT_UIE: update interrupt
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void PWM_ITConfig(PWM_TypeDef* PWMx, u32 PWM_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_IT(PWM_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if((PWM_IT == PWM_IT_ARI) | (PWM_IT == PWM_IT_OC1I) | (PWM_IT == PWM_IT_OC2I) | (PWM_IT == PWM_IT_OC3I) | (PWM_IT == PWM_IT_OC4I) | (PWM_IT == PWM_IT_UI))
	{
        if(PWM_IT == PWM_IT_IC1I)
        {
            if (NewState != DISABLE)
            {
                /* Enable the interrupt sources */
                PWMx->CR2 |= PWM_CAPR_IC1I;
            }
            else
            {
                /* Disable the interrupt sources */
                PWMx->CR2 &= ~PWM_CAPR_IC1I;
            }
        }
        else
        {
            if (NewState != DISABLE)
            {
                /* Enable the interrupt sources */
                PWMx->CR2 |= PWM_IT;
            }
            else
            {
                /* Disable the interrupt sources */
                PWMx->CR2 &= ~PWM_IT;
            }
        }		
	}
	if(PWM_IT == PWM_IT_BKI)
	{
		if (NewState != DISABLE)
		{
			/* Enable the interrupt sources */
			PWMx->BDTR |= PWM_IT;
		}
		else
		{
			/* Disable the interrupt sources */
			PWMx->BDTR &= ~PWM_IT;
		}
	}
	if((PWM_IT == PWM_IT_IC1I) | (PWM_IT == PWM_IT_IC2I) | (PWM_IT == PWM_IT_IC3I) | (PWM_IT == PWM_IT_IC4I))
	{
		if (NewState != DISABLE)
		{
			/* Enable the interrupt sources */
			PWMx->CAPR |= PWM_IT;
		}
		else
		{
			/* Disable the interrupt sources */
			PWMx->CAPR &= ~PWM_IT;
		}
	}
}

/**
  * @brief  Checks whether the specified PWM flag is set or not.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  PWM_FLAG: Specify the flag to be checked.
  *         This parameter can be one of the following values:
  *         @arg PWM_FLAG_ARF: auto reload flag
  *         @arg PWM_FLAG_OC1F: output compare 1 flag
  *         @arg PWM_FLAG_OC2F: output compare 2 flag
  *         @arg PWM_FLAG_OC3F: output compare 3 flag
  *         @arg PWM_FLAG_OC4F: output compare 4 flag
  *         @arg PWM_FLAG_IC1R: input capture 1 rising edge flag
  *         @arg PWM_FLAG_IC1F: input capture 1 falling edge flag
  *         @arg PWM_FLAG_IC2R: input capture 2 rising edge flag
  *         @arg PWM_FLAG_IC3F:	input capture 2 falling edge flag
  *         @arg PWM_FLAG_IC3R: input capture 3 rising edge flag
  *         @arg PWM_FLAG_IC3F:	input capture 3 falling edge flag
  *         @arg PWM_FLAG_IC4R: input capture 4 rising edge flag
  *         @arg PWM_FLAG_IC4F:	input capture 4 falling edge flag
  *         @arg PWM_FLAG_BIF: break input flag
  *         @arg PWM_FLAG_TIF: trigger input flag
  *         @arg PWM_FLAG_UF: update flag
  * @return FlagStatus of PWM_FLAG (SET or RESET).
  */
FlagStatus PWM_GetFlagStatus(PWM_TypeDef* PWMx, u32 PWM_FLAG)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_FLAG(PWM_FLAG));
	if ((PWMx->SR & PWM_FLAG) != RESET)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
  * @brief  Clears the PWM's pending flags.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  PWM_FLAG: Specify the flag to be checked.
  *         This parameter can be one of the following values:
  *         @arg PWM_FLAG_ARF: auto reload flag
  *         @arg PWM_FLAG_OC1F: output compare 1 flag
  *         @arg PWM_FLAG_OC2F: output compare 2 flag
  *         @arg PWM_FLAG_OC3F: output compare 3 flag
  *         @arg PWM_FLAG_OC4F: output compare 4 flag
  *         @arg PWM_FLAG_IC1R: input capture 1 rising edge flag
  *         @arg PWM_FLAG_IC1F: input capture 1 falling edge flag
  *         @arg PWM_FLAG_IC2R: input capture 2 rising edge flag
  *         @arg PWM_FLAG_IC3F:	input capture 2 falling edge flag
  *         @arg PWM_FLAG_IC3R: input capture 3 rising edge flag
  *         @arg PWM_FLAG_IC3F:	input capture 3 falling edge flag
  *         @arg PWM_FLAG_IC4R: input capture 4 rising edge flag
  *         @arg PWM_FLAG_IC4F:	input capture 4 falling edge flag
  *         @arg PWM_FLAG_BIF: break input flag
  *         @arg PWM_FLAG_TIF: trigger input flag
  *         @arg PWM_FLAG_UF: update flag
  * @retval None
  */
void PWM_ClearFlag(PWM_TypeDef* PWMx, u32 PWM_FLAG)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_FLAG(PWM_FLAG));
	/* Clear the flags */
	PWMx->SR = PWM_FLAG;
}

/**
  * @brief  Enable the ADC trigger function for PWMx peripheral.
  * @param  PWMx: where x can be TIM1, TIM5 , TIM6 or TIM7 to select the PWM peripheral
  * @param  ADCTrigger: the mode of ADC trigger.
  *         This parameter can be one of the following values:
  *         @arg PWM_ADCTrigger_OC1UE: OC1U trigger ADC enable
  *         @arg PWM_ADCTrigger_OC1DE: OC1D trigger ADC enable
  *         @arg PWM_ADCTrigger_OC2UE: OC2U trigger ADC enable
  *         @arg PWM_ADCTrigger_OC2DE: OC2D trigger ADC enable
  *         @arg PWM_ADCTrigger_OC3UE: OC3U trigger ADC enable
  *         @arg PWM_ADCTrigger_OC3DE: OC3D trigger ADC enable
  *         @arg PWM_ADCTrigger_OC4UE: OC4U trigger ADC enable
  *         @arg PWM_ADCTrigger_OC4DE: OC4D trigger ADC enable
  *         @arg PWM_ADCTrigger_UOAE: UpOVF trigger ADC enable
  *         @arg PWM_ADCTrigger_DOAE: DownOVF trigger ADC enable
  *         @arg PWM_ADCTrigger_IC1RAE: IC1R trigger ADC enable
  *         @arg PWM_ADCTrigger_IC1FAE: IC1F trigger ADC enable
  *         @arg PWM_ADCTrigger_IC2RAE: IC2R trigger ADC enable
  *         @arg PWM_ADCTrigger_IC2FAE: IC2F trigger ADC enable
	*         @arg PWM_ADCTrigger_IC3RAE: IC3R trigger ADC enable
  *         @arg PWM_ADCTrigger_IC3FAE: IC3F trigger ADC enable
	*         @arg PWM_ADCTrigger_IC4RAE: IC4R trigger ADC enable
  *         @arg PWM_ADCTrigger_IC4FAE: IC4F trigger ADC enable
  * @retval None
  */
void PWM_ADCTrigger(PWM_TypeDef* PWMx, u32 ADCTrigger)
{
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_PWM_ADCTrigger(ADCTrigger));
	PWMx->TACR |= ADCTrigger;
}

/**
  * @brief  Enable or Disable Software Break.
  * @param  PWMx
  * @param  NewState: new state of the PWMx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWM_SoftwareBreak_CMD(PWM_TypeDef *PWMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_PWM_ALL_PERIPH(PWMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState!=DISABLE)
	{
	  PWMx->BDTR|=PWM_BDTR_BKSC;
	}
	else
	{
	  PWMx->BDTR&=~PWM_BDTR_BKSC;	
	}
}



/**
  * @}
  */
