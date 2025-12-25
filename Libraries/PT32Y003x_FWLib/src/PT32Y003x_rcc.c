  /******************************************************************************
  * @file    PT32x03x_rcc.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the SYS peripheral:
  *           + Initialization and Configuration
  *           + Interrupts and flags management
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_rcc.h"

/** @defgroup RCC
  * @brief RCC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Gets the value of clock frequence.
  * @param  RCC_Clock: specify the clock selection.
	*        @arg RCC_SYSCLK: Get the system clock frequence
	*        @arg RCC_HCLK: Get the AHB clock frequence
	*        @arg RCC_PCLK: Get the APB clock frequence
  * @retval Clock Frequent value
  */
u32 RCC_GetClockFreq(u8 RCC_Clock)
{
	u32 CLK_Freq;
	u32 SYSCLK;
	u32 HCLK_Freq;
	u32 HCLK_DIV;
	u32 PCLK_Freq;
	u32 PCLK_DIV;
	/* Check the parameters */
	assert_param(IS_RCC_Clock(RCC_Clock));
	SYSCLK = CLOCK_GetSYSCLK();
	if(RCC_Clock == RCC_SYSCLK)
	{
		CLK_Freq = SYSCLK;
	}
	else
	{
		HCLK_DIV = ((RCC->CFGR & RCC_CFGR_HPRE) >> 4) ;
		HCLK_Freq=SYSCLK/(HCLK_DIV+1);
		if(RCC_Clock == RCC_HCLK)
		{
			CLK_Freq = HCLK_Freq;
		}
		else
		{
			PCLK_DIV = ((RCC->CFGR & RCC_CFGR_PPRE) >> 24) ;
			PCLK_Freq = HCLK_Freq / (PCLK_DIV+1);
			CLK_Freq = PCLK_Freq;
		}
	}
	return CLK_Freq;
}

/**
 * @brief  Check whether the specific global reset flag is set or not.
 *  @param RCC_FLAG: specify the reset flag.
 *        This parameter can be:
 *        @arg RCC_FLAG_SFR: Software reset flag
 *        @arg RCC_FLAG_IWDG: Indepent watch dog reset flag
 *        @arg RCC_FLAG_CPU: CPU reset flag
 *        @arg RCC_FLAG_HSE: HSE fail reset flag
 *        @arg RCC_FLAG_POR: Power reset flag
 *        @arg RCC_FLAG_PVD: PVD low voltage reset flag
 *        @arg RCC_FLAG_PIN: Pin reset flag
 *        @arg RCC_FLAG_CWR: Configuration word reset flag
 *  @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(u32 RCC_FLAG)
{
	u32 tmpreg;
	/* Check the parameters */
	assert_param(IS_RCC_FLAG(RCC_FLAG));
    if(RCC_FLAG == RCC_FLAG_RDY)
    {
        tmpreg = (RCC->HSECR1 & (RCC_FLAG));
        if (tmpreg != RESET)
        {
            return SET;
        }
        else
        {
            return RESET;
        }     
    }   
    else if(RCC_FLAG == RCC_FLAG_HSEDE)
    {
        tmpreg = (RCC->CFGR & (RCC_FLAG));
        if (tmpreg != RESET)
        {
            return SET;
        }
        else
        {
            return RESET;
        }     
    } 
    else
    {
        tmpreg = (RCC->RSR & (RCC_FLAG));
        if (tmpreg != RESET)
        {
            return SET;
        }
        else
        {
            return RESET;
        }  
    }	
}

/**
 * @brief  Clear the specific global reset flag.
 * @param RCC_FLAG: specify the reset flag.
 *        This parameter can be:
 *        @arg RCC_FLAG_SFR: Software reset flag
 *        @arg RCC_FLAG_IWDG: Indepent watch dog reset flag
 *        @arg RCC_FLAG_CPU: CPU reset flag
 *        @arg RCC_FLAG_HSE: HSE fail reset flag
 *        @arg RCC_FLAG_POR: Power reset flag
 *        @arg RCC_FLAG_PVD: PVD low voltage reset flag
 *        @arg RCC_FLAG_PIN: Pin reset flag
 *        @arg RCC_FLAG_CWR: Configuration word reset flag
 *        @arg RCC_FLAG_ALL: All flags above
 * @retval None
  */
