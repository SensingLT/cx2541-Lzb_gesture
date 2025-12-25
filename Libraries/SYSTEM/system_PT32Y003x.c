/**
  ******************************************************************************
  * @file    system_PT32Y003x.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 当前的固件仅供指导, 目的是向客户提供有关其产品的编码信息,以节省他们的时间。 
  * 对于因此类固件的内容/或客户使用其中包含的编码信息而引起的任何索赔,
  * Pai-IC不对任何直接， 间接或继发的损害负责。
  * 
  * (C) 版权所有Pai-IC Microelectronics  
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"

/**
  * @}
  */
void Wait_ClockReady(void)
{
	u8 i,j;
	for(i=0; i<100; i++)
		for(j=0; j<48; j++);
}



//<<< Use Configuration Wizard in Context Menu >>>
/*--------------------- Clock Configuration ----------------------------------
//    <h> HSE配置(4~25M)
//      <q0>    使能
//                <i> 默认 = DISABLE
//    </h>
//    <h> HSI配置(48M)
//      <q1>    使能
//                <i> 默认 = ENABLE
//    </h>
//
//    <h> PLL配置
//      <q2>    使能
//                <i> 默认  = DISABLE
//    </h>
//    <h> 系统时钟配置(SYSCLK)
//      <o3>    系统时钟源
//                <0=> HSI
//                <1=> HSE
//                <2=> PLL
//                <i> 默认系统时钟源 = HSI
//      <o4>  AHB分频
//                <0=> 0
//                <1=> 2
//                <2=> 3
//                <3=> 4
//                <4=> 5
//                <5=> 6
//                <6=> 7
//                <7=> 8
//                <8=> 9
//                <9=> 10
//                <10=> 11
//                <11=> 12
//                <12=> 13
//                <13=> 14
//                <14=> 15
//                <15=> 16
//                <16=> 17
//                <17=> 18
//                <18=> 19
//                <19=> 20
//                <20=> 21
//                <21=> 22
//                <22=> 23
//                <23=> 24
//                <24=> 25
//                <25=> 26
//                <26=> 27
//                <27=> 28
//                <28=> 29
//                <29=> 30
//                <30=> 31
//                <31=> 32
//                <i> 默认分频 = 1
//      <o5>    APB分频
//                <0=> 0
//                <1=> 2
//                <2=> 3
//                <3=> 4
//                <4=> 5
//                <5=> 6
//                <6=> 7
//                <7=> 8
//                <8=> 9
//                <9=> 10
//                <10=> 11
//                <11=> 12
//                <12=> 13
//                <13=> 14
//                <14=> 15
//                <15=> 16
//                <16=> 17
//                <17=> 18
//                <18=> 19
//                <19=> 20
//                <20=> 21
//                <21=> 22
//                <22=> 23
//                <23=> 24
//                <24=> 25
//                <25=> 26
//                <26=> 27
//                <27=> 28
//                <28=> 29
//                <29=> 30
//                <30=> 31
//                <31=> 32
//                <i> 默认分频= 1
//    </h>
//
//
//    <h>  MCO输出配置
//      <e6>    MCO输出使能
//                <i> 默认 = DISABLE 
//        <o7>   MCO输出时钟
//                <0=> HSI时钟
//                <1=> HSE时钟
//                <2=> PLL时钟
//                <3=> LSI时钟
//                <4=> 系统主时钟
//        <o8>    MCO输出引脚
//                <0=> PC4
//        <o9>   MCO输出分频
//                <0=> 1
//                <1=> 2
//                <2=> 4
//                <3=> 8
//                <4=> 16
//    </e>
//    </h>
//
//    <o10>当前HSE频率
//    <i>Default: 25000000 (Unit:Hz)
//    <0-25000000>
*/


/** @defgroup CLK_Private_Defines
  * @{
  */

