/******************************************************************************
  * @file    PT32Y003x_crc.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the CRC firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_CRC_H
#define PT32Y003x_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/*!< Includes ------------------------------------------------------------*/
#include "PT32Y003x.h"

#define CRC_PolyCCITT16	    0x00001021           // 0x1021
#define CRC_PolyIBM16		0x00008005           // 0x8005

/** @addtogroup CRC
  * @{
  */

/* Exported types ---------------------------------------------------------*/

/** @brief  CRC Init structure definition **/
typedef struct
{
	u32 CRC_Input;
	u32 CRC_InputBitSequenceReversal;
	u32 CRC_InputByteSequenceReversal;
	u32 CRC_OutputBitSequenceReversal;
	u32 CRC_Seed;
	u32 CRC_Poly;																														
} CRC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
#define CRC_Input_8b      0x00000000
#define CRC_Input_16b     CRC_CR_CIS
#define IS_CRC_Input(SEL)   (((SEL) == CRC_Input_8b) ||\
							 ((SEL) == CRC_Input_16b))

#define CRC_InputBitSequenceReversal_Disable		    0x00000000       
#define CRC_InputBitSequenceReversal_Enable		        CRC_CR_CISN	       
#define IS_CRC_InputBitSequenceReversal(SEL)		((SEL == CRC_InputBitSequenceReversal_Disable) || \
													 (SEL == CRC_InputBitSequenceReversal_Enable))

/** @defgroup CRC_InputByteSequenceReversal
* @{ 
*/
#define CRC_InputByteSequenceReversal_Disable		    	0x00000000	       
#define CRC_InputByteSequenceReversal_Enable		        CRC_CR_CBN     
#define IS_CRC_InputByteSequenceReversal(SEL)		((SEL == CRC_InputByteSequenceReversal_Disable) || \
													 (SEL == CRC_InputByteSequenceReversal_Enable))

/** @defgroup CRC_OutputBitSequenceReversal
* @{ 
*/
#define CRC_OutputBitSequenceReversal_Disable		    	0x00000000	      
#define CRC_OutputBitSequenceReversal_Enable		        CRC_CR_COSN	       
#define IS_CRC_OutputBitSequenceReversal(SEL)		((SEL == CRC_OutputBitSequenceReversal_Disable) || \
													 (SEL == CRC_OutputBitSequenceReversal_Enable))
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CRC_Init(CRC_InitTypeDef* CRC_InitStruct);
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct);
void CRC_Cmd(FunctionalState NewState);
void CRC_ResetDout(void);
u32 CRC_CalculateCRC(u16 CRC_Data);
u32 CRC_CalculateBlockCRC(u16 pBuffer[], u32 BufferLength);
u32 CRC_GetCRC(void);
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif


