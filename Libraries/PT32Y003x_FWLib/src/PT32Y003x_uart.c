  /******************************************************************************
  * @file    PT32Y003x_uart.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the Universal synchronous asynchronous receiver
  *          transmitter (USART):
  *           + Initialization and Configuration
  *           + STOP Mode
  *           + BaudRate
  *           + Data transfers
  *           + Multi-Processor Communication
  *           + Half-duplex mode
  *           + Smartcard mode
  *           + Interrupts and flags management
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_uart.h"


/** @defgroup UART
  * @brief UART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/\
#define Init_CR_MASK        (u32)0xFFFFFE80
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
  *         the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
	u32  tmpreg = 0, pclk = 0,quotient=0,remainder=0;
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_BaudRate(UART_InitStruct->UART_BaudRate));
	assert_param(IS_UART_UART_WordLengthAndParity(UART_InitStruct->UART_WordLengthAndParity));
	assert_param(IS_UART_StopBitLength(UART_InitStruct->UART_StopBitLength));
	assert_param(IS_UART_ParityMode(UART_InitStruct->UART_ParityMode));
	assert_param(IS_UART_Receiver(UART_InitStruct->UART_Receiver));
  assert_param(IS_UART_LoopbackMode(UART_InitStruct->UART_LoopbackMode));
	UARTx->RXFR = UART_RXFR_RXFR;
	UARTx->TXFR = UART_TXFR_TXFR;
	tmpreg = UARTx->CR;
	tmpreg &= Init_CR_MASK;
	tmpreg |=  (UART_InitStruct ->UART_WordLengthAndParity  | \
							UART_InitStruct ->UART_StopBitLength        | \
							UART_InitStruct ->UART_ParityMode           | \
							UART_InitStruct->UART_LoopbackMode          | \
							UART_InitStruct->UART_Receiver);
	UARTx->CR = tmpreg;
	
	pclk = RCC_GetClockFreq(RCC_PCLK);
	quotient=(pclk/(16*UART_InitStruct->UART_BaudRate));
	remainder=(pclk%(16*UART_InitStruct->UART_BaudRate));
	
	if(quotient == 0)
	{
		 UARTx->BRR = 1;
	}
	else
	{
		if (remainder > (8 * UART_InitStruct->UART_BaudRate))
		{
				UARTx->BRR = (u16) (quotient + 1);
		}
		else
		{
				UARTx->BRR = (u16) quotient;
		}
	}
}

/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
	/* USART_InitStruct members default value */
	UART_InitStruct->UART_BaudRate = 19200;
	UART_InitStruct->UART_WordLengthAndParity = UART_WordLengthAndParity_8DP;
	UART_InitStruct->UART_StopBitLength = UART_StopBitLength_1;
	UART_InitStruct->UART_ParityMode = UART_ParityMode_Odd;
	UART_InitStruct->UART_Receiver = UART_Receiver_Enable;
	UART_InitStruct->UART_LoopbackMode = UART_LoopbackMode_Disable;
}

/**
  * @brief  Enables or disables the specified UART peripheral.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  NewState: new state of the USARTx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the selected USART by setting the UE bit in the CR1 register */
		UARTx->CR |= UART_CR_EN;
	}
	else
	{
		/* Disable the selected USART by clearing the UE bit in the CR1 register */
		UARTx->CR &= (~UART_CR_EN);
	}
}

/**
  * @brief  Transmits single data through the UARTx peripheral.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_SendData(UART_TypeDef* UARTx, u16 Data)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_DATA(Data));
	/* While the TxFIFO contain 8 characters. */
	while((UARTx->SR & UART_SR_TXF));
	/* Transmit Data */
	UARTx->DR = (Data & (u16)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @retval The received data.
  */
u16 UART_ReceiveData(UART_TypeDef* UARTx)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	/* Receive Data */
	return (u16)(UARTx->DR & (u16)0x01FF);
}

/**
  * @brief  This function reset the Rx and the Tx FIFOs
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  FIFO: Transmit FIFO or receive FIFO for the UART .
  *          This parameter can be:
  *            @arg Rx_FIFO: Receive FIFO .
  *            @arg Tx_FIFO: Transmit FIFO .
  * @retval None.
  */
