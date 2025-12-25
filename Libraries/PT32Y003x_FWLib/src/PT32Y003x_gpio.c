  /******************************************************************************
  * @file    PT32Y003x_gpio.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the GPIO peripheral:
  *           + Initialization and Configuration functions
  *           + GPIO Read and Write functions
  *           + GPIO Alternate functions configuration functions
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_gpio.h"


/** @defgroup GPIO
  * @brief GPIO driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A, B, C, D) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	u32 currentpin = 0x00;
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_Mode(GPIO_InitStruct->GPIO_Mode));
	assert_param(IS_GPIO_Pull(GPIO_InitStruct->GPIO_Pull));

	currentpin = GPIO_InitStruct->GPIO_Pin;
	if (((GPIO_InitStruct->GPIO_Mode) == GPIO_Mode_OutPP) || ((GPIO_InitStruct->GPIO_Mode) == GPIO_Mode_OutOD))
	{
		/* Output mode configuration */
		GPIOx->OES = currentpin;
		if((GPIO_InitStruct->GPIO_Mode) == GPIO_Mode_OutOD)
		{
			GPIOx->ODS = currentpin;
		}
		else
		{
			GPIOx->ODC = currentpin;
		}
	}
	if((GPIO_InitStruct->GPIO_Mode) == GPIO_Mode_In)
	{
		/* input mode configuration */
		GPIOx->OEC = currentpin;
		switch(((u32)GPIO_InitStruct->GPIO_Pull))
		{
			case GPIO_Pull_NoPull :
				GPIOx->PDC = currentpin;
				GPIOx->PUC = currentpin;
				break;
			case GPIO_Pull_Up :
				GPIOx->PDC = currentpin;
				GPIOx->PUS = currentpin;
				break;
			case GPIO_Pull_Down :
				GPIOx->PDS = currentpin;
				GPIOx->PUC = currentpin;
				break;
		}
	}
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
	/* Reset GPIO init structure parameters values */
	GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStruct->GPIO_Mode = GPIO_Mode_In;
	GPIO_InitStruct->GPIO_Pull = GPIO_Pull_NoPull;
}

u16 GPIO_ReadData(GPIO_TypeDef* GPIOx)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	return ((u16)GPIOx->DR);
}

u8 GPIO_ReadDataBit(GPIO_TypeDef* GPIOx, u32 GPIO_Pin)
{
    u8 bitstatus = 0x00;
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	if ((GPIOx->DR & GPIO_Pin) != (u32)RESET)
	{
		bitstatus = (u8)SET;
	}
	else
	{
		bitstatus = (u8)RESET;
	}
	return bitstatus;   
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *               @arg   This parameter can be GPIO_Pin_x where x can be(0~15) or GPIO_Pin_All 
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u32 GPIO_Pin)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	GPIOx->BSR= GPIO_Pin;
}

/**
  * @brief  Reset the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *               @arg   This parameter can be GPIO_Pin_x where x can be(0~15) or GPIO_Pin_All 
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u32 GPIO_Pin)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	GPIOx->BRR= GPIO_Pin;
}
/**
  * @brief  Reverse the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *               @arg   This parameter can be GPIO_Pin_x where x can be(0~15) or GPIO_Pin_All 
  * @retval None
  */
void GPIO_ReverseBits(GPIO_TypeDef* GPIOx, u32 GPIO_Pin)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	GPIOx->DR ^= GPIO_Pin;
}

void GPIO_WriteDataBit(GPIO_TypeDef* GPIOx, u32 GPIO_Pin, BitAction Action)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
    if (Action != RESET)
	{
		GPIOx->DR |= GPIO_Pin;
	}
	else
	{
		GPIOx->DR &= ~GPIO_Pin;
	}
}

void GPIO_WriteData(GPIO_TypeDef* GPIOx, u16 PortVal)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	GPIOx->DR = PortVal;
}

void GPIO_AnalogRemapConfig(AFIO_TypeDef* AFIOx, u32 GPIO_Pin, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_AFIO_ALL_PERIPH(AFIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		AFIOx->ANAS |= GPIO_Pin;
	}
	else
	{
		AFIOx->ANAC |= GPIO_Pin;
	}
}