void RCC_ClearFlag(u32 RCC_FLAG)
{
	assert_param(IS_RCC_FLAG(RCC_FLAG));
	if(RCC_FLAG==RCC_FLAG_SFR || RCC_FLAG==RCC_FLAG_IWDG   ||\
		 RCC_FLAG==RCC_FLAG_CPU || RCC_FLAG==RCC_FLAG_HSE  ||\
		 RCC_FLAG==RCC_FLAG_PVD || RCC_FLAG==RCC_FLAG_POR  || RCC_FLAG==RCC_FLAG_PIN)
    {	
        RCC->RSR |= RCC_FLAG; 
    }		
}

/**
  * @brief  Enables or disables the specified Reset Source.
  * @param  ResetSource: specifies the Reset source to be enabled or disabled.
  *          This parameter can be one of the following values:
	*        @arg RCC_ResetEnable_PDRE: the new state of PVD low voltage reset enable
  * @param  NewState: new state of the specified Reset Source
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ResetConfig(u32 ResetSource, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_RCC_ResetEnable(ResetSource));
	if (NewState != DISABLE)
	{
		RCC->RCR |= ResetSource;
	}
	else
	{
		RCC->RCR &= ~(ResetSource);
	}
}

/**
  * @brief  Enables or disables the specified clock source
  * @param  ClockSource: specifies the clock source to be enabled or disabled.
  *         This parameter can be one of the following values:
  *         @arg RCC_ClockSource_HSE: Specify the new state of Extern High Crystal
  *         @arg RCC_ClockSource_HSEExternal: Specify the new state of Extern High Clock
  *         @arg RCC_ClockSource_PLL: Specify the new state of Phase Locked Loop
  *         @arg RCC_ClockSource_HSI: Specify the new state of Internal High Crystal
  *         @arg RCC_ClockSource_LSI: Specify the new state of Internal Low Crystal
	* @param  NewState: new state of the specified Reset Source
  *          This parameter can be: ENABLE or DISABLE.
  *         @return None
  */
void RCC_ClockSourceConfig(u32 ClockSource, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_ClockSource(ClockSource));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		if(ClockSource == RCC_ClockSource_HSE)
		{
			RCC->HSECR1&=~RCC_HSECR1_ECEN;
			RCC->HSECR1 |= RCC_HSECR1_EN;
			while(((RCC->HSECR1) & (RCC_HSECR1_RDY)) != RCC_HSECR1_RDY);
		}
		if(ClockSource == RCC_ClockSource_HSEExternal)
		{
			RCC->HSECR1&=~RCC_HSECR1_EN;
			RCC->HSECR1|=RCC_HSECR1_ECEN;
		}
		if(ClockSource == RCC_ClockSource_PLL)		RCC->PCR 	|= RCC_PCR_EN;
		if(ClockSource == RCC_ClockSource_HSI)		RCC->HSICR 	|= RCC_HSICR_EN;
		if(ClockSource == RCC_ClockSource_LSI)		RCC->LSICR 	|= RCC_LSICR_EN;
	}
	else
	{
		if(ClockSource == RCC_ClockSource_HSE)			RCC->HSECR1 &= ~RCC_HSECR1_EN;
		if(ClockSource == RCC_ClockSource_HSEExternal)	RCC->HSECR1 &= ~RCC_HSECR1_ECEN;
		if(ClockSource == RCC_ClockSource_PLL)		RCC->PCR 		&= ~RCC_PCR_EN;
		if(ClockSource == RCC_ClockSource_HSI)		RCC->HSICR 	&= ~RCC_HSICR_EN;
		if(ClockSource == RCC_ClockSource_LSI)		RCC->LSICR 	&= ~RCC_LSICR_EN;
	}
}

/**
  * @brief  Generate advanced software reset.
	* @param  RCC_AdvancedSoftwareResetSource: specifies the advancedSoftware reset source to be selected.
  *          This parameter can be one of the following values:
	*        @arg RCC_AdvancedSoftwareReset_CWR: generate CWR reset
	*        @arg RCC_AdvancedSoftwareReset_CPU: generate CPU reset
  * @retval None
  */
void RCC_AdvancedSoftwareReset(u8 RCC_AdvancedSoftwareResetSource)
{
	assert_param(IS_RCC_AdvancedSoftwareRese(RCC_AdvancedSoftwareResetSource));
	if(RCC_AdvancedSoftwareResetSource == RCC_AdvancedSoftwareReset_CWR)
	{
		RCC->ASFCR |= RCC_KEY_CWR;
	}
	else
	{
		RCC->ASFCR |= RCC_KEY_CPU;
	}
}

/**
  * @brief  Configures the AHB Clock Prescaler.
  * @param  Prescaler: specifies the Prescaler value (0~31)
  * @retval None
  */
