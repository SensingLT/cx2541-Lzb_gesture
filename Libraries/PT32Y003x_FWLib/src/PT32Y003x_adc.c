/******************************************************************************
  * @file    PT32Y003x_adc.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the ADC peripheral:
  *           + Initialization and Configuration
  *           + Interrupts and flags management
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_adc.h"


/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Init_CR1_MASK        (u32)0xFFC0F481
#define Init_CR2_MASK        (u32)0xFF00FFFF
#define SetSampleTime_CR2_MASK   (u32)0xFFFF00FF

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC (
  *         Resolution, Data Alignment, continuous mode activation, External
  *         trigger source and edge, Sequence Scan Direction).
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
	u32 tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_Mode(ADC_InitStruct->ADC_Mode));
    assert_param(IS_ADC_TriggerSource(ADC_InitStruct->ADC_TriggerSource));
	assert_param(IS_ADC_TimerTriggerSource(ADC_InitStruct->ADC_TimerTriggerSource));
	assert_param(IS_ADC_Align(ADC_InitStruct->ADC_Align));
	assert_param(IS_ADC_Channel(ADC_InitStruct->ADC_Channel));
	assert_param(IS_ADC_BGVoltage(ADC_InitStruct->ADC_BGVoltage));
	assert_param(IS_ADC_ReferencePositive(ADC_InitStruct->ADC_ReferencePositive));  

	tmpreg = ADCx->CR1;
	tmpreg &= Init_CR1_MASK;
	tmpreg  |= ((ADC_InitStruct->ADC_Mode) |\
	           	(ADC_InitStruct->ADC_TriggerSource)|\
                (ADC_InitStruct->ADC_TimerTriggerSource)|\
                (ADC_InitStruct->ADC_Align)|\
                (ADC_InitStruct->ADC_Channel)|\
                (ADC_InitStruct->ADC_BGVoltage)|\
                (ADC_InitStruct->ADC_ReferencePositive));
	ADCx->CR1 = tmpreg;
    
    tmpreg = ADCx->CR2;
	tmpreg &= Init_CR2_MASK;
    tmpreg |= ((ADC_InitStruct->ADC_Prescaler)<<16);
    ADCx->CR2 = tmpreg; 
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC (
  *         Resolution, Data Alignment, continuous mode activation, External
  *         trigger source and edge, Sequence Scan Direction).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
	ADC_InitStruct->ADC_Prescaler = 2;						 	//ADC二分频，8/2=4 MHz
	ADC_InitStruct->ADC_Mode = ADC_Mode_Single;						//单次转换模式
    ADC_InitStruct->ADC_TriggerSource = ADC_TriggerSource_Software;
	ADC_InitStruct->ADC_TimerTriggerSource=ADC_TimerTriggerSource_TIM1ADC;						//定时源触发选择TIM0事件
	ADC_InitStruct->ADC_Align = ADC_Align_Right;					//右对齐
	ADC_InitStruct->ADC_Channel=ADC_Channel_0;						//通道0,PC13
	ADC_InitStruct->ADC_ReferencePositive= ADC_ReferencePositive_VDD;	//选择VDDA作为正端参考电平
	ADC_InitStruct->ADC_BGVoltage=ADC_BGVoltage_BG1v2;
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Set the ADEN bit to Enable the ADC peripheral */
		ADCx->CR1 |= ADC_CR1_EN;
	}
	else
	{
		/* Reset the ADEN to Disable the ADC peripheral */
		ADCx->CR1 &= ~ADC_CR1_EN;
	}
}



/**
  * @brief  Configures for the selected ADC and its sampling time.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure.
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: 
  *            @arg ADC_Channel_10: 
  *            @arg ADC_Channel_11:
  * @retval None
  */
void ADC_ChannelConfig(ADC_TypeDef* ADCx, u32 ADC_Channel)
{
	u32 tmpreg=0;
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_Channel(ADC_Channel));	
	tmpreg = ADCx->CR1;
	tmpreg &= ~ADC_CR1_CHS;
	tmpreg |= ADC_Channel;
	ADCx->CR1 = tmpreg;
}

void ADC_StartOfConversion(ADC_TypeDef* ADCx)
{
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    ADCx->CR1 |= ADC_CR1_SOC;
}