void UART_FifoReset(UART_TypeDef* UARTx, u8 UART_FIFO)
{
  assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_FIFO(UART_FIFO));
	switch (UART_FIFO)
	{
		case FIFO_RX :
			UARTx->RXFR = UART_RXFR_RXFR;
			break;
		case FIFO_TX :
			UARTx->TXFR = UART_TXFR_TXFR;
			break;
	}
}

/**
  * @brief  Enables or disables the UART's Half Duplex communication.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  NewState: new state of the UART Communication.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_HalfDuplexCmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the Half-Duplex mode by setting the OWE bit in the CR register */
		UARTx->CR |= UART_CR_SLME;
	}
	else
	{
		/* Disable the Half-Duplex mode by clearing the OWE bit in the CR register */
		UARTx->CR  &= (u32)~((u32)UART_CR_SLME);
	}
}

/**
  * @brief  Enables or disables the UART's transmitter or receiver.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  UART_Direction: specifies the UART direction.
  *          This parameter can be any combination of the following values:
  *            @arg UART_SingleLineDirection_Tx: UART Single Line Direction Transmitter
  *            @arg UART_SingleLineDirection_Rx: UART Single Line Direction Receiver
  * @param  NewState: new state of the USART transfer direction.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_HalfDuplexDirectionConfig(UART_TypeDef* UARTx, u32 Direction)
{
	u32 tmpreg=0;
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_SingleLineDirection(Direction));
	
	tmpreg=UARTx->CR;
	tmpreg&=~UART_CR_SLDS;
	tmpreg|=Direction;
	UARTx->CR=tmpreg;
}

/**
  * @brief  Enables or disables the UART's IrDA interface.
  * @param  UARTx: where x can be 0 to select the UART peripheral.
  * @param  NewState: new state of the IrDA mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the IrDA mode by setting the IRE bit in the IMCR register */
		UARTx->IMCR |= UART_IMCR_IRE;
	}
	else
	{
		/* Disable the IrDA mode by clearing the EN bit in the IMCR register */
		UARTx->IMCR &= ~UART_IMCR_IRE;
	}
}

/**
  * @brief  Configures the IrDA's Pin polarity
  * @param  UARTx: where x can be 0 to select the UART peripheral.
  * @param  NewState: new defined levels for the USART data.
  *          This parameter can be:
  *            @arg ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).
  *            @arg pin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).
  * @note   This function has to be called before calling UART_Cmd() function.
  * @retval None
  */
void UART_IrDAPolarityConfig(UART_TypeDef* UARTx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the binary data inversion feature by setting the DATAINV bit in
		   the CR2 register */
		UARTx->IMCR |= UART_IMCR_IRPN;
	}
	else
	{
		/* Disable the binary data inversion feature by clearing the DATAINV bit in
		   the CR2 register */
		UARTx->IMCR &= ~UART_IMCR_IRPN;
	}
}

/**
  * @brief  Sets the infrared duty cycle for UART peripheral.
  * @param  UARTx: where x can be 0 to select the UART peripheral.
  * @param  IrDADutyCycle: specifies the infrared duty cycle.
  * @note   This function has to be called before calling UART_Cmd() function.
  * @retval None
  */
