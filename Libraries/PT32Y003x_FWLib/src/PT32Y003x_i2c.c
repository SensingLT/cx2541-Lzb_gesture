
  /******************************************************************************
  * @file    PT32Y003x_i2c.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides firmware functions to manage the following
  *          functionalities of the Inter-Integrated circuit (I2C0):
  *           + Initialization and Configuration
  *           + Communications handling
  *           + I2C0 registers management
  *           + Data transfers management
  *           + Interrupts and flags management
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
  
/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_i2c.h"

/** @defgroup I2C0
  * @brief I2C0 driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define Init_CR_MASK   (u32)0xFC00FFFB
#define Init_CCR_MASK  (u32)0x3FF0004
/**
  * @brief  Initializes the I2Cx peripheral according to the specified
  *            parameters in the I2C_InitStruct.
  * @param  I2Cx: select the I2C0 peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *               contains the configuration information for the specified I2C0 peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
	u32 tmpreg =0;
	u32 addr_bc=0;
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_Address(I2C_InitStruct->I2C_OwnAddress));
	assert_param(IS_I2C_Acknowledge(I2C_InitStruct->I2C_Acknowledge));
	assert_param(IS_I2C_Prescaler(I2C_InitStruct->I2C_Prescaler));
	assert_param(IS_I2C_Broadcast(I2C_InitStruct->I2C_Broadcast));

	I2Cx->CCR=Init_CCR_MASK;
	tmpreg=I2Cx->CR;
	tmpreg&=Init_CR_MASK;
	/*---------------------------- I2Cx OAR Configuration ---------------------*/
	/* I2Cx BroadCast Configuration */
	/* I2Cx Address Configuration */
	addr_bc = (u32)(((I2C_InitStruct->I2C_OwnAddress) << 0x01) | (I2C_InitStruct->I2C_Broadcast));
	/* Write to I2Cx OAR */
	I2Cx->OAR = addr_bc;
	
	/*---------------------------- I2Cx ACK Configuration ----------------------*/
	/* I2Cx ACK Configuration */
	/* I2Cx PSC Configuration */
	tmpreg |=  (u32)((I2C_InitStruct->I2C_Acknowledge) | (((I2C_InitStruct->I2C_Prescaler/4)-1) << 16));
	I2Cx->CR = tmpreg;
	
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
	I2C_InitStruct->I2C_Prescaler = 192;	
	I2C_InitStruct->I2C_Broadcast=I2C_Broadcast_Disable;	
	I2C_InitStruct->I2C_OwnAddress = 0;
	I2C_InitStruct->I2C_Acknowledge = I2C_Acknowledge_Disable;	
}

/**
  * @brief  Enables or disables the specified I2C0 peripheral.
  * @param  I2Cx: select the I2C0 peripheral.
  * @param  NewState: new state of the I2Cx peripheral.
  *               @arg   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Enable the selected I2C0 peripheral */
		I2Cx->CR |= I2C_CR_EN;
	}
	else
	{
		/* Disable the selected I2C0 peripheral */
		I2Cx->CCR |= I2C_CCR_EN;
	}
}

/**
  * @brief  Generates I2Cx communication event.
  * @param  I2Cx: select the I2C0 peripheral.
  * @param  Event: the types of I2Cx's event.
	*          This parameter can be one of the following values:
	*          @arg I2C_Event_Stop: I2C generate stop
	*          @arg I2C_Event_Start: I2C generates start
  * @param  NewState: new state of the I2C Event generation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateEvent(I2C_TypeDef* I2Cx, u8 Event, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_Event(Event));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	/* Generate a STOP event */
	if(Event==I2C_Event_Stop)
	{
		if (NewState != DISABLE)
		{
			/* Generate a STOP condition */
		I2Cx->CR |= I2C_CR_STOP;
		I2Cx->CCR |= I2C_CCR_SI;
		}
		else
		{
			/* Disable the STOP condition generation */
			I2Cx->CCR |= I2C_CCR_SI | I2C_CCR_STOP;
		}
	}
	/* Generate a START event */
	else if(Event==I2C_Event_Start)
	{
		if (NewState != DISABLE)
		{
			/* Generate a START condition */
			I2Cx->CR |= I2C_CR_STAR;
		}
		else
		{
			/* Disable the START condition generation */
			I2Cx->CCR |= I2C_CCR_STAR;
		}
	}
	else
	{
		if (NewState != DISABLE)
		{
			/* Generate a START condition */
			I2Cx->CR |= I2C_CR_STAR;
			I2Cx->CCR |= I2C_CCR_SI;
		}
		else
		{
			/* Disable the START condition generation */
			I2Cx->CCR |= I2C_CCR_STAR;
		}
	}
}

