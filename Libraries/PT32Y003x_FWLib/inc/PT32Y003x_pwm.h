/******************************************************************************
* @file    PT32Y003x_pwm.h
* @author  应用开发团队
* @version V1.6.0
* @date    2023/12/18
* @brief    This file contains all the functions prototypes for the PWM firmware library.
*
******************************************************************************
* @attention
*
*
*****************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_PWM_H
#define PT32Y003x_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

/** @defgroup PWM_ALL_PERIPH
* @{ 
*/
#define IS_PWM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1))

/** @defgroup PWM_TimeBaseInitTypeDef
* @{ 
*/
typedef struct
{
	u16 PWM_AutoReloadValue;       /*!< Specifies the value to be loaded into the Auto-Reload Register at the next update event.
																		  This parameter can be a number between 0x0000 and 0xFFFF */ 
	
	u8  PWM_ClockSource;   /*!< Specifies internal clock source.
																		  This parameter can be value of @ref PWM_InternalClockSource */
	
	u16 PWM_Prescaler; 						 /*!< Specifies the prescaler value used to divide the PCLK.
																		  This parameter can be a number between 0x0000 and 0xFFFF */
			
	u32 PWM_Direction;						 /*!< Specifies the counter mode.
																			This parameter can be value of @ref PWM_Direction */
	
	u32 PWM_CenterAlignedMode;		 /*!< Specifies the center aligned mode.
																			This parameter can be value of @ref PWM_CenterAlignedMode */
	
} PWM_TimeBaseInitTypeDef;

/** @defgroup PWM_InternalClockSource
* @{ 
*/
#define PWM_ClockSource_PCLK		0x00000000
#define PWM_ClockSource_SYSCLK	    PWM_CR1_CLKS
#define IS_PWM_ClockSource(SEL)	(((SEL) == PWM_ClockSource_PCLK) || \
								((SEL) == PWM_ClockSource_SYSCLK))

/** @defgroup PWM_Direction
* @{ 
*/
#define PWM_Direction_Up		    0x00000000
#define PWM_Direction_Down	        PWM_CR1_DIR  
#define IS_PWM_Direction(SEL)      (((SEL) == PWM_Direction_Up) || \
									((SEL) == PWM_Direction_Down))   

/** @defgroup PWM_CenterAlignedMode
* @{ 
*/
#define PWM_CenterAlignedMode_Disable	0x00000000
#define PWM_CenterAlignedMode_Enable	PWM_CR1_CMS
#define IS_PWM_CenterAlignedMode(SEL)   (((SEL) == PWM_CenterAlignedMode_Disable) || \
										 ((SEL) == PWM_CenterAlignedMode_Enable))  

/** @defgroup PWM_CH_Enum
* @{ 
*/
typedef enum
{
	PWM_Channel_1 = 0,                /*!< PWM channel 1 */
	PWM_Channel_2,                    /*!< PWM channel 2 */
	PWM_Channel_3,                    /*!< PWM channel 3 */
	PWM_Channel_4                     /*!< PWM channel 4 */
}PWM_CH_Enum;

/** @defgroup PWM_OCInitTypeDef
* @{ 
*/
typedef struct
{
	PWM_CH_Enum PWM_Channel;  
	u32 PWM_OCMode; 
	u32 PWM_OCIdleState; 
	u32 PWM_OCNIdleState;
	u32 PWM_OCOutput;  
	u32 PWM_OCNOutput;
	u16 PWM_OCValue;
	u32 PWM_OCPolarity;  
	u32 PWM_OCNPolarity;
} PWM_OCInitTypeDef;

/** @defgroup PWM_Channel
* @{ 
*/
#define IS_PWM_Channel(SEL) (((SEL) == PWM_Channel_1) ||\
                            ((SEL) == PWM_Channel_2)  ||\
                            ((SEL) == PWM_Channel_3)  ||\
                            ((SEL) == PWM_Channel_4))

