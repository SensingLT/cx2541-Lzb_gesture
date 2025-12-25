  /******************************************************************************
  * @file    PT32Y003x_spi.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the SPI firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_SPI_H
#define PT32Y003x_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @brief  SPI Init structure definition   **/
typedef struct
{
  u16 SPI_MasterSlaveMode;               
  u16 SPI_DataFrameFormat;          
  u16 SPI_ClockPolarity;             
  u16 SPI_ClockPhase;             
  u16 SPI_CSS;             
  u16 SPI_SoftwareControlCSS; 
  u8 SPI_Prescaler; 
  u16 SPI_BaudRate;																							 
}SPI_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants **/
#define IS_SPI_ALL_PERIPH(SEL) ((SEL) == SPI0)
                                   
/** @defgroup SPI_Mode  **/
#define SPI_MasterSlaveMode_Master	0x00000000
#define SPI_MasterSlaveMode_Slave	SPI_CR2_MSM
#define IS_SPI_MasterSlaveMode(SEL)	(((SEL) == SPI_MasterSlaveMode_Master) ||\
                                     ((SEL) == SPI_MasterSlaveMode_Slave))

/** @defgroup SPI_DataSize **/
#define SPI_DataFrameFormat_4b	(SPI_CR1_DFF&0x03)
#define SPI_DataFrameFormat_5b	(SPI_CR1_DFF&0x04)
#define SPI_DataFrameFormat_6b	(SPI_CR1_DFF&0x05)
#define SPI_DataFrameFormat_7b	(SPI_CR1_DFF&0x06)
#define SPI_DataFrameFormat_8b	(SPI_CR1_DFF&0x07)
#define SPI_DataFrameFormat_9b	(SPI_CR1_DFF&0x08)
#define SPI_DataFrameFormat_10b	(SPI_CR1_DFF&0x09)
#define SPI_DataFrameFormat_11b	(SPI_CR1_DFF&0x0A)
#define SPI_DataFrameFormat_12b	(SPI_CR1_DFF&0x0B)
#define SPI_DataFrameFormat_13b	(SPI_CR1_DFF&0x0C)
#define SPI_DataFrameFormat_14b	(SPI_CR1_DFF&0x0D)
#define SPI_DataFrameFormat_15b	(SPI_CR1_DFF&0x0E)
#define SPI_DataFrameFormat_16b	(SPI_CR1_DFF&0x0F)
#define IS_SPI_DataFrameFormat(SEL) (((SEL) == SPI_DataFrameFormat_4b)  ||\
                                     ((SEL) == SPI_DataFrameFormat_5b)  ||\
                                     ((SEL) == SPI_DataFrameFormat_6b)  ||\
                                     ((SEL) == SPI_DataFrameFormat_7b)  ||\
                                     ((SEL) == SPI_DataFrameFormat_8b)  ||\
                                     ((SEL) == SPI_DataFrameFormat_9b)  ||\
                                     ((SEL) == SPI_DataFrameFormat_10b) ||\
                                     ((SEL) == SPI_DataFrameFormat_11b) ||\
                                     ((SEL) == SPI_DataFrameFormat_12b) ||\
                                     ((SEL) == SPI_DataFrameFormat_13b) ||\
                                     ((SEL) == SPI_DataFrameFormat_14b) ||\
                                     ((SEL) == SPI_DataFrameFormat_15b) ||\
                                     ((SEL) == SPI_DataFrameFormat_16b))

/** @defgroup SPI_CPOL **/
#define  SPI_ClockPolarity_Low	    0x00000000
#define  SPI_ClockPolarity_High	    SPI_CR1_CPOL
#define IS_SPI_ClockPolarity(SEL)	(((SEL) == SPI_ClockPolarity_Low) ||\
                                     ((SEL) == SPI_ClockPolarity_High))
    
/** @defgroup SPI_CPHA **/
#define  SPI_ClockPhase_1Edge	    0x00000000
#define  SPI_ClockPhase_2Edge	    SPI_CR1_CPHA
#define IS_SPI_ClockPhase(SEL)	    (((SEL) == SPI_ClockPhase_1Edge) ||\
                                     ((SEL) == SPI_ClockPhase_2Edge))
                           
/** @defgroup SPI_CSS  **/
#define  SPI_CSS_HardwareControl	0x00000000
#define  SPI_CSS_SoftwareControl	SPI_CSS_CSS
#define IS_SPI_CSS(SEL)		(((SEL) == SPI_CSS_HardwareControl) ||\
                             ((SEL) == SPI_CSS_SoftwareControl))
                         
/** @defgroup IS_SPI_BR_VAL  **/
#define IS_SPI_BaudRate(SEL) (((SEL) > 1) && ((SEL) < 255))


/** @defgroup IS_SPI_SWCS_SEL  **/
#define  SPI_SoftwareControlCSS_Low			0x00000000
#define  SPI_SoftwareControlCSS_High			SPI_CSS_SWCS
#define IS_SPI_SoftwareControlCSS(SEL)	(((SEL) == SPI_SoftwareControlCSS_Low) ||\
                                         ((SEL) == SPI_SoftwareControlCSS_High))
                                       
/** @defgroup IS_SPI_IE_SEL&GET  **/
#define SPI_IT_OVRE             (SPI_IE_OVRE&0x1)
#define SPI_IT_OTE              (SPI_IE_OTE&0x2)
#define SPI_IT_RXHE             (SPI_IE_RXHE&0x4)
#define SPI_IT_TXHE             (SPI_IE_TXHE&0x8)
#define IS_SPI_IT(SEL)	        (((SEL) == SPI_IT_OVRE) ||\
                                 ((SEL) == SPI_IT_OTE)  ||\
                                 ((SEL) == SPI_IT_RXHE) ||\
                                 ((SEL) == SPI_IT_TXHE))
							
