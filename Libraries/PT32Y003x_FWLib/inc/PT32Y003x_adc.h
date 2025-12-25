  /******************************************************************************
  * @file   PT32Y003x_adc.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief   This file contains all the functions prototypes for the ADC firmware library
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_ADC_H
#define PT32Y003x_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/** @addtogroup ADC
  * @{
  */


/* Exported types ------------------------------------------------------------*/

/** @brief  ADC Init structure definition **/
typedef struct
{
    u8 ADC_Prescaler;										
    u32 ADC_Mode;													
    u32 ADC_TriggerSource;								
    u32 ADC_TimerTriggerSource;						
    u32 ADC_Align;												
    u32 ADC_Channel;										
    u32 ADC_BGVoltage;																															 
    u32 ADC_ReferencePositive;		
}ADC_InitTypeDef;


#define	ADC_ScanChannel_0 0
#define	ADC_ScanChannel_1 1
#define	ADC_ScanChannel_2 2
#define	ADC_ScanChannel_3 3
#define	ADC_ScanChannel_4 4
#define	ADC_ScanChannel_5 5
#define	ADC_ScanChannel_6 6
#define	ADC_ScanChannel_7 7
#define	ADC_ScanChannel_8 8

#define IS_ADC_ALL_PERIPH(PERIPH)   ((PERIPH) == ADC)

/** @defgroup ADC_MODE_SEL **/
#define ADC_Mode_Single		    0x00000000
#define ADC_Mode_Continuous     ADC_CR1_MODE
#define IS_ADC_Mode(SEL)        (((SEL) == ADC_Mode_Single) ||\
								 ((SEL) == ADC_Mode_Continuous))

#define ADC_TriggerSource_Software       0x00000000
#define ADC_TriggerSource_Timer         (ADC_CR1_TRIGS&0x00000004)
#define ADC_TriggerSource_ExternalPin   (ADC_CR1_TRIGS&0x00000008)
#define IS_ADC_TriggerSource(SEL)    (((SEL) == ADC_TriggerSource_Software) ||\
                                      ((SEL) == ADC_TriggerSource_Timer)  ||\
                                      ((SEL) == ADC_TriggerSource_ExternalPin))  

/** @defgroup IS_ADC_TIMS_SEL **/
#define ADC_TimerTriggerSource_TIM1ADC       0x00000010
#define ADC_TimerTriggerSource_TIM2ADC       (ADC_CR1_TIMS&0x00000020)
#define ADC_TimerTriggerSource_TIM3ADC       (ADC_CR1_TIMS&0x00000030)
#define IS_ADC_TimerTriggerSource(SEL)	    (((SEL) == ADC_TimerTriggerSource_TIM1ADC) ||\
                                             ((SEL) == ADC_TimerTriggerSource_TIM2ADC) ||\
                                             ((SEL) == ADC_TimerTriggerSource_TIM3ADC))

                                          
/** @defgroup IS_ADC_ALIGN_SEL **/
#define ADC_Align_Right	        0x00000000
#define ADC_Align_Left	        ADC_CR1_ALIGN
#define IS_ADC_Align(SEL)       (((SEL) == ADC_Align_Right) ||\
								 ((SEL) == ADC_Align_Left))

/** @defgroup IS_ADC_BGS_SEL **/
#define ADC_BGVoltage_BG1v2      0x00000000
#define ADC_BGVoltage_BG1v0      ADC_CR1_BGS
#define IS_ADC_BGVoltage(SEL)    (((SEL) == ADC_BGVoltage_BG1v2) ||\
								  ((SEL) == ADC_BGVoltage_BG1v0))
                                                                                                                                                      
/** @defgroup IS_ADC_ADVRPS_SEL **/
#define ADC_ReferencePositive_VDD       0x00000000
#define ADC_ReferencePositive_BG2v0     (ADC_CR1_ADVRPS&0x100)
#define ADC_ReferencePositive_AVREF     (ADC_CR1_ADVRPS&0x200)
#define IS_ADC_ReferencePositive(SEL)  (((SEL) == ADC_ReferencePositive_VDD)   || \
                                        ((SEL) == ADC_ReferencePositive_BG2v0) || \
                                        ((SEL) == ADC_ReferencePositive_AVREF))