/** @defgroup PWM_OCMode
* @{ 
*/
#define TIM_OCMode_Timing			(PWM_OCMR_OC1M&0x0000)
#define TIM_OCMode_PWM1				(PWM_OCMR_OC1M&0x0001)
#define TIM_OCMode_PWM2				(PWM_OCMR_OC1M&0x0002)
#define TIM_OCMode_Toggle			(PWM_OCMR_OC1M&0x0003)
#define TIM_OCMode_Active			(PWM_OCMR_OC1M&0x0004)
#define TIM_OCMode_Inactive		    (PWM_OCMR_OC1M&0x0005)
#define TIM_OCMode_CompelInactive	(PWM_OCMR_OC1M&0x0006)
#define TIM_OCMode_CompelActive		(PWM_OCMR_OC1M&0x0007)
#define IS_PWM_OCMode(SEL) (((SEL) == TIM_OCMode_Timing) ||\
                            ((SEL) == TIM_OCMode_PWM1) || \
                            ((SEL) == TIM_OCMode_PWM2) ||\
                            ((SEL) == TIM_OCMode_Toggle) || \
                            ((SEL) == TIM_OCMode_Active) ||\
                            ((SEL) == TIM_OCMode_Inactive) || \
                            ((SEL) == TIM_OCMode_CompelInactive) ||\
                            ((SEL) == TIM_OCMode_CompelActive))

/** @defgroup PWM_OCIdleState
* @{ 
*/
#define  PWM_OCIdleState_Low		0x00000000
#define  PWM_OCIdleState_High		PWM_OCMR_OIS1
#define IS_PWM_OCIdleState(SEL)	(((SEL) == PWM_OCIdleState_Low)    || \
								 ((SEL) == PWM_OCIdleState_High))

/** @defgroup PWM_OCNIdleState
* @{ 
*/
#define  PWM_OCNIdleState_Low		0x00000000
#define  PWM_OCNIdleState_High	PWM_OCMR_OIS1N
#define IS_PWM_OCNIdleState(SEL)	(((SEL) == PWM_OCNIdleState_Low)    || \
									 ((SEL) == PWM_OCNIdleState_High))	

/** @defgroup PWM_OCOutput
* @{ 
*/
#define  PWM_OCOutput_Disable	0x00000000 
#define  PWM_OCOutput_Enable	PWM_OCMR_OC1E
#define IS_PWM_OCOutput(SEL)	(((SEL) == PWM_OCOutput_Disable) || \
								 ((SEL) == PWM_OCOutput_Enable))

/** @defgroup PWM_OCNOutput
* @{ 
*/
#define  PWM_OCNOutput_Disable	    0x00000000
#define  PWM_OCNOutput_Enable		PWM_OCMR_OC1NE
#define IS_PWM_OCNOutput(SEL)	(((SEL) == PWM_OCNOutput_Disable) || \
								 ((SEL) == PWM_OCNOutput_Enable))

/** @defgroup PWM_OCPolarity
* @{ 
*/
#define  PWM_OCPolarity_High 	0x00000000
#define  PWM_OCPolarity_Low		PWM_CR3_CC1P
#define IS_PWM_OCPolarity(SEL)	(((SEL) == PWM_OCPolarity_High) || \
								 ((SEL) == PWM_OCPolarity_Low))

/** @defgroup PWM_OCNPolarity
* @{ 
*/
#define  PWM_OCNPolarity_Low 	0x00000000
#define  PWM_OCNPolarity_High   PWM_CR3_C1NP
#define IS_PWM_OCNPolarity(SEL)	(((SEL) == PWM_OCNPolarity_High) || \
								 ((SEL) == PWM_OCNPolarity_Low))

/** @defgroup PWM_ICInitTypeDef
* @{ 
*/
typedef struct
{
    PWM_CH_Enum PWM_Channel;              
    u32 PWM_ICRiseCapture;
    u32 PWM_ICFallCapture;
    u32 PWM_ICResetCounter;
    u32 PWM_ICSource;                  
} PWM_ICInitTypeDef;

/** @defgroup PWM_ICRiseCapture
* @{ 
*/
#define  PWM_ICRiseCapture_Disable	0x00000000
#define  PWM_ICRiseCapture_Enable	PWM_CAPR_IC1R         
#define  IS_PWM_ICRiseCapture(SEL)	(((SEL) == PWM_ICRiseCapture_Disable)    || \
									((SEL) == PWM_ICRiseCapture_Enable))

/** @defgroup PWM_ICFallCapture
* @{ 
*/
#define  PWM_ICFallCapture_Disable	0x00000000
#define  PWM_ICFallCapture_Enable	PWM_CAPR_IC1F
#define  IS_PWM_ICFallCapture(SEL)	(((SEL) == PWM_ICFallCapture_Disable)    || \
									 ((SEL) == PWM_ICFallCapture_Enable))	

/** @defgroup PWM_ICResetCounter
* @{ 
*/
#define  PWM_ICResetCounter_Disable	0x00000000
#define  PWM_ICResetCounter_Enable	PWM_CAPR_IC1RC
#define  IS_PWM_ICResetCounter(SEL)	(((SEL) == PWM_ICResetCounter_Disable)    || \
									 ((SEL) == PWM_ICResetCounter_Enable))	

