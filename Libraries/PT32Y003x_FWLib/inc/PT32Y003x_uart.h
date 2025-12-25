  /******************************************************************************
  * @file    PT32Y003x_uart.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the UART firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
    

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_UART_H
#define PT32Y003x_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @brief UART Init Structure definition **/
typedef struct
{
	u32 UART_BaudRate; 							/*!< This member configures the USART communication baud rate.
																			 @note UART_BaudRate's maximum is 3Mbps. */
	
	u16 UART_WordLengthAndParity;		/*!< Specifies the number of data bits transmitted or 
																			 received in a frame and the parity mode.
                                       This parameter can be a value of @ref UART_WordLengthAndParity */
	
	u16 UART_StopBitLength;					/*!< Specifies the number of stop bits transmitted.
                                       This parameter can be a value of @ref UART_StopBitLength */
	
	u16 UART_ParityMode;						/*!< Specifies the parity mode.
                                       This parameter can be a value of @ref UART_ParityMode */
	
	u16 UART_Receiver;							/*!< Specifies the receive enable.
                                       This parameter can be a value of @ref UART_Receiver */
	
	u16 UART_LoopbackMode;					/*!< Specifies the lookback mode enable.
                                       This parameter can be a value of @ref UART_LoopbackMode */
} UART_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup UART_Oversampling_Rate **/
#define IS_UART_ALL_PERIPH(SEL)   ((SEL) == UART0 || (SEL) == UART1)

/** @defgroup UART_FIFO
* @{ 
*/
#define FIFO_RX    						(u8)0x0
#define FIFO_TX    						(u8)0x1
#define IS_UART_FIFO(SEL)   	(((SEL) == FIFO_RX) || ((SEL) == FIFO_TX))

/** @defgroup UART_BaudRate
* @{ 
*/
#define IS_UART_BaudRate(SEL)	(((SEL) > 46) && ((SEL) <= 3000000))

#define UART_SampleRate1   (UART_BRR_SRC&0x00000)
#define UART_SampleRate2   (UART_BRR_SRC&0x10000)
#define UART_SampleRate3   (UART_BRR_SRC&0x20000)
#define IS_UART_SampleRateControl(SEL)	( (SEL==UART_SampleRate1) || (SEL==UART_SampleRate2) || (SEL==UART_SampleRate3) )
/** @defgroup UART_WordLengthAndParity
* @{ 
*/
#define UART_WordLengthAndParity_8D      (UART_CR_WP&0X1)
#define UART_WordLengthAndParity_7DP     (UART_CR_WP&0X3)
#define UART_WordLengthAndParity_9D      (UART_CR_WP&0X4)
#define UART_WordLengthAndParity_8DP     (UART_CR_WP&0X7)
#define IS_UART_UART_WordLengthAndParity(SEL)	(((SEL) == UART_WordLengthAndParity_8D)  ||\
                                                 ((SEL) == UART_WordLengthAndParity_7DP) ||\
                                                 ((SEL) == UART_WordLengthAndParity_9D)  ||\
                                                 ((SEL) == UART_WordLengthAndParity_8DP))

/** @defgroup UART_StopBitLength
* @{ 
*/
#define UART_StopBitLength_0P5      0x00000000
#define UART_StopBitLength_1        (UART_CR_STOP&0X08)
#define UART_StopBitLength_1P5      (UART_CR_STOP&0X10) 
#define UART_StopBitLength_2        (UART_CR_STOP&0X18) 
#define IS_UART_StopBitLength(SEL) (((SEL) == (UART_StopBitLength_1)) ||\
                                    ((SEL) == UART_StopBitLength_0P5) ||\
                                    ((SEL) == UART_StopBitLength_1P5) ||\
                                    ((SEL) == UART_StopBitLength_2))
																		
/** @defgroup UART_ParityMode
* @{ 
*/                               
#define UART_ParityMode_Even        0x00000000    
#define UART_ParityMode_Odd		    	UART_CR_PS		
#define IS_UART_ParityMode(SEL)	   (((SEL) == UART_ParityMode_Even) ||\
                                    ((SEL) == UART_ParityMode_Odd))
							
/** @defgroup UART_Receiver
* @{ 
*/								
#define  UART_Receiver_Disable	            0x00000000 								
#define  UART_Receiver_Enable	    	    UART_CR_RE
#define IS_UART_Receiver(SEL)				(((SEL) == UART_Receiver_Disable) ||\
                                            ((SEL) == UART_Receiver_Enable))

/** @defgroup UART_LoopbackMode
* @{ 
*/
#define UART_LoopbackMode_Disable		0x00000000
#define UART_LoopbackMode_Enable		UART_CR_LPB
#define IS_UART_LoopbackMode(SEL)	   (((SEL) == UART_LoopbackMode_Disable) ||\
                                        ((SEL) == UART_LoopbackMode_Enable))

/** @defgroup UART_Global_definition **/
#define IS_UART_DATA(SEL)             	 ((SEL) <= 0x1FF)

/** @defgroup UART_DutyCycle
* @{ 
*/
#define IS_UART_InfraredDutyCycle(SEL)   ((SEL) <= 0xFFF)

/** @defgroup IS_UART_OWD_SEL **/
#define UART_SingleLineDirection_Rx				0x00000000
#define UART_SingleLineDirection_Tx				UART_CR_SLDS
#define IS_UART_SingleLineDirection(SEL)	(((SEL) == UART_SingleLineDirection_Tx) || \
                                            ((SEL) == UART_SingleLineDirection_Rx))                                                           
/** @defgroup IS_UART_SR_SEL **/
#define UART_FLAG_RXNE    UART_SR_RXNE
#define UART_FLAG_RXF	    UART_SR_RXF
#define UART_FLAG_PE	    UART_SR_PE
#define UART_FLAG_FE 	    UART_SR_FE
#define UART_FLAG_OVR	    UART_SR_OVR
#define UART_FLAG_TXE	    UART_SR_TXE
#define UART_FLAG_TXF	    UART_SR_TXF
#define UART_FLAG_TXO	    UART_SR_TXO
#define IS_UART_FLAG(SEL)	   (((SEL) == UART_FLAG_RXNE)    ||\
															((SEL) == UART_FLAG_RXF)     ||\
															((SEL) == UART_FLAG_PE)    	 ||\
															((SEL) == UART_FLAG_FE)   	 ||\
															((SEL) == UART_FLAG_OVR)     ||\
															((SEL) == UART_FLAG_TXE)     ||\
															((SEL) == UART_FLAG_TXF)     ||\
															((SEL) == UART_FLAG_TXO))

/** @defgroup IS_UART_IE_SEL&GET **/
#define UART_IT_RXNEI     UART_IE_RXNEI
#define UART_IT_RXFI      UART_IE_RXFI   
#define UART_IT_PEI       UART_IE_PEI
#define UART_IT_FEI       UART_IE_FEI
#define UART_IT_OVRI      UART_IE_OVRI
#define UART_IT_TXEI      UART_IE_TXEI
#define UART_IT_TXFI      UART_IE_TXFI
#define UART_IT_TXOI      UART_IE_TXOI
#define IS_UART_IT(SEL)		   (((SEL) == UART_IT_RXNEI)  ||\
															((SEL) == UART_IT_RXFI)   ||\
															((SEL) == UART_IT_PEI)    ||\
															((SEL) == UART_IT_FEI)    ||\
															((SEL) == UART_IT_OVRI)   ||\
															((SEL) == UART_IT_TXEI)   ||\
															((SEL) == UART_IT_TXFI)   ||\
															((SEL) == UART_IT_TXOI))
								
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_SendData(UART_TypeDef* UARTx, u16 Data);
u16 UART_ReceiveData(UART_TypeDef* UARTx);
void UART_FifoReset(UART_TypeDef * UARTx,  u8 UART_FIFO);
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDAPolarityConfig(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDABaudRateConfig(UART_TypeDef* UARTx, u8 IrDABaudRate);
void UART_IrDADutyCycleConfig(UART_TypeDef* UARTx, u16 IrDADutyCycle);
void UART_HalfDuplexCmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_HalfDuplexDirectionConfig(UART_TypeDef* UARTx, u32 Direction);
void UART_ITConfig(UART_TypeDef* UARTx, u32 UART_IT, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, u32 UART_FLAG);
void UART_ClearFlag(UART_TypeDef* UARTx, u32 UART_CLEAR_FLAG);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, u32 UART_IT);
void UART_SampleRateControl(UART_TypeDef* UARTx, u32 UART_SCR);
/**;
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif 


