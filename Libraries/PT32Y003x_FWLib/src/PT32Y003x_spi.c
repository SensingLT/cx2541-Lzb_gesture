  /******************************************************************************
  * @file    PT32Y003x_spi.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the Serial peripheral interface (SPI):
  *           + Initialization and Configuration
  *           + Data transfers functions
  *           + Interrupts and flags management
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
  
/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_spi.h"


/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Init_CR1_MASK   (u32)0xFFFF0030
#define Init_CSS_MASK   (u32)0xFFFFFFF3

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the SPIx  peripheral according to
  *            the specified parameters in the SPI_InitTypeDef.
  * @param  SPIx: select the PWM peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef
  *         structure that contains the configuration information for
  *         the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
	u32 tmpreg = 0;
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_MasterSlaveMode(SPI_InitStruct->SPI_MasterSlaveMode));
	assert_param(IS_SPI_DataFrameFormat(SPI_InitStruct->SPI_DataFrameFormat));
	assert_param(IS_SPI_ClockPolarity(SPI_InitStruct->SPI_ClockPolarity));
	assert_param(IS_SPI_ClockPhase(SPI_InitStruct->SPI_ClockPhase));
	assert_param(IS_SPI_CSS(SPI_InitStruct->SPI_CSS));
    assert_param(IS_SPI_SoftwareControlCSS(SPI_InitStruct->SPI_SoftwareControlCSS));
	assert_param(IS_SPI_BaudRate(SPI_InitStruct->SPI_BaudRate));

	tmpreg = SPIx->CR1;
	tmpreg &= Init_CR1_MASK;
	tmpreg |= (SPI_InitStruct->SPI_DataFrameFormat | SPI_InitStruct->SPI_ClockPolarity |
	                     SPI_InitStruct->SPI_ClockPhase | ((SPI_InitStruct->SPI_Prescaler)<<8));
	SPIx->CR1 = tmpreg;
    
	SPIx->CR2 &= ~SPI_CR2_MSM;
	SPIx->CR2 |= SPI_InitStruct->SPI_MasterSlaveMode;

	SPIx->BR = SPI_InitStruct->SPI_BaudRate;
	
	tmpreg = SPIx->CSS;
	tmpreg &= Init_CSS_MASK;
	tmpreg |= SPI_InitStruct->SPI_CSS | SPI_InitStruct->SPI_SoftwareControlCSS;
	SPIx->CSS = tmpreg;
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
	/*--------------- Reset SPI init structure parameters values -----------------*/
	/* Initialize the SPI_Mode member */
	SPI_InitStruct->SPI_MasterSlaveMode = SPI_MasterSlaveMode_Slave;
	/* Initialize the SPI_DataSize member */
	SPI_InitStruct->SPI_DataFrameFormat = SPI_DataFrameFormat_8b;
	/* Initialize the SPI_CPOL member */
	SPI_InitStruct->SPI_ClockPolarity = SPI_ClockPolarity_Low;
	/* Initialize the SPI_CPHA member */
	SPI_InitStruct->SPI_ClockPhase = SPI_ClockPhase_1Edge;
	/* Initialize the SPI_CSS member */
	SPI_InitStruct->SPI_CSS = SPI_CSS_HardwareControl;
    /* Initialize the SPI_SWCS member */
	SPI_InitStruct->SPI_SoftwareControlCSS = SPI_SoftwareControlCSS_High;
	/* Initialize the SPI_Prescaler member */
	SPI_InitStruct->SPI_Prescaler = 2;
	/* Initialize the SPI_BaudRatePrescaler member */
	SPI_InitStruct->SPI_BaudRate = 16;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: select the PWM peripheral.
  * @param  NewState: new state of the SPIx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the selected SPI peripheral */
		SPIx->CR2 |= SPI_CR2_EN;
	}
	else
	{
		/* Disable the selected SPI peripheral */
		SPIx->CR2 &= ~SPI_CR2_EN;
	}
}


/**
  * @brief  Configures internally by software the CS pin for the selected SPI.
  * @param  SPIx: select the PWM peripheral.
  * @param  SPI_SWCS_SEL: specifies the SPI CS internal state.
  *          This parameter can be one of the following values:
  *            @arg SPI_CSSInternalSoft_Set: Set CS pin internally
  *            @arg SPI_CSSInternalSoft_Reset: Reset CS pin internally
  * @retval None
  */
void SPI_SoftwareControlCSSConfig(SPI_TypeDef* SPIx, u32 SWCS_Signal)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_SoftwareControlCSS(SWCS_Signal));
	if (SWCS_Signal != SPI_SoftwareControlCSS_Low)
	{
		/* Set NSS pin internally by software */
		SPIx->CSS |= SPI_SoftwareControlCSS_High;
	}
	else
	{
		/* Reset NSS pin internally by software */
		SPIx->CSS &= ~SPI_SoftwareControlCSS_High;
	}
}


/**
  * @brief  Transmits a Data through the SPIx peripheral.
  * @param  SPIx: select the PWM peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_SendData(SPI_TypeDef* SPIx, u16 Data)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));

	/* Write in the DR register the data to be sent */
	SPIx->DR = Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx peripheral.
  * @param  SPIx: select the PWM peripheral.
  * @retval The value of the received data.
  */
u8 SPI_ReceiveData(SPI_TypeDef* SPIx)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));

	/* Return the data in the DR register */
	return SPIx->DR;
}


/**
  * @brief  Enables or disables the specified SPI interrupts.
  * @param  SPIx: select the PWM peripheral.
  * @param  SPI_IT: specifies the SPI interrupt source to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg SPI_IE_OVRE
  *            @arg SPI_IE_OTE
  *            @arg SPI_IE_RXHE
  *            @arg SPI_IE_TXHE
  * @param  NewState: new state of the specified SPI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_ITConfig(SPI_TypeDef* SPIx, u32 SPI_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_SPI_IT(SPI_IT));
	if (NewState != DISABLE)
	{
		/* Enable the selected SPI interrupt */
		SPIx->IE |= SPI_IT;
	}
	else
	{
		/* Disable the selected SPI interrupt */
		SPIx->IE &= ~SPI_IT;
	}
}

/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPIx: select the PWM peripheral.
  * @param  SPI_FLAG: specifies the SPI flag to check.
  *          This parameter can be one of the following values:
  *            @arg SPI_FLAG_TXE
  *            @arg SPI_FLAG_TNF
  *            @arg SPI_FLAG_RXNE
  *            @arg SPI_FLAG_RXF
  *            @arg SPI_FLAG_BSY
  *            @arg SPI_FLAG_OVR
  *            @arg SPI_FLAG_OT
  *            @arg SPI_FLAG_RXH
  *            @arg SPI_FLAG_TXH
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, u32 SPI_FLAG)
{
	FlagStatus bitstatus = RESET;
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_FLAG(SPI_FLAG));
	if(SPI_FLAG <= SPI_FLAG_OVR)
	{
        if(SPI_FLAG == SPI_FLAG_TXFS0)
        {
            if ((SPIx->SR1&SPI_SR1_TXFS) != SET)
            {
                /* */
                bitstatus = SET;
            }
            else
            {
                /* */
                bitstatus = RESET;
            }
        }
        else if(SPI_FLAG == SPI_FLAG_RXFS0)
        {
            if ((SPIx->SR1&SPI_SR1_RXFS) != SET)
            {
                /* */
                bitstatus = SET;
            }
            else
            {
                /* */
                bitstatus = RESET;
            }
        
        }
        else
        {
            if ((SPIx->SR1&SPI_FLAG) != RESET)
            {
                /* */
                bitstatus = SET;
            }
            else
            {
                /* */
                bitstatus = RESET;
            }
        }		
	}
	else
	{
		if ((SPIx->SR2&(SPI_FLAG&0xFFFEFFFF)) != RESET)
		{
			/* */
			bitstatus = SET;
		}
		else
		{
			/* */
			bitstatus = RESET;
		}
	}
	/*  */
	return  bitstatus;
}

/**
  * @brief  Clears the SPIx flag.
  * @param  SPIx: select the PWM peripheral.
  * @param  SPI_FLAG: Specify the flag to be cleared.
  *         This parameter can be one of the following values:
  *         @arg SPI_IFC_OVR
  *         @arg SPI_IFC_OT
  * @retval None
  */
void SPI_ClearFlag(SPI_TypeDef* SPIx, u32 SPI_FLAG)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_FLAG(SPI_FLAG));
    if(SPI_FLAG == SPI_FLAG_OVR)
    {
        SPI0->IC |= SPI_IC_OVR;
    }
    else if(SPI_FLAG == SPI_FLAG_OT)
    {
        SPI0->IC |= SPI_IC_OT;
    }
    else
    {}
}

void SPI_FifoReset(SPI_TypeDef* SPIx, u8 SPI_FIFO)
{
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_FIFO(SPI_FIFO));
	switch (SPI_FIFO)
	{
		case SPI_FIFO_RX :
			SPIx->RXFR = SPI_RXFR_RXFR;
			break;
		case SPI_FIFO_TX :
			SPIx->TXFR = SPI_TXFR_TXFR;
			break;
	}
}

/**
  * @}
  */