/** @defgroup PWM_ICSource
* @{ 
*/
#define PWM_ICSource_ICS1            (PWM_CAPR_IC1S&0x00010000)
#define PWM_ICSource_ICS2            (PWM_CAPR_IC1S&0x00020000)
#define PWM_ICSource_ICS3            (PWM_CAPR_IC1S&0x00030000)
#define PWM_ICSource_ICS4            (PWM_CAPR_IC1S&0x00040000)
#define IS_PWM_ICSource(SEL) (((SEL) == PWM_ICSource_ICS1) ||\
                              ((SEL) == PWM_ICSource_ICS2) ||\
                              ((SEL) == PWM_ICSource_ICS3) ||\
                              ((SEL) == PWM_ICSource_ICS4))
                  
/** @defgroup PWM_BDTRInitTypeDef
* @{ 
*/
typedef struct
{
	u32 PWM_DeadTime;
	u32 PWM_Break;
	u32 PWM_BreakPolarity;
	u32 PWM_BreakSoftwareControl;
	u32 PWM_BreakInput; 
  u32 PWM_BreakSource;
} PWM_BDTRInitTypeDef;

/** @defgroup PWM_DeadTime
* @{ 
*/
#define IS_PWM_DeadTime(SEL)	((SEL) <4096)

/** @defgroup PWM_Break
* @{ 
*/
#define PWM_Break_Disable			0x00000000
#define PWM_Break_Enable			PWM_BDTR_BKE
#define IS_PWM_Break(SEL)	(((SEL) == PWM_Break_Disable) ||\
							 ((SEL) == PWM_Break_Enable))

/** @defgroup PWM_BreakPolarity
* @{ 
*/
#define PWM_BreakPolarity_Low			0x00000000
#define PWM_BreakPolarity_High			PWM_BDTR_BKP 
#define IS_PWM_BreakPolarity(SEL)		(((SEL) == PWM_BreakPolarity_Low) || \
                                        ((SEL) == PWM_BreakPolarity_High))

/** @defgroup PWM_BreakSoftware
* @{ 
*/
#define PWM_BreakSoftwareControl_Disable	    0x00000000
#define PWM_BreakSoftwareControl_Enable		PWM_BDTR_BKSC 
#define IS_PWM_BreakSoftwareControl(SEL)	(((SEL) == PWM_BreakSoftwareControl_Disable) || \
                                    ((SEL) == PWM_BreakSoftwareControl_Enable))

/** @defgroup PWM_BreakInput
* @{ 
*/
#define PWM_BreakInput_TIMIdle	0x00000000
#define PWM_BreakInput_TIMOFF	PWM_BDTR_BKIC
#define IS_PWM_BreakInput(SEL)	(((SEL) == PWM_BreakInput_TIMIdle) || \
                                ((SEL) == PWM_BreakInput_TIMOFF)) 
                                        

#define PWM_BreakSource_BKIN    PWM_BKICR_BKINE
#define PWM_BreakSource_PVD     PWM_BKICR_PVDE
#define PWM_BreakSource_SW      PWM_BKICR_SWE
#define IS_PWM_BreakSource(SEL)	(((SEL) == NULL)    || \
                                ((SEL) == PWM_BreakSource_BKIN)    || \
                                ((SEL) == PWM_BreakSource_PVD)      || \
                                ((SEL) == PWM_BreakSource_SW)       || \
                                ((SEL) == (PWM_BreakSource_BKIN | PWM_BreakSource_PVD)) || \
                                ((SEL) == (PWM_BreakSource_BKIN | PWM_BreakSource_SW))  || \
                                ((SEL) == (PWM_BreakSource_PVD | PWM_BreakSource_SW))   ||\
                                ((SEL) == (PWM_BreakSource_BKIN | PWM_BreakSource_PVD | PWM_BreakSource_SW))) 

                                        


/** @defgroup PWM_EventSource
* @{ 
*/
#define PWM_EventSource_Update	(PWM_CR1_UG&0x0002)
#define PWM_EventSource_Break	(PWM_BDTR_BKSC&0X80000)
#define IS_PWM_EventSource(SEL) (((SEL) == PWM_EventSource_Update) || \
								((SEL) == PWM_EventSource_Break))	

/** @defgroup PWM_RepeatTimes
* @{ 
*/
#define IS_PWM_RepeatTimes(SEL)             ((SEL) <= 0xF)

