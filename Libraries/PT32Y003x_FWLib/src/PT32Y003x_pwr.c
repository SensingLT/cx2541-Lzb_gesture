/******************************************************************************
  * @file    PT32X03x_pwr.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage Power Controller (PWR) peripheral
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_pwr.h"

/** @defgroup PWR
  * @brief PWR driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Config_PVDR_MASK              ((u32)0xFFFFFFF1)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_PVDLevel_0: Set level 0 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_1: Set level 1 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_2: Set level 2 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_3: Set level 3 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_4: Set level 4 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_5: Set level 5 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_6: Set level 6 as the PVD voltage threshold
  *             @arg PWR_PVDLevel_7: Set level 7 as the PVD voltage threshold
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void PWR_PVDLevelConfig(u32 PWR_PVDLevel)
{
	u32 tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_PWR_PVDLevel(PWR_PVDLevel));
	tmpreg = PWR->PVDR;
	/* Clear PLS[7:5] bits */
	tmpreg &= Config_PVDR_MASK;
	/* Set PLS[7:5] bits according to PWR_PVDLevel value */
	tmpreg |= PWR_PVDLevel;
	/* Store the new value */
	PWR->PVDR = tmpreg;
}

/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @param  NewState: new state of the PVD.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the PVD */
		PWR->PVDR |= PWR_PVDR_PVDE;
	}
	else
	{
		/* Disable the PVD */
		PWR->PVDR &= (u32)~((u32)PWR_PVDR_PVDE);
	}
}

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *             @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *             @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSleepMode(u8 PWR_SleepEntry)
{
	/* Check the parameters */
	assert_param(IS_PWR_SleepEntry(PWR_SleepEntry));
	/* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
	SCB->SCR &= (u32)~((u32)SCB_SCR_SLEEPDEEP_Msk);
	/* Select SLEEP mode entry */
	if(PWR_SleepEntry == PWR_SleepEntry_WFI)
	{
		/* Request Wait For Interrupt */
		__WFI();
	}
	else
	{
		/* Request Wait For Event */
		__SEV();
		__WFE();
		__WFE();
	}
}

/**
  * @brief  Enters DeepSleep mode.
  * @note   In DeepSleep mode, all I/O pins are high impedance except for:
  *          - Peripherals work on LSI clock.
  *          - The registers of the Core-M0, the memory information is still saved.
  *             @arg PWR_DeepSleepEntry_WFI: enter DEEPSLEEP mode with WFI instruction
  *             @arg PWR_DeepSleepEntry_WFE: enter DEEPSLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterDeepSleepMode(u8 PWR_DeepStandbyEntry)
{
	/* Check the parameters */
	assert_param(IS_PWR_DeepSleepEntry(PWR_DeepStandbyEntry));
	/* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	/* Select DEEPSLEEP mode entry */
	if(PWR_DeepStandbyEntry == PWR_DeepSleepEntry_WFI)
	{
		/* Request Wait For Interrupt */
		__WFI();
	}
	else
	{
		/* Request Wait For Event */
		__WFE();
		__WFE();
	}
}

/**
  * @}
  */
