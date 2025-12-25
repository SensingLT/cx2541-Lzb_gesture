  /******************************************************************************
  * @file    PT32Y003x_wdg.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the Independent watchdog (IWDG) peripheral:
  *           + Prescaler and Counter configuration
  *           + IWDG activation
  *           + Flag management
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_wdg.h"

/** @defgroup WDG
  * @brief WDG driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Enable or Disable WDGx
  * @param  WDGx:select the WDG peripheral.
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void WDG_Cmd(IWDG_TypeDef* WDGx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the IWDG */
		WDGx->CR |= IWDG_CR_EN;
	}
	else
	{
		/* Disable the IWDG */
		WDGx->CR &= ~IWDG_CR_EN;
	}
}

void WDG_ResetCmd(IWDG_TypeDef* WDGx, FunctionalState NewState)
{
    	/* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the IWDG */
		WDGx->CR |= IWDG_CR_RSTE;
	}
	else
	{
		/* Disable the IWDG */
		WDGx->CR &= ~IWDG_CR_RSTE;
	}

}

/**
  * @brief  Enables or disables write access all registers.
  * @param  WDGx:select the WDG peripheral.
  * @param  SEL: new state of write access to all registers.
  *          This parameter can be one of the following values:
  *            @arg IWDG_LOCK_UnLock: Enable write access to all registers
  *            @arg IWDG_LOCK_Lock: Disable write access to all registers
  * @retval None
  */
void WDG_LockCmd(IWDG_TypeDef* WDGx, FunctionalState NewState)
{
    assert_param(IS_WDG_ALL_PERIPH(WDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
	{
		/* Enable the IWDG */
		WDGx->LOCK = IWDG_LockKey_Lock;
	}
	else
	{
		/* Disable the IWDG */
		WDGx->LOCK = IWDG_LockKey_UnLock;
	}
}

/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param  WDGx:select the WDG peripheral.
  * @param  IWDG_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg WDG_SR_HDF
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus WDG_GetFlagStatus(IWDG_TypeDef* WDGx, u32 WDG_FLAG)
{
	FlagStatus bitstatus = RESET;
	/* Check the parameters */
    assert_param(IS_WDG_ALL_PERIPH(WDGx));
	assert_param(IS_WDG_FLAG(WDG_FLAG));
	
    if(WDG_FLAG == WDG_FLAG_HungryDog)
    {
        if ((WDGx->SR & IWDG_SR_HDF) != (u32)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((WDGx->LOCK & IWDG_LOCK_LOCK) != (u32)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }        
    }
	return bitstatus;
}

/**
  * @brief  Sets IWDG Reload value.
  * @param  WDGx:select the WDG peripheral.
  * @param  Reload: specifies the IWDG Reload value.
  *          This parameter must be a number between 0 and 0xFFFFFFFF.
  * @retval None
  */
void WDG_SetReload(IWDG_TypeDef* WDGx, u32 Reload)
{
	/* Check the parameters */
    assert_param(IS_WDG_ALL_PERIPH(WDGx));
	WDGx->RLR = Reload;
}

/**
  * @brief  Reloads IWDG counter 
  * @param  WDGx:select the WDG peripheral.
  * @retval None
  */
void WDG_ReloadCounter(IWDG_TypeDef* WDGx)
{
	/* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));
	WDGx->KR = 1;
}

/**
  * @brief   Enables or disables the specified WDG DebugPending
  * @param  WDGx:select the WDG peripheral.
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void WDG_DBGPendingCmd(IWDG_TypeDef* WDGx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the IWDG RESET */
		WDGx->CR |= IWDG_CR_DBGE;
	}
	else
	{
		/* Disable the IWDG RESET*/
		WDGx->CR &= ~IWDG_CR_DBGE;
	}
}

/**
  * @}
  */


