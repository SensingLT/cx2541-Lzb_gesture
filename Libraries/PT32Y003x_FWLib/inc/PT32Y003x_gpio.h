 /******************************************************************************
  * @file    PT3Y003x_gpio.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the GPIO firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_GPIO_H
#define PT32Y003x_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/** @addtogroup GPIO
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || ((PERIPH) == GPIOB) || ((PERIPH) == GPIOC) || ((PERIPH) == GPIOD))

#define IS_AFIO_ALL_PERIPH(PERIPH) (((PERIPH) == AFIOA) || ((PERIPH) == AFIOB) || ((PERIPH) == AFIOC) || ((PERIPH) == AFIOD))
                                                                        
typedef enum
{
	GPIO_Mode_In   = 0x00, 	
	GPIO_Mode_OutPP,         	
	GPIO_Mode_OutOD,
} GPIO_ModeInitTypeDef;
#define IS_GPIO_Mode(SEL)  (((SEL) == GPIO_Mode_In)    ||\
                            ((SEL) == GPIO_Mode_OutPP) ||\
                            ((SEL) == GPIO_Mode_OutOD))

typedef enum
{
	GPIO_Pull_NoPull = 0x00,
	GPIO_Pull_Up,     
	GPIO_Pull_Down,   
} GPIO_PullInitTypeDef;
#define IS_GPIO_Pull(SEL)  (((SEL) == GPIO_Pull_NoPull) ||\
                            ((SEL) == GPIO_Pull_Up)     ||\
                            ((SEL) == GPIO_Pull_Down))

/** @brief  GPIO Init structure definition **/
typedef struct
{
	u32 GPIO_Pin;              
	GPIO_ModeInitTypeDef GPIO_Mode;     
	GPIO_PullInitTypeDef GPIO_Pull;    
} GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
#define GPIO_Pin_0                 ((u16)0x0001)  //!< Pin 0 selected    
#define GPIO_Pin_1                 ((u16)0x0002)  //!< Pin 1 selected    
#define GPIO_Pin_2                 ((u16)0x0004)  //!< Pin 2 selected    
#define GPIO_Pin_3                 ((u16)0x0008)  //!< Pin 3 selected    
#define GPIO_Pin_4                 ((u16)0x0010)  //!< Pin 4 selected    
#define GPIO_Pin_5                 ((u16)0x0020)  //!< Pin 5 selected    
#define GPIO_Pin_6                 ((u16)0x0040)  //!< Pin 6 selected    
#define GPIO_Pin_7                 ((u16)0x0080)  //!< Pin 7 selected    
#define GPIO_Pin_8                 ((u16)0x0100)  //!< Pin 8 selected    
#define GPIO_Pin_9                 ((u16)0x0200)  //!< Pin 9 selected    
#define GPIO_Pin_10                ((u16)0x0400)  //!< Pin 10 selected   
#define GPIO_Pin_11                ((u16)0x0800)  //!< Pin 11 selected   
#define GPIO_Pin_12                ((u16)0x1000)  //!< Pin 12 selected   
#define GPIO_Pin_13                ((u16)0x2000)  //!< Pin 13 selected   
#define GPIO_Pin_14                ((u16)0x4000)  //!< Pin 14 selected   
#define GPIO_Pin_15                ((u16)0x8000)  //!< Pin 15 selected   
#define GPIO_Pin_All               ((u16)0xFFFF)  //!< All pins selected 
#define IS_GPIO_Pin(SEL)        ((((SEL) & (u32)0xffff0000) == 0) && ((SEL) != (u32)0x0000))
                                         							
/** @brief  AF Primary selection **/
#define AFIO_AF_None	     ((u8)0x00)
#define AFIO_AF_0            ((u8)0x01)	/** @brief  AF 0 selection **/
#define AFIO_AF_1            ((u8)0x02)	/** @brief  AF 1 selection **/
#define AFIO_AF_2            ((u8)0x03)	/** @brief  AF 2 selection **/
#define AFIO_AF_3            ((u8)0x04)	/** @brief  AF 3 selection **/
#define AFIO_AF_4            ((u8)0x05)	/** @brief  AF 4 selection **/
#define AFIO_AF_5            ((u8)0x06)	/** @brief  AF 5 selection **/
#define AFIO_AF_6            ((u8)0x07)	/** @brief  AF 6 selection **/
#define IS_AFIO_AF(SEL)    (((SEL) == AFIO_AF_None) || ((SEL) == AFIO_AF_0)  ||\
                            ((SEL) == AFIO_AF_1)    || ((SEL) == AFIO_AF_2)  ||\
                            ((SEL) == AFIO_AF_3)    || ((SEL) == AFIO_AF_4)  ||\
                            ((SEL) == AFIO_AF_5)    || ((SEL) == AFIO_AF_6))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
u16 GPIO_ReadData(GPIO_TypeDef* GPIOx);
u8 GPIO_ReadDataBit(GPIO_TypeDef* GPIOx, u32 GPIO_Pin);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u32 GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u32 GPIO_Pin);
void GPIO_ReverseBits(GPIO_TypeDef* GPIOx, u32 GPIO_Pin);
void GPIO_WriteDataBit(GPIO_TypeDef* GPIOx, u32 GPIO_Pin, BitAction Action);
void GPIO_WriteData(GPIO_TypeDef* GPIOx, u16 PortVal);
void GPIO_AnalogRemapConfig(AFIO_TypeDef* AFIOx, u32 GPIO_Pin, FunctionalState NewState);
void GPIO_DigitalRemapConfig(AFIO_TypeDef* AFIOx, u32 GPIO_Pin, u8 AFIO_AF, FunctionalState NewState);
void GPIO_SetMASKLPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_ResetMASKLPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_SetMASKHPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_ResetMASKHPin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_PullUpConfig(GPIO_TypeDef *GPIOx, u32 GPIO_Pin, FunctionalState NewState);
void GPIO_PullDownConfig(GPIO_TypeDef *GPIOx, u32 GPIO_Pin, FunctionalState NewState);
/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif 