/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: select the I2C0 peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, u8 Data)
{
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	/* Write in the DR register the data to be sent */
	I2Cx->DR = (u8)Data;
	I2Cx->CCR = I2C_CCR_SI| I2C_CCR_STAR;
}
/**
  * @brief  Sends a data/addr byte through the I2Cx peripheral, then clear STA bit
  * @param  I2Cx: select the I2C0 peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendAddr(I2C_TypeDef* I2Cx, u8 Data)
{
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	/* Write in the DR register the data to be sent */
	I2Cx->DR = (u8)Data;
	I2Cx->CCR = I2C_CCR_SI | I2C_CCR_STAR;
}


/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: select the I2C0 peripheral.
  * @retval The value of the received data.
  */
u8 I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	/* Return the data in the DR register */
	return (I2Cx->DR);
}

/**
  * @brief  Checks whether the specified I2C0 flag is set or not.
  * @param  I2Cx: select the I2C0 peripheral.
  * @param  I2C_FLAG: specifies the flag to check. 
  *               This parameter can be one of the following values:
  *               @arg I2C_FLAG_Stop 			总线上出现一个停止信号
  *               @arg I2C_FLAG_StartOk 			起始信号发送完毕
  *               @arg I2C_ReStartOk 			重复起始信号发送完毕
  *               @arg I2C_FLAG_MASGetAckW 	主机， 地址字发送完毕， 收到 ACK
  *               @arg I2C_FLAG_MASGetNackW 	主机， 地址字发送完毕， 收到 NACK
  *               @arg I2C_FLAG_MDSGetAck 		主机， 数据字发送完毕， 收到 ACK
  *               @arg I2C_FLAG_MDSGetNack 		主机， 数据字发送完毕， 收到 NACK
  *               @arg I2C_FLAG_MArbitrationlost  	主机， 总线仲裁失败
  *               @arg I2C_FLAG_MASGetAckR 		主机， 地址字发送完毕， 收到 ACK
  *               @arg I2C_FLAG_MASGetNackR 		主机， 地址字发送完毕， 收到 NACK
  *               @arg I2C_FLAG_MDGSendAck 		主机， 数据字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_MDGSendNack 		主机， 数据字接收完毕， 回送 NACK
   
  *               @arg I2C_FLAG_SAGSendAckW 	从机， 地址字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SALAGSendAckW 	从机，总线仲裁失败转化的从机， 地址字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SBCAGSendAck 	从机，广播地址字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SALBCAGSendAck 	从机，总线仲裁失败转化的从机，广播地址字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SDGSendAck 		从机， 数据字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SDGSendNack 		从机， 数据字接收完毕， 回送 NACK
  *               @arg I2C_FLAG_SBCDGSendAck 	从机， 广播数据字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SBCDGSendNack 	从机， 广播数据字接收完毕， 回送 NACK
  *               @arg I2C_FLAG_SDGGSRS 			从机， 数据字接收完毕， 接收到停止信号或重复起始信号
  *               @arg I2C_FLAG_SAGSendAckR 	从机， 地址字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SALAGSendAckR 	从机， 主机总线仲裁失败转化的从机,地址字接收完毕， 回送 ACK
  *               @arg I2C_FLAG_SDSReadAck 		从机， 数据字发送完毕， 收到 ACK
  *               @arg I2C_FLAG_SDSReadNack 		从机， 数据字发送完毕， 收到 NACK
  *               @arg I2C_FLAG_SDSSAGSRS 		从机， 数据字接收完毕， 回送 ACK 后、接收到停止信号或重复起始信号
  *               @arg I2C_FLAG_IDLE 				总线空闲
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, u32 I2C_FLAG)
{
	FlagStatus bitstatus = RESET;
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_FLAG(I2C_FLAG));
	if (I2Cx->SR  == I2C_FLAG)
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
  * @}
  */