void GPIO_DigitalRemapConfig(AFIO_TypeDef* AFIOx, u32 GPIO_Pin, u8 AFIO_AF, FunctionalState NewState)
{
    u8 temp = 0;
	/* Check the parameters */
	assert_param(IS_AFIO_ALL_PERIPH(AFIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	assert_param(IS_AFIO_AF(AFIO_AF));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		AFIOx->AFC |= GPIO_Pin;
		while(GPIO_Pin)			
		{
			if((GPIO_Pin&0x01)==1)	
			{
        AFIOx->AFS0|=AFIO_AF<<(temp*4);
			}
			GPIO_Pin=GPIO_Pin>>1;
			temp++;				
		}
	}
	else
	{
		AFIOx->AFC |= GPIO_Pin;
	}
}
/**
  * @brief	Set the selected data port low Byte(PIN0~PIN7),the operation is interrupt safe 
  * @param  GPIOx: where x can be (A, B, C, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *    @arg   This parameter can be GPIO_Pin_x where x can be(0~7)
  * @retval None
  */
void GPIO_SetMASKLPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	
	GPIOx->MASKL[GPIO_Pin & 0xFF] = GPIO_Pin;
}

/**
  * @brief	Reset the selected data port low Byte(PIN0~PIN7),the operation is interrupt safe 
  * @param  GPIOx: where x can be (A, B, C, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *    @arg   This parameter can be GPIO_Pin_x where x can be(0~7)
  * @retval None
  */
void GPIO_ResetMASKLPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	GPIOx->MASKL[GPIO_Pin & 0xFF] = ~GPIO_Pin;
}

/**
  * @brief	Set the selected data port High Byte(PIN0~PIN7),the operation is interrupt safe 
  * @param  GPIOx: where x can be (A, B, C, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *    @arg   This parameter can be GPIO_Pin_x where x can be(0~7)
  * @retval None
  */
void GPIO_SetMASKHPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	GPIOx->MASKH[GPIO_Pin & 0xFF] = GPIO_Pin;
}

/**
  * @brief  Reset the selected data port High Byte(PIN0~PIN7),the operation is interrupt safe 
  * @param  GPIOx: where x can be (A, B, C, F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *    @arg   This parameter can be GPIO_Pin_x where x can be(0~7)
  * @retval None
  */
void GPIO_ResetMASKHPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	GPIOx->MASKH[GPIO_Pin & 0xFF] = ~GPIO_Pin;
}

/**
  * @brief  Enable or Disable GPIO_Pin Pull_Up function.
  * @param  GPIOx: where x can be (A, B, C, F) to select the AFIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *    			@arg   This parameter can be GPIO_Pin_x where x can be(0..15) or GPIO_Pin_All
  * @param  NewState: new state of the port pin schmitt function.
  *    			@arg   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_PullUpConfig(GPIO_TypeDef *GPIOx, u32 GPIO_Pin, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	GPIOx->OEC = GPIO_Pin;
	if(NewState != DISABLE)
	{
		GPIOx->PDC = GPIO_Pin;
		GPIOx->PUS = GPIO_Pin;
	}
	else
	{
		GPIOx->PUC = GPIO_Pin;
	}
}

/**
  * @brief  Enable or Disable GPIO_Pin Pull_Down function.
  * @param  GPIOx: where x can be (A, B, C, F) to select the AFIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *    			@arg   This parameter can be GPIO_Pin_x where x can be(0..15) or GPIO_Pin_All
  * @param  NewState: new state of the port pin schmitt function.
  *    			@arg   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_PullDownConfig(GPIO_TypeDef *GPIOx, u32 GPIO_Pin, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_Pin(GPIO_Pin));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	GPIOx->OEC = GPIO_Pin;
	if(NewState != DISABLE)
	{
		GPIOx->PUC = GPIO_Pin;
		GPIOx->PDS = GPIO_Pin;
	}
	else
	{
		GPIOx->PDC = GPIO_Pin;
	}	
}