#define EOSC_HSE_ENABLE	(0)     /*!< 0: DISABLE,    1: ENABLE                                     */
#define IOSC_HSI_ENABLE	(1)     /*!< 0: DISABLE,    1: ENABLE                                     */
#define IOSC_PLL_ENABLE	(0)     /*!< 0: DISABLE,    1: ENABLE                                     */
#define SystemClockSEL  (0)     /*!< 0: HSI,        1: HSE,     2: PLL,                           */
#define AHB_Prescaler	  (0)    /*!< 0: DIV1,       1: DIV1,    2: DIV1,    ......      31: DIV1  */ 
#define APB_Prescaler	  (0)     /*!< 0: DIV1,       1: DIV1,    2: DIV1,    ......      31: DIV1  */ 
#define MCO_ENABLE	    (0)     /*!< 0: DISABLE,    1: ENABLE                                     */
#define MCO_SourceSEL   (4)     /*!< 0: HSI,        1: HSE,     2: PLL,     3: LSI,     4: SYSCLK */
#define MCO_PINSEL	    (0)     /*!< 0: PC4                                                       */
#define MCO_prescale	  (0)     /*!< 0: DIV1,       1: DIV2,    2: DIV4,    3: DIV8,    4: DIV16  */
#define CrystalOscillator_Freq (25000000)

/**
  * @}
  */


/** @defgroup CLK_Private_Functions
  * @{
  */


/**
* @brief 时钟源配置
* @param IOSC_HSI_ENABLE    配置向导指定,片内RC8M时钟使能控制
* @param EOSC_CLK_ENABLE	配置向导指定,外部高频时钟使能控制
* @param EOSC_LSI_ENABLE	配置向导指定,外部低频时钟使能控制
* @retval None
*/
void CLOCK_Cmd(void)
{
    #if (EOSC_HSE_ENABLE == 1)
        GPIO_DigitalRemapConfig(AFIOA,GPIO_Pin_1,AFIO_AF_0,ENABLE);
        GPIO_DigitalRemapConfig(AFIOA,GPIO_Pin_2,AFIO_AF_0,ENABLE);  
				RCC_ClockSourceConfig(RCC_ClockSource_HSE, ENABLE);	
        while(!(RCC_GetFlagStatus(RCC_FLAG_RDY)));
	#else
				RCC_ClockSourceConfig(RCC_ClockSource_HSE, DISABLE);			
	#endif
    
    #if (IOSC_HSI_ENABLE == 1)
        RCC_ClockSourceConfig(RCC_ClockSource_HSI, ENABLE);		
	#else
				RCC_ClockSourceConfig(RCC_ClockSource_HSI, DISABLE);	
	#endif
       
    #if (IOSC_PLL_ENABLE == 1)
        #if (EOSC_HSE_ENABLE == 0)
        #error "PLL时钟开启失败：EOSC_HSE 尚未使能"
        #else
        RCC_ClockSourceConfig(RCC_ClockSource_PLL, ENABLE);		
        #endif		
	#else
				RCC_ClockSourceConfig(RCC_ClockSource_PLL, DISABLE);		
	#endif
}

/**
* @brief 系统主时钟设置
* @param HCLK_SRC		配置向导指定,参数如下
*     @arg 0: 主时钟源选择内部RC32K
*     @arg 1: 主时钟源选择外部高速时钟
*     @arg 2: 主时钟源选择内部PLL倍频时钟
*     @arg 3: 主时钟源选择内部低频时钟
* @param HCLK_DIV		配置向导指定,HCLK的分频系数
* @param PCLK_DIV		配置向导指定,PCLK的分频系数
* @retval None
*/
void CLOCK_SystemClockConfig(void)
{
    #if (SystemClockSEL == 0 )
		#if (IOSC_HSI_ENABLE == 0)
			#error "系统时钟源错误：IOSC_HSI未使能"
		#else
			RCC_SetSystemClock(RCC_SystemClock_HSI);
		#endif
	#endif
    
    #if (SystemClockSEL == 1 )
		#if (EOSC_HSE_ENABLE == 0)
			#error "系统时钟源错误：EOSC_HSE未使能"
		#else
      Wait_ClockReady();
			RCC_SetSystemClock(RCC_SystemClock_HSE);
      if (IOSC_HSI_ENABLE == 0)	RCC_ClockSourceConfig(RCC_ClockSource_HSI, DISABLE);
		#endif
	#endif
    
    #if (SystemClockSEL == 2 )
		#if (IOSC_PLL_ENABLE == 0)
			#error "系统时钟源错误：IOSC_PLL未使能"
		#else
			#if (IOSC_HSE_ENABLE == 1024)
					#error "系统时钟源错误：EOSC_HSE未使能"
			#endif
			Wait_ClockReady();
			RCC_SetSystemClock(RCC_SystemClock_PLL);
			if (IOSC_HSI_ENABLE == 0)	RCC_ClockSourceConfig(RCC_ClockSource_HSI, DISABLE);
		#endif
	#endif
    
  RCC_HCLKSetPrescaler(AHB_Prescaler);	//HCLK分频选择
	RCC_PCLKSetPrescaler(APB_Prescaler);	//PCLK分频选择
	
	if((RCC_GetSystemClockSelection())!= SystemClockSEL)	//系统时钟选择错误
	{
		while(1);
	}
	RCC_SetSystemClockAfterWakeUp(RCC_SystemClockAfterWakeUp_PreviousClock);
}

