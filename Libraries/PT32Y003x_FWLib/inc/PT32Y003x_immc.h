 /******************************************************************************
  * @file    PT32Y003x_immc.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the IMMC firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_IMMC_H
#define PT32Y003x_IMMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

#define IMMC_Key_MainCode       ((u32)0xADEB0000) 
#define IMMC_Key_EEPROM         ((u32)0xADEB0000) 
#define IMMC_Key_INFO           ((u32)0xC5AE0000) 

#define IMMC_StartADDR_MainCode ((u32)0x00000000)
#define IMMC_EndADDR_MainCode   ((u32)0x00003FFF)

#define IMMC_StartADDR_EEPROM   ((u32)0x00003FFF)
#define IMMC_EndADDR_EEPROM     ((u32)0x000041FF)

#define IMMC_Page_Size    ((u16)0x200)	 /*!< 512B */

/** @addtogroup IMMC
  * @{
  */
#define IS_InstructionFetchWaitCycle(SEL) 	((SEL) <= 15) 

#define IS_IMMC_Prescaler(SEL) ((SEL< 64))

#define IS_IMMC_OperatMAXAddress(SEL)    ((SEL< 0x0000423F))

/** @defgroup IMMC_FLAG  **/ 
#define IMMC_FLAG_WOV               IMMC_SR_WOV
#define IMMC_FLAG_URPT              IMMC_SR_URPT
#define IMMC_FLAG_BUSY              IMMC_SR_BUSY
#define IMMC_FLAG_CERR              IMMC_SR_CERR
#define IMMC_FLAG_KERR              IMMC_SR_KERR
#define IMMC_FLAG_AERR              IMMC_SR_AERR
#define IMMC_FLAG_WTO               IMMC_SR_WTO 
#define IMMC_FLAG_IAPF              IMMC_BSR_IAPF                       
#define IMMC_FLAG_PSR               (IMMC_RPSR_PSR|0x100) 
#define IS_IMMC_FLAG(SEL)      (((SEL) == IMMC_FLAG_WOV)    || \
								((SEL) == IMMC_FLAG_URPT)   || \
								((SEL) == IMMC_FLAG_BUSY)   || \
								((SEL) == IMMC_FLAG_CERR)   || \
								((SEL) == IMMC_FLAG_KERR)   || \
                                ((SEL) == IMMC_FLAG_AERR)   || \
                                ((SEL) == IMMC_FLAG_WTO)    || \
                                ((SEL) == IMMC_FLAG_IAPF)   || \
								((SEL) == IMMC_FLAG_PSR))
                                                                                           
#define IMMC_IT_WOVI            IMMC_IE_WOVI
#define IMMC_IT_URPTI           IMMC_IE_URPTI
#define IMMC_IT_CERI            IMMC_IE_CERI
#define IMMC_IT_KERI            IMMC_IE_KERI
#define IMMC_IT_AERI            IMMC_IE_AERI
#define IMMC_IT_WTOI            IMMC_IE_WTOI                              
#define IS_IMMC_IT(SEL)        (((SEL) == IMMC_IT_WOVI)  || \
								((SEL) == IMMC_IT_URPTI) || \
								((SEL) == IMMC_IT_CERI)  || \
								((SEL) == IMMC_IT_KERI)  || \
								((SEL) == IMMC_IT_AERI)  || \
								((SEL) == IMMC_IT_WTOI))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void IMMC_SetPrescaler(u8 Prescaler);
FlagStatus IMMC_WaitIMMCFree(void);
FlagStatus IMMC_WriteWord(u32 Address, u32 Data);
u32 IMMC_ReadWord(u32 Address);
u16 IMMC_ReadHalfWord(u32 Address);
u8 IMMC_ReadByte(u32 Address);
void IMMC_ITConfig(u32 IMMC_IT, FunctionalState NewState);
FlagStatus IMMC_GetFlagStatus(u32 IMMC_FLAG);
void IMMC_ClearFlag(u32 IMMC_FLAG);
/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif 