/** @defgroup PWM_ADCTrigger
* @{ 
*/
#define PWM_ADCTrigger_OC1UE                  PWM_TACR_OC1UE
#define PWM_ADCTrigger_OC1DE                  PWM_TACR_OC1DE
#define PWM_ADCTrigger_OC2UE                  PWM_TACR_OC2UE
#define PWM_ADCTrigger_OC2DE                  PWM_TACR_OC2DE
#define PWM_ADCTrigger_OC3UE                  PWM_TACR_OC3UE
#define PWM_ADCTrigger_OC3DE                  PWM_TACR_OC3DE
#define PWM_ADCTrigger_OC4UE                  PWM_TACR_OC4UE
#define PWM_ADCTrigger_OC4DE                  PWM_TACR_OC4DE
#define PWM_ADCTrigger_UOAE                   PWM_TACR_UOAE
#define PWM_ADCTrigger_DOAE                   PWM_TACR_DOAE
#define PWM_ADCTrigger_IC1RAE                 PWM_TACR_IC1RAE
#define PWM_ADCTrigger_IC1FAE                 PWM_TACR_IC1FAE
#define PWM_ADCTrigger_IC2RAE                 PWM_TACR_IC2RAE
#define PWM_ADCTrigger_IC2FAE                 PWM_TACR_IC2FAE
#define PWM_ADCTrigger_IC3RAE                 PWM_TACR_IC3RAE
#define PWM_ADCTrigger_IC3FAE                 PWM_TACR_IC3FAE
#define PWM_ADCTrigger_IC4RAE                 PWM_TACR_IC4RAE
#define PWM_ADCTrigger_IC4FAE                 PWM_TACR_IC4FAE
#define IS_PWM_ADCTrigger(SEL)      (((SEL) ==  PWM_ADCTrigger_OC1UE) || ((SEL) == PWM_ADCTrigger_OC1DE) ||\
                                    ((SEL) ==  PWM_ADCTrigger_OC2UE) || ((SEL) == PWM_ADCTrigger_OC2DE) ||\
                                    ((SEL) ==  PWM_ADCTrigger_OC3UE) || ((SEL) == PWM_ADCTrigger_OC3DE) ||\
                                    ((SEL) ==  PWM_ADCTrigger_OC4UE) || ((SEL) == PWM_ADCTrigger_OC4DE) ||\
                                    ((SEL) ==  PWM_ADCTrigger_UOAE)  || ((SEL) == PWM_ADCTrigger_DOAE)  ||\
                                    (((SEL) == PWM_ADCTrigger_IC1RAE)|| (SEL) == PWM_ADCTrigger_IC1FAE) ||\
                                    ((SEL) == PWM_ADCTrigger_IC2RAE) || ((SEL) == PWM_ADCTrigger_IC2FAE)||\
                                    ((SEL) == PWM_ADCTrigger_IC3RAE) || ((SEL) == PWM_ADCTrigger_IC3FAE)||\
                                    ((SEL) == PWM_ADCTrigger_IC4RAE) || ((SEL) == PWM_ADCTrigger_IC4FAE))

/** @defgroup PWM_IT
* @{ 
*/
#define PWM_IT_ARI                   PWM_CR2_ARI
#define PWM_IT_OC1I                  PWM_CR2_OC1I        
#define PWM_IT_OC2I                  PWM_CR2_OC2I      
#define PWM_IT_OC3I                  PWM_CR2_OC3I    
#define PWM_IT_OC4I                  PWM_CR2_OC4I      
#define PWM_IT_IC1I                  (PWM_CAPR_IC1I|0x80000)  
#define PWM_IT_IC2I                  PWM_CAPR_IC2I     
#define PWM_IT_IC3I                  PWM_CAPR_IC3I   
#define PWM_IT_IC4I                  PWM_CAPR_IC4I     
#define PWM_IT_BKI                   PWM_BDTR_BKI 
#define PWM_IT_UI                    PWM_CR2_UI
#define IS_PWM_IT(SEL)              (((SEL) == PWM_IT_ARI)  || ((SEL) == PWM_IT_OC1I)  || \
                                    ((SEL) == PWM_IT_OC2I)  || ((SEL) == PWM_IT_OC3I)  || \
                                    ((SEL) == PWM_IT_OC4I)  || ((SEL) == PWM_CAPR_IC1I)   || \
                                    ((SEL) == PWM_CAPR_IC2I)  || ((SEL) == PWM_CAPR_IC3I) || \
                                    ((SEL) == PWM_CAPR_IC4I)  || ((SEL) == PWM_BDTR_BKI)  || ((SEL) == PWM_IT_UI))
																		

