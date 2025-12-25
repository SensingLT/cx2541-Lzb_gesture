 /******************************************************************************
  * @file    PT32Y003x_exti.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2020/2/14
  * @brief    This file contains all the functions prototypes for the EXTI firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_EXTI_H
#define PT32Y003x_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/** @addtogroup EXTI
  * @{
  */
  
/* Exported types ------------------------------------------------------------*/

#define IS_EXTI_ALL_PERIPH(PERIPH) (((PERIPH) == EXTIA) || ((PERIPH) == EXTIB) || ((PERIPH) == EXTIC) || ((PERIPH) == EXTID))
                                    
typedef enum
{
	EXTI_Trigger_Rising,
	EXTI_Trigger_Falling,
	EXTI_Trigger_RisingFalling,
	EXTI_Trigger_HighLevel,
	EXTI_Trigger_LowLevel
} EXTI_Trigger;
#define IS_EXTI_Trigger(SEL)	(((SEL) == EXTI_Trigger_Rising) || \
								((SEL) == EXTI_Trigger_Falling) || \
								((SEL) == EXTI_Trigger_RisingFalling) || \
								((SEL) == EXTI_Trigger_HighLevel) || \
								((SEL) == EXTI_Trigger_LowLevel))
                                                    
/**  @brief IS_EXTI_PIN_SEL&GET  definition **/
#define EXTI_Pin_0		((u32)0x0001)		/* Pin 0 selected    */
#define EXTI_Pin_1		((u32)0x0002)		/* Pin 1 selected    */
#define EXTI_Pin_2		((u32)0x0004)		/* Pin 2 selected    */
#define EXTI_Pin_3		((u32)0x0008)		/* Pin 3 selected    */
#define EXTI_Pin_4		((u32)0x0010)		/* Pin 4 selected    */
#define EXTI_Pin_5		((u32)0x0020)		/* Pin 5 selected    */
#define EXTI_Pin_6		((u32)0x0040)		/* Pin 6 selected    */
#define EXTI_Pin_7		((u32)0x0080)		/* Pin 7 selected    */
#define EXTI_Pin_8		((u32)0x0100)		/* Pin 8 selected    */
#define EXTI_Pin_9		((u32)0x0200)		/* Pin 9 selected    */
#define EXTI_Pin_10		((u32)0x0400)		/* Pin 10 selected   */
#define EXTI_Pin_11		((u32)0x0800)		/* Pin 11 selected   */
#define EXTI_Pin_12		((u32)0x1000)		/* Pin 12 selected   */
#define EXTI_Pin_13		((u32)0x2000)		/* Pin 13 selected   */
#define EXTI_Pin_14		((u32)0x4000)		/* Pin 14 selected   */
#define EXTI_Pin_15		((u32)0x8000)		/* Pin 15 selected   */
#define EXTI_Pin_All	((u32)0xFFFF)		/* All pins selected */
#define IS_EXTI_Pin(SEL)        ((((SEL) & (u32)0xffff0000) == 0) && ((SEL) != (u32)0x0000))
      
/**  @brief IS_EXTI_IT_SEL&GET **/
#define EXTI_IT_0	  	((u32)0x0001)		/* Port interrupt selected 0 */
#define EXTI_IT_1	   	((u32)0x0002)		/* Port interrupt selected 1 */
#define EXTI_IT_2	  	((u32)0x0004)		/* Port interrupt selected 2 */
#define EXTI_IT_3		((u32)0x0008)		/* Port interrupt selected 3 */
#define EXTI_IT_4	  	((u32)0x0010)		/* Port interrupt selected 4 */
#define EXTI_IT_5		((u32)0x0020)		/* Port interrupt selected 5 */
#define EXTI_IT_6		((u32)0x0040)		/* Port interrupt selected 6 */
#define EXTI_IT_7		((u32)0x0080)		/* Port interrupt selected 7 */
#define EXTI_IT_8	  	((u32)0x0100)		/* Port interrupt selected 8 */
#define EXTI_IT_9		((u32)0x0200)		/* Port interrupt selected 9 */
#define EXTI_IT_10		((u32)0x0400)		/* Port interrupt selected 10 */
#define EXTI_IT_11		((u32)0x0800)		/* Port interrupt selected 11 */
#define EXTI_IT_12		((u32)0x1000)		/* Port interrupt selected 12 */
#define EXTI_IT_13		((u32)0x2000)		/* Port interrupt selected 13 */
#define EXTI_IT_14		((u32)0x4000)		/* Port interrupt selected 14 */
#define EXTI_IT_15		((u32)0x8000)		/* Port interrupt selected 15 */
#define EXTI_IT_All		((u32)0xFFFF)		/* Port interrupt selected All */
#define IS_EXTI_IT(SEL)        ((((SEL) & (u32)0xffff0000) == 0) && ((SEL) != (u32)0x0000))

#define EXTI_FLAG_0		((u16)0x0001)		
#define EXTI_FLAG_1		((u16)0x0002)		
#define EXTI_FLAG_2		((u16)0x0004)		
#define EXTI_FLAG_3		((u16)0x0008)		
#define EXTI_FLAG_4		((u16)0x0010)		
#define EXTI_FLAG_5		((u16)0x0020)		
#define EXTI_FLAG_6		((u16)0x0040)		
#define EXTI_FLAG_7		((u16)0x0080)		
#define EXTI_FLAG_8		((u16)0x0100)		
#define EXTI_FLAG_9		((u16)0x0200)		
#define EXTI_FLAG_10	((u16)0x0400)		
#define EXTI_FLAG_11	((u16)0x0800)		
#define EXTI_FLAG_12	((u16)0x1000)		
#define EXTI_FLAG_13	((u16)0x2000)		
#define EXTI_FLAG_14	((u16)0x4000)		
#define EXTI_FLAG_15	((u16)0x8000)		
#define EXTI_FLAG_All	((u16)0xFFFF)		
#define IS_EXTI_FLAG(SEL)        ((((SEL) & (u32)0xffff0000) == 0) && ((SEL) != (u32)0x0000))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void EXTI_ITConfig(EXTI_TypeDef* EXTIx, u32 EXTI_IT, FunctionalState NewState);
void EXTI_TriggerTypeConfig(EXTI_TypeDef* EXTIx, u32 EXTI_Pin, EXTI_Trigger TriggerType);
void EXTI_ClearFlag(EXTI_TypeDef* EXTIx, u32 EXTI_IT_FLAG);
ITStatus EXTI_GetITStatus(EXTI_TypeDef* EXTIx, u32 EXTI_IT);
/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif 