#define SPI_FLAG_TXE	        SPI_SR1_TXE
#define	SPI_FLAG_TNF            SPI_SR1_TNF
#define	SPI_FLAG_RXNE           SPI_SR1_RXNE
#define	SPI_FLAG_RXF            SPI_SR1_RXF
#define	SPI_FLAG_BSY            SPI_SR1_BSY
#define SPI_FLAG_RXFS0          0x00000000   
#define SPI_FLAG_RXFS1          (SPI_SR1_RXFS&0x100) 
#define SPI_FLAG_RXFS2          (SPI_SR1_RXFS&0x200) 
#define SPI_FLAG_RXFS3          (SPI_SR1_RXFS&0x300) 
#define SPI_FLAG_RXFS4          (SPI_SR1_RXFS&0x400) 
#define SPI_FLAG_RXFS5          (SPI_SR1_RXFS&0x500) 
#define SPI_FLAG_RXFS6          (SPI_SR1_RXFS&0x600) 
#define SPI_FLAG_RXFS7          (SPI_SR1_RXFS&0x700) 
#define SPI_FLAG_RXFS8          (SPI_SR1_RXFS&0x800) 
#define SPI_FLAG_TXFS0          0x0000F000   
#define SPI_FLAG_TXFS1          (SPI_SR1_TXFS&0x1000)
#define SPI_FLAG_TXFS2          (SPI_SR1_TXFS&0x2000)
#define SPI_FLAG_TXFS3          (SPI_SR1_TXFS&0x3000)
#define SPI_FLAG_TXFS4          (SPI_SR1_TXFS&0x4000)
#define SPI_FLAG_TXFS5          (SPI_SR1_TXFS&0x5000)
#define SPI_FLAG_TXFS6          (SPI_SR1_TXFS&0x6000)
#define SPI_FLAG_TXFS7          (SPI_SR1_TXFS&0x7000)
#define SPI_FLAG_TXFS8          (SPI_SR1_TXFS&0x8000)
#define	SPI_FLAG_OVR            (SPI_SR2_OVR|0x10000)
#define	SPI_FLAG_OT             (SPI_SR2_OT|0x10000)
#define	SPI_FLAG_RXH            (SPI_SR2_RXH|0x10000)
#define	SPI_FLAG_TXH            (SPI_SR2_TXH|0x10000)
/** @defgroup IS_SPI_SR1_SEL  **/
#define IS_SPI_FLAG(SEL)   (((SEL) == SPI_FLAG_TXE)       ||\
							((SEL) == SPI_FLAG_TNF)       ||\
							((SEL) == SPI_FLAG_RXNE)      ||\
							((SEL) == SPI_FLAG_RXF)       ||\
							((SEL) == SPI_FLAG_BSY)       ||\
							((SEL) == SPI_FLAG_RXFS0)     ||\
							((SEL) == SPI_FLAG_RXFS1)     ||\
							((SEL) == SPI_FLAG_RXFS2)     ||\
                            ((SEL) == SPI_FLAG_RXFS3)     ||\
                            ((SEL) == SPI_FLAG_RXFS4)     ||\
                            ((SEL) == SPI_FLAG_RXFS5)     ||\
                            ((SEL) == SPI_FLAG_RXFS6)     ||\
                            ((SEL) == SPI_FLAG_RXFS7)     ||\
                            ((SEL) == SPI_FLAG_RXFS8)     ||\
                            ((SEL) == SPI_FLAG_TXFS0)     ||\
                            ((SEL) == SPI_FLAG_TXFS1)     ||\
                            ((SEL) == SPI_FLAG_TXFS2)     ||\
                            ((SEL) == SPI_FLAG_TXFS3)     ||\
                            ((SEL) == SPI_FLAG_TXFS4)     ||\
                            ((SEL) == SPI_FLAG_TXFS5)     ||\
                            ((SEL) == SPI_FLAG_TXFS6)     ||\
                            ((SEL) == SPI_FLAG_TXFS7)     ||\
                            ((SEL) == SPI_FLAG_TXFS8)     ||\
                            ((SEL) == SPI_FLAG_OVR)       ||\
                            ((SEL) == SPI_FLAG_OT)        ||\
                            ((SEL) == SPI_FLAG_RXH)       ||\
                            ((SEL) == SPI_FLAG_TXH))
/** @defgroup UART_FIFO
* @{ 
*/
#define SPI_FIFO_RX    						(u8)0x0
#define SPI_FIFO_TX    						(u8)0x1
#define IS_SPI_FIFO(SEL)   	(((SEL) == SPI_FIFO_RX) || ((SEL) == SPI_FIFO_TX))

/* Exported macro ------------------------------------------------------------*/											
/* Exported functions ------------------------------------------------------- */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_SoftwareControlCSSConfig(SPI_TypeDef* SPIx, u32 SWCS_Signal);
void SPI_SendData(SPI_TypeDef* SPIx, u16 Data);
u8 SPI_ReceiveData(SPI_TypeDef* SPIx);
void SPI_ITConfig(SPI_TypeDef* SPIx, u32 SPI_IT, FunctionalState NewState);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, u32 SPI_FLAG);
void SPI_ClearFlag(SPI_TypeDef* SPIx, u32 SPI_FLAG);
u8 SPI_FLASH_SendByte(SPI_TypeDef* SPIx,u8 byte);
void SPI_FifoReset(SPI_TypeDef* SPIx, u8 SPI_FIFO);


/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif 