/**
* @brief 系统主时钟输出配置
* @param MCO_ENABLE	配置向导指定,系统主时钟输出使能
* @param MCO_PINSEL		配置向导指定,参数如下
*     @arg 0: 系统主时钟输出到PA8
*     @arg 1: 系统主时钟输出到PD1
* @param MCO_DIV		系统主时钟输出的分频控制
* @retval None
*/
void CLOCK_MCOConfig(void)
{   
    #if (MCO_ENABLE == 1)
		#if (MCO_SourceSEL == 0 )
			#if (IOSC_HSI_ENABLE == 0)
				#error "系统时钟源错误：IOSC_36M 尚未使能"
			#else
				RCC_SetMCOSource(RCC_ClockOutput_HSI);
			#endif
		#endif
		
		#if (MCO_SourceSEL == 1 )
			#if (EOSC_HSE_ENABLE == 0)
				#error "系统时钟源错误：EOSC_CLK 尚未使能"
			#else
				RCC_SetMCOSource(RCC_ClockOutput_HSE);
			#endif
		#endif
		
		#if (MCO_SourceSEL == 2 )
			#if (IOSC_PLL_ENABLE == 0)
				#error "系统时钟源错误：PLL_CLK 尚未使能"
			#else
				RCC_SetMCOSource(RCC_ClockOutput_PLL);
			#endif
		#endif
		
		#if (MCO_SourceSEL == 3 )
			RCC_ClockSourceConfig(RCC_ClockSource_LSI, ENABLE);
			RCC_SetMCOSource(RCC_ClockOutput_LSI);
		#endif
		
		#if (MCO_SourceSEL == 4 )
			RCC_SetMCOSource(RCC_ClockOutput_SYS);
		#endif
		
		#if (MCO_PINSEL == 0)
			GPIO_DigitalRemapConfig(AFIOC,GPIO_Pin_4,AFIO_AF_0,ENABLE);
		#endif
			RCC_MCOSetPrescaler(MCO_prescale);
    #endif
}
/**
* @brief 获取系统时钟
* @param none
* @retval None
*/
u32 CLOCK_GetSYSCLK(void)
{
	u32 SystemCoreClock;
	switch(SystemClockSEL)
	{
		case 0:
			SystemCoreClock=RCC_Freq_HSI;
			break;
			
		case 1:
			SystemCoreClock=CrystalOscillator_Freq;
			break;
						
		case 2:
			SystemCoreClock=CrystalOscillator_Freq*2;
			break;
			
		default:
			break;
	}
	return SystemCoreClock;
}

/**
* @brief 系统时钟初始化
* @param none
* @retval None
*/
extern  void Retrim(void);
void SystemInit (void)
{
	Retrim();
	/* 时钟使能配置 */
	CLOCK_Cmd();
	/* 系统主时钟选择配置 */
	CLOCK_SystemClockConfig();
	/* 系统主时钟输出配置 */
	CLOCK_MCOConfig();
}

//<<< end of configuration section >>>

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */


/******************* (C) 版权所有 Pai-IC Microelectronics *****END OF FILE****/

