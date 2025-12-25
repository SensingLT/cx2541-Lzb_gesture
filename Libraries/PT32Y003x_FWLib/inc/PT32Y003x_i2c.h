 /******************************************************************************
  * @file    PT32Y003x_i2c.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the I2C0 firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_I2C_H
#define PT32Y003x_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/** @addtogroup I2C0
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/

/** @brief  I2C0 Init structure definition **/
typedef struct
{
	u32 I2C_Prescaler;					/*!< Specifies the baud rate prescaler control.
								                   This parameter can be a number between 20 and 4096 
																	 @note I2C BaundRate = PCLK's Frequency / I2C_Prescaler */
	
	u32 I2C_Broadcast;					/*!< Specifies the Broadcast response control.
								                   This parameter can be a value of @ref I2C_broadcast_state */
	
	u32 I2C_OwnAddress;					/*!< Specifies the device own address.
																   This parameter can be a 7-bit address */
	
	u32 I2C_Acknowledge;   		  /*!< Enables or disables the acknowledgement.
								                   This parameter can be a value of @ref I2C_acknowledgement_state */
	         		
}I2C_InitTypeDef;

/** @defgroup IS_I2C_ALL_PERIPH **/
#define IS_I2C_ALL_PERIPH(SEL)       ((SEL) == I2C0)

/** @defgroup I2C_broadcast_state 
  * @{
  */
#define  I2C_Broadcast_Disable					0x00000000
#define  I2C_Broadcast_Enable			 		I2C_OAR_BC
#define  IS_I2C_Broadcast(SEL)					(((SEL) == I2C_Broadcast_Enable) || ((SEL) == I2C_Broadcast_Disable))

/** @defgroup I2C_acknowledgement **/
#define  I2C_Acknowledge_Disable			 	0x00000000
#define  I2C_Acknowledge_Enable			    I2C_CR_ACK
#define  IS_I2C_Acknowledge(SEL) 				(((SEL) == I2C_Acknowledge_Disable) || \
												((SEL) == I2C_Acknowledge_Enable))
                                         
/** @defgroup I2C_Prescaler **/
#define IS_I2C_Prescaler(SEL)	    (((SEL) >= 20)  && ((SEL) < 4096))

/** @defgroup IS_I2C_AddressValue 
  * @{
  */
#define  IS_I2C_Address(SEL)  			((SEL) <128)

/** @defgroup IS_I2C_Event 
  * @{
  */
#define  I2C_Event_Stop								 ((u8)0x00)
#define  I2C_Event_Start							 ((u8)0x01)
#define  I2C_Event_Restart						 ((u8)0x02)
#define  IS_I2C_Event(SEL)  					 (((SEL)==I2C_Event_Stop)||((SEL)==I2C_Event_Start)||((SEL)==I2C_Event_Restart))

/** @defgroup I2C_flag 
  * @{
  */
#define I2C_FLAG_Stop 			  			(I2C_SR_SR&0x00)	/* 总线上出现一个停止信号	*/
#define I2C_FLAG_StartOk 					(I2C_SR_SR&0x08)	/* 起始信号发送完毕 */
#define I2C_FLAG_ReStartOk 					(I2C_SR_SR&0x10)	/* 重复起始信号发送完毕 */
#define I2C_FLAG_MASGetAckW 				(I2C_SR_SR&0x18)	/* 主机， 地址字发送完毕， 收到 ACK  */
#define I2C_FLAG_MASGetNackW 				(I2C_SR_SR&0x20)	/* 主机， 地址字发送完毕， 收到 NACK */
#define I2C_FLAG_MDSGetAck 					(I2C_SR_SR&0x28)	/* 主机， 数据字发送完毕， 收到 ACK  */
#define I2C_FLAG_MDSGetNack 				(I2C_SR_SR&0x30)	/* 主机， 数据字发送完毕， 收到 NACK */
#define I2C_FLAG_MArbitrationlost 	        (I2C_SR_SR&0x38)	/* 主机， 总线仲裁失败 */
#define I2C_FLAG_MASGetAckR 				(I2C_SR_SR&0x40)	/* 主机， 地址字发送完毕， 收到 ACK  */
#define I2C_FLAG_MASGetNackR 				(I2C_SR_SR&0x48)	/* 主机， 地址字发送完毕， 收到 NACK */
#define I2C_FLAG_MDGSendAck 				(I2C_SR_SR&0x50)	/* 主机， 数据字接收完毕， 回送 ACK  */
#define I2C_FLAG_MDGSendNack 				(I2C_SR_SR&0x58)	/* 主机， 数据字接收完毕， 回送 NACK */

#define I2C_FLAG_SAGSendAckW 				(I2C_SR_SR&0x60)	/* 从机， 地址字接收完毕， 回送 ACK */
#define I2C_FLAG_SALAGSendAckW 			    (I2C_SR_SR&0x68)	/* 从机， 总线仲裁失败转化的从机， 地址字接收完毕， 回送 ACK */
#define I2C_FLAG_SBCAGSendAck 			    (I2C_SR_SR&0x70)	/* 从机， 广播地址字接收完毕， 回送 ACK */
#define I2C_FLAG_SALBCAGSendAck 		    (I2C_SR_SR&0x78)	/* 从机， 总线仲裁失败转化的从机，广播地址字接收完毕， 回送 ACK */
#define I2C_FLAG_SDGSendAck 				(I2C_SR_SR&0x80)	/* 从机， 数据字接收完毕， 回送 ACK */
#define I2C_FLAG_SDGSendNack 				(I2C_SR_SR&0x88)	/* 从机， 数据字接收完毕， 回送 NACK */
#define I2C_FLAG_SBCDGSendAck 			    (I2C_SR_SR&0x90)	/* 从机， 广播数据字接收完毕， 回送 ACK */
#define I2C_FLAG_SBCDGSendNack 			    (I2C_SR_SR&0x98)	/* 从机， 广播数据字接收完毕， 回送 NACK */
#define I2C_FLAG_SDGGSRS 					(I2C_SR_SR&0xA0)	/* 从机， 数据字接收完毕， 接收到停止信号或重复起始信号 */
#define I2C_FLAG_SAGSendAckR 				(I2C_SR_SR&0xA8)	/* 从机， 地址字接收完毕， 回送 ACK */
#define I2C_FLAG_SALAGSendAckR 			    (I2C_SR_SR&0xB0)	/* 从机， 主机总线仲裁失败转化的从机,地址字接收完毕， 回送 ACK */
#define I2C_FLAG_SDSReadAck 				(I2C_SR_SR&0xB8)	/* 从机， 数据字发送完毕， 收到 ACK */
#define I2C_FLAG_SDSReadNack 				(I2C_SR_SR&0xC0)	/* 从机， 数据字发送完毕， 收到 NACK */
#define I2C_FLAG_SDSSAGSRS 					(I2C_SR_SR&0xC8)	/* 从机， 数据字接收完毕， 回送 ACK 后、接收到停止信号或重复起始信号 */
#define I2C_FLAG_IDLE 						(I2C_SR_SR&0xF8)	/* 总线空闲*/
#define IS_I2C_FLAG(SEL)   (((SEL) == I2C_FLAG_Stop)          || ((SEL) == I2C_FLAG_StartOk)             || \
                            ((SEL) == I2C_FLAG_ReStartOk)     || ((SEL) == I2C_FLAG_MASGetAckW)          || \
                            ((SEL) == I2C_FLAG_MASGetNackW)   || ((SEL) == I2C_FLAG_MDSGetAck)           || \
                            ((SEL) == I2C_FLAG_MDSGetNack)    || ((SEL) == I2C_FLAG_MArbitrationlost)    || \
                            ((SEL) == I2C_FLAG_MASGetAckR)    || ((SEL) == I2C_FLAG_MASGetNackR)         || \
                            ((SEL) == I2C_FLAG_MDGSendAck)    || ((SEL) == I2C_FLAG_MDGSendNack)         || \
                            ((SEL) == I2C_FLAG_SAGSendAckW)   || ((SEL) == I2C_FLAG_SALAGSendAckW)       || \
                            ((SEL) == I2C_FLAG_SBCAGSendAck)  || ((SEL) == I2C_FLAG_SALBCAGSendAck)      || \
                            ((SEL) == I2C_FLAG_SDGSendAck)    || ((SEL) == I2C_FLAG_SDGSendNack)         || \
                            ((SEL) == I2C_FLAG_SBCDGSendAck)  || ((SEL) == I2C_FLAG_SBCDGSendNack)       || \
                            ((SEL) == I2C_FLAG_SDGGSRS)       || ((SEL) == I2C_FLAG_SAGSendAckR)         || \
                            ((SEL) == I2C_FLAG_SALAGSendAckR) || ((SEL) == I2C_FLAG_SDSReadAck)          || \
                            ((SEL) == I2C_FLAG_SDSReadNack)   || ((SEL) == I2C_FLAG_SDSSAGSRS)           || \
                            ((SEL) == I2C_FLAG_IDLE))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateEvent(I2C_TypeDef* I2Cx, u8 Event, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, u8 Data);
void I2C_SendAddr(I2C_TypeDef* I2Cx, u8 Data);
u8 I2C_ReceiveData(I2C_TypeDef* I2Cx);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, u32 I2C_FLAG);

/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif 