u16 ADC_DataCalculator(ADC_TypeDef* ADCx, u16 data)
{
	s16 AGENT_H;
	u32 AGENT_ID;
	s16 tmp;
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	AGENT_ID=(*((u32 volatile*)(0x4001F02C)));

	if(AGENT_ID==0xFFFFFFFF)
	{
		if(((ADCx->CR1) &0x8000000) == 0x0)
		{
			if((ADCx->CR1&ADC_CR1_ALIGN)==ADC_CR1_ALIGN)
			{
        return data>>1;
			}
			else
			{
				return data<<1;
			}
		}
		else
		{
			return data;
		}
	}		
	else
	{
		if(((ADCx->CR1) &0x8000000) == 0x8000000)
		{
			AGENT_ID<<=3;
			AGENT_H=(s32)AGENT_ID>>19;
			AGENT_H<<=1;
			if((ADCx->CR1&ADC_CR1_ALIGN) == 0)
			{
				data <<= 2;
			}
			tmp = (s16)data;
			tmp >>= 2;
			tmp = tmp + AGENT_H/1000;
			tmp &=  0xFFFE;
			if(tmp > 8191)
			{
				tmp = 8191;
			}
			else if(tmp < -8191)
			{
				tmp = -8191;
			}
			if((ADCx->CR1&ADC_CR1_ALIGN)==ADC_CR1_ALIGN)
			{
				tmp <<= 2;
			}
			return (u16)tmp;
		}
		else
		{
			return data<<1;
		}
	}
}
/**
  * @brief  Returns the last ADCx conversion result data for ADC channel.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval The Data conversion value.
  */
u16 ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
	/* Check the parameters */
	u16 data;
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	/* Return the selected ADC conversion value */
	data=ADCx->DR;
  data=ADC_DataCalculator(ADCx,data);
	return data; 
}


void ADC_ITConfig(ADC_TypeDef* ADCx, u32 ADC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT(ADC_IT)); 

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->CR1 |= ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->CR1 &= (~ADC_IT);
    }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_RDY: ADC Ready flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u32 ADC_FLAG)
{
	FlagStatus bitstatus = RESET;
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_FLAG(ADC_FLAG));
	/* Check the status of the specified ADC flag */
	if ((ADCx->SR & ADC_FLAG) != (u32)RESET)
	{
		/* ADC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* ADC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the ADC_FLAG status */
	return  bitstatus;
}

/**
  * @brief ADC Average Command
  * @param ADCx:ADC Peripheral 
  * @param NewState:FunctionalState type variable
  * @retval None
  */
void ADC_AverageCmd(ADC_TypeDef* ADCx,FunctionalState NewState)
{
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if(NewState!=DISABLE)
    { 
        ADCx->CR1 |= ADC_CR1_AVGE;
    }
    else
    {
        ADCx->CR1 &= (~ADC_CR1_AVGE);
    }		
}

/**
  * @brief ADC Average Times Config
  * @param ADCx:ADC Peripheral
  * @param Times: the time of average conversion
	* @arg ADC_AverageTimes_1: Average conversion 1 times                                         
	* @arg ADC_AverageTimes_2: Average conversion 2 times                                                                                 
	* @arg ADC_AverageTimes_4: Average conversion 4 times                                                                                  
	* @arg ADC_AverageTimes_8: Average conversion 8 times                                                                                  
	* @arg ADC_AverageTimes_16: Average conversion 16 times                                                                                  
	* @arg ADC_AverageTimes_32: Average conversion 32 times                                                                                  
	* @arg ADC_AverageTimes_64: Average conversion 64 times                                         
	* @arg ADC_AverageTimes_128: Average conversion 128 times                                          
  * @retval None
  */
void ADC_AverageTimesConfig(ADC_TypeDef* ADCx,u32 Times)
{
    u32 tmpreg=0;	
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_AverageTimes(Times));

    tmpreg = ADCx->CR2;
    tmpreg &= (~ADC_CR2_AVGT);
    tmpreg |= ((Times));
    ADCx->CR2 = tmpreg;	
}

/**
  * @brief ADC Ready Time Config
  * @param ADCx:ADC Peripheral 
  * @param ReadyTime:0x0-0xFF
  * @retval None
  */
void ADC_ReadyTimeConfig(ADC_TypeDef* ADCx,u32 ReadyTime)
{
    u32 tmpreg=0;
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    tmpreg = ADCx->CR2;
    tmpreg &= (~ADC_CR2_RDTC);
    tmpreg |= ReadyTime;
    ADCx->CR2 = tmpreg;	
}

/**
  * @brief  Set ADC sample times the specified ADC peripheral.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  sampletime: sample time value (3~255).
  * @retval None
  */
void ADC_SampleTimeConfig(ADC_TypeDef* ADCx, u8 SampleTime)
{
  u32 tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_SampleTime(SampleTime));    
	tmpreg = ADCx->CR2;
	tmpreg &= SetSampleTime_CR2_MASK;
	tmpreg |= (SampleTime << 8);
  ADCx->CR2 = tmpreg;
}

/**
  * @brief ADC Scan Command
  * @param ADCx:ADC Peripheral 
  * @param NewState:FunctionalState type variable
  * @retval None
  */