void UART_IrDADutyCycleConfig(UART_TypeDef* UARTx, u16 IrDADutyCycle)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_InfraredDutyCycle(IrDADutyCycle));
	/* Clear the IrDA's modulation PWM duty cycle */
	UARTx->IMDCR &= ~UART_IMDCR_DUTY;
	/* Set the IrDA's modulation PWM duty cycle*/
	UARTx->IMDCR |= IrDADutyCycle;
}

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  UARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_RXNEI: specifies the interrupt source for Receiver FIFO buffer non-empty interrupt.
  *            @arg UART_IT_RXFI: specifies the interrupt source for Receiver FIFO buffer full interrupt.
  *            @arg UART_IT_PEI: specifies the interrupt source for Parity error interrupt.
  *            @arg UART_IT_FEI: specifies the interrupt source for Frame error interrupt.
  *            @arg UART_IT_OVRI: specifies the interrupt source for Receiver FIFO buffer overflow interrupt.
  *            @arg UART_IT_TXEI: specifies the interrupt source for Transmitter FIFO buffer empty interrupt.
  *            @arg UART_IT_TXFI: specifies the interrupt source for Transmitter FIFO buffer full interrupt.
  *            @arg UART_IT_TXOI: specifies the interrupt source for Transfer end interrupt
  * @param  NewState: new state of the specified USARTx interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(UART_TypeDef* UARTx, u32 UART_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_IT(UART_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		UARTx->IE |= UART_IT;
	}
	else
	{
		UARTx->IE &= ~UART_IT;
	}
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UARTx: where x can be from 0 to 1 to select the UART peripheral.
  * @param  UART_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg UART_FLAG_RXNE: Receiver FIFO not empty flag.
  *            @arg UART_FLAG_RXF: Receiver FIFO full flag.
  *            @arg UART_FLAG_PE: Parity error flag.
  *            @arg UART_FLAG_FE: Frame error flag.
  *            @arg UART_FLAG_OVR: Receiver FIFO buffer overflow flag.
  *            @arg UART_FLAG_TXE: Transmitter FIFO empty flag.
  *            @arg UART_FLAG_TXF: Transmitter FIFO full flag.
  *            @arg UART_FLAG_TXO: Transfer end flag.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, u32 UART_FLAG)
{
	FlagStatus bitstatus = RESET;
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_FLAG(UART_FLAG));
	if ((UARTx->SR & UART_FLAG) != (u16)RESET)
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
  * @brief  Clears the UARTx's pending flags.
  * @param  UARTx: where x can be from 0 to 1 to select the USART peripheral.
  * @param  USART_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg UART_FLAG_PE: Parity error flag.
  *            @arg UART_FLAG_FE: Frame error flag.
  *            @arg UART_FLAG_OVR: Receiver FIFO buffer overflow flag.
  * @retval None
  */
void UART_ClearFlag(UART_TypeDef* UARTx, u32 UART_FLAG)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_FLAG(UART_FLAG));
	if(UART_FLAG==UART_FLAG_PE || UART_FLAG==UART_FLAG_FE || UART_FLAG==UART_FLAG_OVR)
	{
		UARTx->SR |= UART_FLAG;
	}
}

/**
  * @brief  Checks whether the specified UART intterrupt status is set or not.
  * @param  UARTx: where x can be from 0 to 1 to select the USART peripheral.
  * @param  UART_IT: Specify the intterrupt status to be checked.
  *         This parameter can be one of the following values:
	*            @arg UART_IT_RXNEI: specifies the interrupt source for Receiver FIFO buffer non-empty interrupt.
  *            @arg UART_IT_RXFI: specifies the interrupt source for Receiver FIFO buffer full interrupt.
  *            @arg UART_IT_PEI: specifies the interrupt source for Parity error interrupt.
  *            @arg UART_IT_FEI: specifies the interrupt source for Frame error interrupt.
  *            @arg UART_IT_OVRI: specifies the interrupt source for Receiver FIFO buffer overflow interrupt.
  *            @arg UART_IT_TXEI: specifies the interrupt source for Transmitter FIFO buffer empty interrupt.
  *            @arg UART_IT_TXFI: specifies the interrupt source for Transmitter FIFO buffer full interrupt.
  *            @arg UART_IT_TXOI: specifies the interrupt source for Transfer completed interrupt
  * @return ITStatus of UART_IT (SET or RESET).
  */
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, u32 UART_IT)
{
	ITStatus bitstatus = RESET;
	u32 enablestatus = 0;
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_IT(UART_IT));
	/**/
	enablestatus = (u32)(UARTx->IE & UART_IT);
	/*  */
	if (((u32)(UARTx->SR & UART_IT) != (u32)RESET) && (enablestatus != (u32)RESET))
	{
		/* */
		bitstatus = SET;
	}
	else
	{
		/* */
		bitstatus = RESET;
	}
	/**/
	return  bitstatus;
}

/**
  * @}
  */

void UART_SampleRateControl(UART_TypeDef* UARTx, u32 UART_SRC)
{
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_SampleRateControl(UART_SRC));
	UARTx->BRR&=~UART_BRR_SRC;
	UARTx->BRR|=UART_SRC;
}