void RCC_HCLKSetPrescaler(u32 Prescaler)
{
	/* Check the parameters */
	assert_param(IS_RCC_HCLKPrescaler(Prescaler));
	RCC->CFGR &= ~(RCC_CFGR_HPRE);
	RCC->CFGR |= ((Prescaler) << 4);
}

/**
  * @brief  Configures the APB Clock Prescaler.
  * @param  Prescaler: specifies the Prescaler value (0~31)
  * @retval None
  */
void RCC_PCLKSetPrescaler(u32 Prescaler)
{
	/* Check the parameters */
	assert_param(IS_RCC_PCLKPrescaler(Prescaler));
	RCC->CFGR &= ~(RCC_CFGR_PPRE);
	RCC->CFGR |= ((Prescaler) << 24);
}

/**
  * @brief  Get the selection of system clock.
  * @retval System Clock Selection
  *         @arg RCC_SystemClock_HSE: Select Extern High Crystal as  System Clock.
  *         @arg RCC_SystemClock_PLL: Select Phase Locked Loop as  System Clock.
  *         @arg RCC_SystemClock_HSI: Select Internal High Crystal as  System Clock.
  */
u8 RCC_GetSystemClockSelection(void)
{
	u8 SystemClockSelection;
	SystemClockSelection = (RCC->CFGR & 0x03);
	return SystemClockSelection;
}

/**
  * @brief  Set system clock after wake-up.
  * @param  Clock: specified the system clock after wake-up.
  *         @arg RCC_SystemClockAfterWakeUp_HSI: Set HSI clock as system clock after wake-up
  *         @arg RCC_SystemClockAfterWakeUp_PreviousClock: Set the clock before MCU sleep as system clock after wake-up
  * @retval None
  */
void RCC_SetSystemClockAfterWakeUp(u32 Clock)
{
	assert_param(IS_RCC_SystemClockAfterWakeUp(Clock));
	if (Clock != RCC_SystemClockAfterWakeUp_HSI)
	{
		RCC->CFGR |= RCC_CFGR_WKCK;
	}
	else
	{
		RCC->CFGR &= ~(RCC_CFGR_WKCK);
	}
}

/**
  * @brief  Set the source for clock output.
  * @param  ClockSource: the selection of Clock Output Source.
  *         @arg RCC_ClockOutput_HSI: Select HSI clock as the clock output source
	*         @arg RCC_ClockOutput_HSE: Select HSE clock as the clock output source
	*         @arg RCC_ClockOutput_PLL: Select PLL clock as the clock output source
  *         @arg RCC_ClockOutput_LSI: Select LSI clock as the clock output source
	*         @arg RCC_ClockOutput_SYS: Select System clock as the clock output source
	*         @arg RCC_ClockOutput_None: None clock output
  * @retval None
  */
void RCC_SetMCOSource(u32 MCOkSource)
{
	assert_param(IS_RCC_ClockOutputSource(MCOkSource));
	RCC->MCOR &= (~RCC_MCOR_COS);
	RCC->MCOR |= MCOkSource;
}

/**
  * @brief  Set the system clock.
  * @param  ClockSource: the selection of Clock Output Source.
  *         @arg RCC_SystemClock_HSI: Select HSI clock as the system clock
	*         @arg RCC_SystemClock_HSE: Select HSE clock as the system clock
	*         @arg RCC_SystemClock_PLL: Select PLL clock as the system clock
  * @retval None
  */
void RCC_SetSystemClock(u32 SystemClock)
{
	assert_param(IS_RCC_SystemClock(SystemClock));
	RCC->CFGR &= ~(RCC_CFGR_SCW);
	RCC->CFGR |= SystemClock;
}

/**
  * @brief  Set the value of prescaler for clock output.
  * @param  PrescaleSelcection: the selection of clock output prescaler.
  *         @arg RCC_ClockOutputPrescale_None : None Prescale the clock output frequency
	*         @arg RCC_ClockOutputPrescale_2: Prescale the clock output frequency into 1/2
	*         @arg RCC_ClockOutputPrescale_4:	Prescale the clock output frequency into 1/4
  *         @arg RCC_ClockOutputPrescale_8: Prescale the clock output frequency into 1/8
  *         @arg RCC_ClockOutputPrescale_16: Prescale the clock output frequency into 1/16
  * @retval None
  */
void RCC_MCOSetPrescaler(u32 PrescaleSelcection)
{
	assert_param(IS_RCC_ClockOutputPrescale(PrescaleSelcection));
	RCC->MCOR &= (~RCC_MCOR_COPRE);
	RCC->MCOR |= PrescaleSelcection;
}
/**
  * @}
  */