void ADC_ScanCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the SCANE bit to Enable the ADC scan */
        ADCx->CR1 |= ADC_CR1_SCANE;
    }
    else
    {
        ADCx->CR1 &= (~ADC_CR1_SCANE);
    }
}

/**
  * @brief ADC Scan Channel Config
  * @param ADCx:ADC Peripheral 
  * @param ADC_Channel:ADC Peripheral
  * @param ADC_Channel:the ADC channel to configure.
	*          This parameter can be one of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  *            @arg ADC_Channel_16: ADC Channel16 selected
  *            @arg ADC_Channel_17: ADC Channel17 selected
  *            @arg ADC_Channel_18: ADC Channel18 selected
  * @param ScanChannel: ADC scan channel (0~19)
  * @retval None
  */
void ADC_ScanChannelConfig(ADC_TypeDef* ADCx,u32 ADC_Channel,u32 ScanChannel)
{
    u32 tmpreg=0;	  
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_Channel(ADC_Channel));
    assert_param(IS_ADC_ScanChannel(ScanChannel));	

    if(ScanChannel <= 5)
    {
        tmpreg = ADCx->SCHR1;	  
        tmpreg &= (~(ADC_SCHR1_CH0<<(ScanChannel*5)));
        tmpreg |= ((ADC_Channel>>16)<<ScanChannel*5);
        ADCx->SCHR1 = tmpreg;
    }
    if((ScanChannel == 6)&&(ScanChannel == 7))
    {
        tmpreg = ADCx->SCHR2;	  
        tmpreg &= (~(ADC_SCHR2_CH6<<((ScanChannel-6)*5)));
        tmpreg |= ((ADC_Channel>>16)<<(ScanChannel-6)*5);
        ADCx->SCHR2 = tmpreg;
    }
}

/**
  * @brief ADC Scan Channel Number Config
  * @param ADCx:ADC Peripheral 
  * @param ScanNumber: the number of ADC scan channel (2~20)
  * @retval None
  */
void ADC_ScanChannelNumberConfig(ADC_TypeDef* ADCx,u32 ScanNumber)
{
    u32 tmpreg=0;	  
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_ScanChannelNumber(ScanNumber));	

    tmpreg = ADCx->SCHR2;	  
    tmpreg &= (~ADC_SCHR2_SCNT);
    tmpreg |= ((ScanNumber-1) << 16);
    ADCx->SCHR2 = tmpreg;
}

u16 ADC_GetScanData(ADC_TypeDef* ADCx,u32 ScanChannel)
{
	/* Check the parameters */
	u16 data;
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_ScanChannel(ScanChannel));
	/* Return the selected ADC conversion value */
	if (ScanChannel==0)
	{
		data = ADCx->SCHDR0;
	}
	else if(ScanChannel==1)
	{
	  data = ADCx->SCHDR1;
	}
	else if(ScanChannel==2)
	{
		data = ADCx->SCHDR2;
	}
	else if(ScanChannel==3)
	{
		data = ADCx->SCHDR3;
	}
	else if(ScanChannel==4)
	{
		data = ADCx->SCHDR4;
	}
	else if(ScanChannel==5)
	{
		data = ADCx->SCHDR5;
	}
	else if(ScanChannel==6)
	{
		data = ADCx->SCHDR6;
	}
	else
	{
		data = ADCx->SCHDR7;
	}
	
  data=ADC_DataCalculator(ADCx,data);
	return data;
}

void ADC_RefNegativeConfig(ADC_TypeDef* ADCx,u32 RefN)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_ReferenceNegative(RefN));
	ADCx->CR1&=~ADC_CR1_INNS;
	if(RefN)
	{
		ADCx->CR1|=ADC_CR1_INNS;
	}
	else
	{
		ADCx->CR1 &= ~ADC_CR1_INNS;
	}
}
/**
  * @brief  ADC bg voltage selection.
  * @param 	ADCx: ADC Peripheral.
  * @param  SEL: the bg voltage of the ADC.
  *          This parameter can be one of the following values:
	* 					@arg ADC_BGVoltage_BG1v2: select the BG1V2 as ADC channel voltage
	* 					@arg ADC_BGVoltage_BG1v0: select the BG1V0 as ADC channel voltage
  * @retval None
  */
void ADC_BGVoltageConfig(ADC_TypeDef *ADCx,u32 SEL)
{
	u32 tmpreg = 0;
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_BGVoltage(SEL));
	
	tmpreg = ADCx->CR1;
	tmpreg &= (~ADC_CR1_BGS);
	tmpreg |= SEL;
	ADCx->CR1 = tmpreg;		
}
/**
  * @}
  */
  