#define ADC_Channel_0       0x00000000
#define ADC_Channel_1       (ADC_CR1_CHS&0x10000)
#define ADC_Channel_2       (ADC_CR1_CHS&0x20000)
#define ADC_Channel_3       (ADC_CR1_CHS&0x30000)
#define ADC_Channel_4       (ADC_CR1_CHS&0x40000)
#define ADC_Channel_5       (ADC_CR1_CHS&0x50000)
#define ADC_Channel_6       (ADC_CR1_CHS&0x60000)
#define ADC_Channel_7       (ADC_CR1_CHS&0x70000)
#define ADC_Channel_8       (ADC_CR1_CHS&0x80000)
#define ADC_Channel_9       (ADC_CR1_CHS&0x90000)
#define ADC_Channel_10      (ADC_CR1_CHS&0xA0000)
#define ADC_Channel_11      (ADC_CR1_CHS&0xB0000)
#define ADC_Channel_12      (ADC_CR1_CHS&0xC0000)
#define ADC_Channel_13      (ADC_CR1_CHS&0xD0000)
#define IS_ADC_Channel(SEL)	       (((SEL) == ADC_Channel_0)  || ((SEL) == ADC_Channel_1)  ||\
									((SEL) == ADC_Channel_2)  || ((SEL) == ADC_Channel_3)  ||\
									((SEL) == ADC_Channel_4)  || ((SEL) == ADC_Channel_5)  ||\
									((SEL) == ADC_Channel_6)  || ((SEL) == ADC_Channel_7)  ||\
									((SEL) == ADC_Channel_8)  || ((SEL) == ADC_Channel_9)  ||\
									((SEL) == ADC_Channel_10) || ((SEL) == ADC_Channel_11) ||\
                                    ((SEL) == ADC_Channel_12) || ((SEL) == ADC_Channel_13))

/** @defgroup IS_ADC_SMP_SEL **/                                     
#define IS_ADC_SampleTime(SEL)	      ((SEL) > 0x02 && ((SEL) < 0xFF))	

#define ADC_AverageTimes_1     (ADC_CR2_AVGT&0x00000000)         
#define ADC_AverageTimes_2     (ADC_CR2_AVGT&0x01000000)         
#define ADC_AverageTimes_4     (ADC_CR2_AVGT&0x02000000)         
#define ADC_AverageTimes_8     (ADC_CR2_AVGT&0x03000000)        
#define ADC_AverageTimes_16    (ADC_CR2_AVGT&0x04000000)        
#define ADC_AverageTimes_32    (ADC_CR2_AVGT&0x05000000)         
#define ADC_AverageTimes_64    (ADC_CR2_AVGT&0x06000000)         
#define ADC_AverageTimes_128   (ADC_CR2_AVGT&0x07000000) 
#define IS_ADC_AverageTimes(SEL)       (((SEL)==ADC_AverageTimes_1)||\
                                        ((SEL)==ADC_AverageTimes_2)||\
                                        ((SEL)==ADC_AverageTimes_4)||\
                                        ((SEL)==ADC_AverageTimes_8)||\
                                        ((SEL)==ADC_AverageTimes_16)||\
                                        ((SEL)==ADC_AverageTimes_32)||\
                                        ((SEL)==ADC_AverageTimes_64)||\
                                        ((SEL)==ADC_AverageTimes_128))
/** @defgroup IS_ADC_GET_FLAG **/  
#define ADC_FLAG_RDY                ADC_SR_RDY                    
#define ADC_FLAG_EOC                ADC_SR_EOC 
#define ADC_FLAG_EOS                ADC_SR_EOS
#define IS_ADC_FLAG(SEL)            (((SEL) == ADC_FLAG_RDY)    || \
                                     ((SEL) == ADC_FLAG_EOC)    || \
                                     ((SEL) == ADC_FLAG_EOS))
                                     
                                     
#define ADC_IT_EOC          ADC_CR1_EOCIE
#define ADC_IT_EOS          ADC_CR1_EOSIE                   
#define IS_ADC_IT(SEL)      (((SEL)==ADC_IT_EOC)||\
                             ((SEL)==ADC_IT_EOS))
                            
#define IS_ADC_ScanChannel(SEL)     ((SEL)<=7)	

#define IS_ADC_ScanChannelNumber(SEL)       (((SEL)>=2)&&((SEL)<=8))	
#define ReferenceNegative_VSS  0X0
#define ReferenceNegative_INN  ADC_CR1_INNS
#define IS_ADC_ReferenceNegative(SEL)       (SEL==ReferenceNegative_VSS)||(SEL==ReferenceNegative_INN)                        
                            
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ChannelConfig(ADC_TypeDef* ADCx, u32 ADC_Channel);
void ADC_StartOfConversion(ADC_TypeDef* ADCx);
u16 ADC_GetConversionValue(ADC_TypeDef* ADCx);
void ADC_ITConfig(ADC_TypeDef* ADCx, u32 ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u32 ADC_FLAG);
void ADC_AverageCmd(ADC_TypeDef* ADCx,FunctionalState NewState);
void ADC_AverageTimesConfig(ADC_TypeDef* ADCx,u32 Times);
void ADC_ReadyTimeConfig(ADC_TypeDef* ADCx,u32 ReadyTime);
void ADC_SampleTimeConfig(ADC_TypeDef* ADCx, u8 SampleTime);
void ADC_ScanCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ScanChannelConfig(ADC_TypeDef* ADCx,u32 ADC_Channel,u32 ScanChannel);
void ADC_ScanChannelNumberConfig(ADC_TypeDef* ADCx,u32 ScanNumber);
u16 ADC_GetScanData(ADC_TypeDef* ADCx,u32 ScanChannel);
void ADC_RefNegativeConfig(ADC_TypeDef* ADCx,u32 RefN);
void ADC_BGVoltageConfig(ADC_TypeDef *ADCx,u32 SEL);
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif


