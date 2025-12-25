/******************************************************************************
  * @file    PT32Y003x_crc.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the CRC peripheral:
  *           + Initialization and Configuration
  *           + Interrupts and flags management
  *          
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_crc.h"

#define Init_CR_MASK	(u32)0xFFFFFFC3

/** @defgroup CRC
  * @brief CRC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the CRC peripheral according to the specified parameters
  *         in the CRC_InitStruct.
  * @param  CRC_InitStruct: pointer to an CRC_InitTypeDef structure that contains
  *         the configuration information for the specified CRC peripheral.
  * @retval None
  */
void CRC_Init(CRC_InitTypeDef* CRC_InitStruct)
{
	u32 tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_CRC_Input(CRC_InitStruct->CRC_Input));
	assert_param(IS_CRC_InputBitSequenceReversal(CRC_InitStruct->CRC_InputBitSequenceReversal));
	assert_param(IS_CRC_InputByteSequenceReversal(CRC_InitStruct->CRC_InputByteSequenceReversal));
	assert_param(IS_CRC_OutputBitSequenceReversal(CRC_InitStruct->CRC_OutputBitSequenceReversal));
	tmpreg = CRC->CR;
	tmpreg &= Init_CR_MASK;
	tmpreg  |= ((u32)(CRC_InitStruct->CRC_Input));
	tmpreg  |= ((u32)(CRC_InitStruct->CRC_InputBitSequenceReversal));
	tmpreg  |= ((u32)(CRC_InitStruct->CRC_InputByteSequenceReversal));
	tmpreg  |= ((u32)(CRC_InitStruct->CRC_OutputBitSequenceReversal));
	/* Write to CRC CR */
	CRC->CR = tmpreg;
	CRC->SEED = CRC_InitStruct->CRC_Seed;
	CRC->POLY = CRC_InitStruct->CRC_Poly;
}

/**
  * @brief  Fills each CRC_InitStruct member with its default value.
  * @param  CRC_InitStruct: pointer to an CRC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct)
{	
	/* Initialize the CRC data input width */
	CRC_InitStruct->CRC_Input = CRC_Input_16b;
	/* Initialize the CRC data input bit reverse function */
	CRC_InitStruct->CRC_InputBitSequenceReversal = CRC_InputBitSequenceReversal_Disable;
	/* Initialize the CRC data output bit reverse function */
	CRC_InitStruct->CRC_OutputBitSequenceReversal = CRC_OutputBitSequenceReversal_Disable;
	/* Initialize the CRC data input byte reverse function */
	CRC_InitStruct->CRC_InputByteSequenceReversal = CRC_InputByteSequenceReversal_Enable;
	/* Initialize the CRC POLY */
	CRC_InitStruct->CRC_Poly = CRC_PolyCCITT16;
	/* Initialize the CRC SEED */
	CRC_InitStruct->CRC_Seed = 0;
}


/**
  * @brief  Enables or disables the specified CRC peripheral.
  * @param  NewState: new state of the CRC peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRC_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the selected CRC peripheral */
		CRC->CR |= CRC_CR_EN;
	}
	else
	{
		/* Disable the selected CRC peripheral */
		CRC->CR &= ~CRC_CR_EN;
	}
}

/**
  * @brief   Resets the Data Out registers.
  * @retval None
  */
void CRC_ResetDout(void)
{
	CRC->CR |= CRC_CR_CRS;
}


/**
  * @brief  Computes the 16-bit CRC of a given 16-bit data. 
  * @param  CRC_Data: data half-word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
u32 CRC_CalculateCRC(u16 CRC_Data)
{
	CRC->DIN = (u16) CRC_Data;
	return (CRC->DOUT);
}


/**
  * @brief  Computes the 16-bit CRC of a given buffer of data word(16-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 16-bit CRC
  */
u32 CRC_CalculateBlockCRC(u16 pBuffer[], u32 BufferLength)
{
	u32 index = 0;
	for(index = 0; index < BufferLength; index++)
	{
		CRC->DIN = pBuffer[index];
	}
	return (CRC->DOUT);
}



/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @retval 16-bit CRC
  */
u32 CRC_GetCRC(void)
{
	return (CRC->DOUT);
}


/**
  * @}
  */

