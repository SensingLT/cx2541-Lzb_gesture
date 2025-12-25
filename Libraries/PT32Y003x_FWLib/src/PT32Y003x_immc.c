/******************************************************************************
  * @file    PT32Y003x_immc.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the IMMC peripheral:
  *           + Initialization and Configuration
  *           + Flash Erase and Read\Write Function
  *           + Interrupts and flags management
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_immc.h"


/** @defgroup IMMC
  * @brief IMMC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WriteWord_CR_MASK   (u32)0x0000FEFE
#define IMMC_TimeOut_Time  ((u32)0x00040000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Sets the IMMC Prescaler.
  * @param  Prescaler: specifies the IMMC PSC value.
  *		    This parameter must be less than 64 
  * @retval None
  */
void IMMC_SetPrescaler(u8 Prescaler)
{
	assert_param(IS_IMMC_Prescaler(Prescaler));
	/* Write the PSC register */
	IMMC->PSC =Prescaler;
}

FlagStatus IMMC_WaitIMMCFree(void)    
{
    u32 Timeout = IMMC_TimeOut_Time;
    FlagStatus bitstatus = RESET;
    while(IMMC_GetFlagStatus(IMMC_FLAG_BUSY) && (Timeout != 0x00))
	{
		Timeout--;
	}
    if(Timeout)
    {
         bitstatus = SET;
    }
    else
    {
         bitstatus = RESET;
    }
    
    return bitstatus; 
}

FlagStatus IMMC_WriteWord(u32 Address, u32 Data)
{
    u32 Timeout = IMMC_TimeOut_Time;
    FlagStatus bitstatus = RESET;
    u32 tmpreg = 0;
		u8 count=3;
 
    IMMC_WaitIMMCFree();
    tmpreg = IMMC->CR;	
    tmpreg &= WriteWord_CR_MASK;
    
		while(count>0)
		{   
			IMMC->AR = Address;
			IMMC->DR  = Data;
			if(Address < 0x00004000)
			{
				tmpreg |= (IMMC_Key_MainCode | IMMC_CR_STAR | IMMC_CR_MODE);
			}
			else if((Address >= 0x00004000)&&(Address<0x00004200))
			{
				tmpreg |= (IMMC_Key_EEPROM | IMMC_CR_STAR | IMMC_CR_MODE);
				count=1;
			}
			else if((Address >= 0x00004200)&&(Address<0x00004240))
			{
				tmpreg |= (IMMC_Key_INFO | IMMC_CR_STAR | IMMC_CR_MODE);
			}
			else
			{
				while(1);//get error address
			}
			IMMC->CR = tmpreg;
			count--;
		}
    while((!IMMC_GetFlagStatus(IMMC_FLAG_WOV)) && (Timeout != 0x00))
		{
			Timeout--;
		}
    if(Timeout)
    {
         bitstatus = SET;
    }
    else
    {
         bitstatus = RESET;
    }
    
    return bitstatus; 
}
    
/**
  * @brief  Read a word at a specified address.
  * @note
  * @note
  *
  * @param
  * @note
  *
  * @retval
  *
  */
u32 IMMC_ReadWord(u32 Address)
{
	return *(__IO u32*) Address;
}
/**
  * @brief  Read a half word at a specified address.
  * @note
  * @note
  *
  * @param
  * @param
  * @retval
  *
  */
u16 IMMC_ReadHalfWord(u32 Address)
{
	return *(__IO u16*) Address;
}

/**
  * @brief Read a Byte at a specified address.
  * @note
  * @note
  *
  * @param
  * @param
  * @retval
  *
  */
u8 IMMC_ReadByte(u32 Address)
{
	return *(__IO u8*) Address;
}


/**
  * @brief  Enables or disables the specified IMMC interrupts.
  * @param  IFMC_IT: specifies the IMMC interrupt sources to be enabled or
  *         disabled.
  *          This parameter can be any combination of the following values:
  *             @arg IFMC_IE_WOVI
  *             @arg IFMC_IE_POVI	  
  *             @arg IFMC_IE_COVI	 
  *             @arg IFMC_IE_CERI	
  *             @arg IFMC_IE_KERI	
  *             @arg IFMC_IE_AERI	
  * @retval None
  */
void IMMC_ITConfig(u32 IMMC_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_IMMC_IT(IMMC_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if(NewState != DISABLE)
	{
		/* Enable the interrupt sources */
		IMMC->IE |= IMMC_IT;
	}
	else
	{
		/* Disable the interrupt sources */
		IMMC->IE &= ~IMMC_IT;
	}
}

/**
  * @brief  Checks whether the specified IMMC flag is set or not.
  * @param  IMMC_FLAG: specifies the IMMC flag to check.
  *          This parameter can be one of the following values:
  *             @arg IMMC_FLAG_BSY: IMMC write/erase operations in progress flag
  *             @arg IMMC_FLAG_PGERR: IMMC Programming error flag flag
  *             @arg IMMC_FLAG_WRPERR: IMMC Write protected error flag
  *             @arg IMMC_FLAG_EOP: IMMC End of Programming flag
  * @retval The new state of IMMC_FLAG (SET or RESET).
  */
FlagStatus IMMC_GetFlagStatus(u32 IMMC_FLAG)
{
	FlagStatus bitstatus = RESET;
	assert_param(IS_IMMC_FLAG(IMMC_FLAG));  
    if(IMMC_FLAG == IMMC_FLAG_IAPF)
    {
        if((IMMC->BSR & IMMC_FLAG) != (u32)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else if(IMMC_FLAG == IMMC_FLAG_PSR)
    {
        if((IMMC->RPSR & (IMMC_FLAG&IMMC_RPSR_PSR)) != (u32)RESET)
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
        if((IMMC->SR & IMMC_FLAG) != (u32)RESET)
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
  * @brief  Clears the IMMC's pending flags.
  * @param  IMMC_FLAG: specifies the IMMC flags to clear.
  *          This parameter can be any combination of the following values:
  *             @arg IMMC_FLAG_WOV	IMMC 写命令完成标志
  *             @arg IMMC_FLAG_POV	IMMC块擦除命令完成标志
  *             @arg IMMC_FLAG_COV	IMMC解保护时擦除主程序完成标志
  *             @arg IMMC_FLAG_BUSY    IMMC操作命令错误标志
  *             @arg IMMC_FLAG_CERR   IMMC操作命令错误标志
  *             @arg IMMC_FLAG_KERR   IMMC操作命令错误标志
  *             @arg IMMC_FLAG_AERR    IMMC地址错误标志
  * @retval None
  */
void IMMC_ClearFlag(u32 IMMC_FLAG)
{
	/* Check the parameters */
	assert_param(IS_IMMC_FLAG(IMMC_FLAG));
    if(IMMC_FLAG==IMMC_FLAG_WOV  || IMMC_FLAG==IMMC_FLAG_CERR ||\
       IMMC_FLAG==IMMC_FLAG_KERR || IMMC_FLAG==IMMC_FLAG_AERR || IMMC_FLAG==IMMC_FLAG_WTO)
		{
        IMMC->SR = IMMC_FLAG;
    }
}

/**
  * @}
  */