/** @defgroup PWM_FLAG
* @{ 
*/
#define PWM_FLAG_ARF                    PWM_SR_ARF
#define PWM_FLAG_OC1F                   PWM_SR_OC1F        
#define PWM_FLAG_OC2F                   PWM_SR_OC2F      
#define PWM_FLAG_OC3F                   PWM_SR_OC3F      
#define PWM_FLAG_OC4F                   PWM_SR_OC4F      
#define PWM_FLAG_IC1R                	PWM_SR_IC1R     
#define PWM_FLAG_IC1F               	PWM_SR_IC1F     
#define PWM_FLAG_IC2R               	PWM_SR_IC2R     
#define PWM_FLAG_IC2F               	PWM_SR_IC2F 
#define PWM_FLAG_IC3R               	PWM_SR_IC3R     
#define PWM_FLAG_IC3F               	PWM_SR_IC3F 
#define PWM_FLAG_IC4R                	PWM_SR_IC4R     
#define PWM_FLAG_IC4F               	PWM_SR_IC4F 
#define PWM_FLAG_BIF                    PWM_SR_BIF 
#define PWM_FLAG_UIF                     PWM_SR_UIF
#define IS_PWM_FLAG(SEL)                (((SEL) == PWM_FLAG_ARF) || ((SEL) == PWM_FLAG_OC1F) || \
                                        ((SEL) == PWM_FLAG_OC2F) || ((SEL) == PWM_FLAG_OC3F) || \
                                        ((SEL) == PWM_FLAG_OC4F) || ((SEL) == PWM_FLAG_IC1R) || \
                                        ((SEL) == PWM_FLAG_IC1F) || ((SEL) == PWM_FLAG_IC2R) || \
                                        ((SEL) == PWM_FLAG_IC2F) || ((SEL) == PWM_FLAG_IC3R) || \
                                        ((SEL) == PWM_FLAG_IC3F) || ((SEL) == PWM_FLAG_IC4R) || \
                                        ((SEL) == PWM_FLAG_IC4F) || ((SEL) == PWM_FLAG_BIF)  || \
                                        ((SEL) == PWM_FLAG_UIF))		

/*! function declaration and definition*/
void PWM_TimeBaseInit(PWM_TypeDef* PWMx, PWM_TimeBaseInitTypeDef* TimeBaseInit);
void PWM_TimeBaseStructInit(PWM_TimeBaseInitTypeDef* TimeBaseInit);
void PWM_OCInit(PWM_TypeDef* PWMx, PWM_OCInitTypeDef* OutInit);
void PWM_OCStructInit(PWM_OCInitTypeDef* OutInit);
void PWM_ICInit(PWM_TypeDef* PWMx, PWM_ICInitTypeDef* CapInit);
void PWM_ICStructInit(PWM_ICInitTypeDef* CapInit);
void PWM_BDTRInit(PWM_TypeDef* PWMx, PWM_BDTRInitTypeDef* BDTRInit);
void PWM_BDTRStructInit(PWM_BDTRInitTypeDef* BDTRInit,u32 DeadTime);
void PWM_SetInterruptAutoreload(PWM_TypeDef* PWMx, u8 value);
void PWM_SetAutoreload(PWM_TypeDef* PWMx, u16 value);
void PWM_SetPrescaler(PWM_TypeDef* PWMx, u16 value);
void PWM_SetOCxValue(PWM_TypeDef* PWMx, u8 PWM_Channel, u16 value);
void PWM_SetICxValue(PWM_TypeDef* PWMx, u8 PWM_Channel, u16 value);
u16 PWM_GetICxValue(PWM_TypeDef* PWMx, u8 PWM_Channel);
u16 PWM_GetCounter(PWM_TypeDef* PWMx);
u16 PWM_GetAutoreload(PWM_TypeDef* PWMx);
u16 PWM_GetPrescaler(PWM_TypeDef* PWMx);
void PWM_GenerateEvent(PWM_TypeDef* PWMx,u32 PWM_EventSource);
void PWM_Cmd(PWM_TypeDef* PWMx, FunctionalState NewState);
void PWM_ITConfig(PWM_TypeDef* PWMx, u32 PWM_IT, FunctionalState NewState);
FlagStatus PWM_GetFlagStatus(PWM_TypeDef* PWMx, u32 PWM_FLAG);
void PWM_ClearFlag(PWM_TypeDef* PWMx, u32 PWM_FLAG);
void PWM_ADCTrigger(PWM_TypeDef* PWMx,u32 CountMode);
void PWM_SoftwareBreak_CMD(PWM_TypeDef *PWMx, FunctionalState NewState);
/**
  * @}
  */

  
#ifdef __cplusplus
}
#endif

#endif


