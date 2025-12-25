/******************************************************************************
  * @file    PT32Y003x_it.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file provides all interrupt service routine.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
  
/* Includes ------------------------------------------------------------------------------------------------*/
#include "PT32Y003x_it.h"
#include "base.h"

/** @defgroup IT
  * @brief IT driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------------------------------------*/



/**
* @brief NMI中断服务函数
* @param None
* @retval None
*/
void NMI_Handler(void)
{
}

/**
* @brief HardFault中断服务函数
* @param None
* @retval None
*/
void HardFault_Handler(void)
{
  	while (1);
}

/**
* @brief SVC中断服务函数
* @param None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief PendSV中断服务函数
* @param None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief SysTick中断服务函数
* @param None
* @retval None
*/
void SysTick_Handler(void)
{
}

/**
* @brief IWDG中断服务函数
* @param None
* @retval None
*/
void IWDG_Handler(void)
{	
}

/**
* @brief PLLFAIL
* @param None
* @retval None
*/
void HSEFAIL(void)
{
}

/**
* @brief IMMC中断服务函数
* @param None
* @retval None
*/
void IMMC_Handler(void)
{
}

/**
* @brief PA中断服务函数
* @param None
* @retval None
*/
void EXTIA_Handler(void)
{
}

/**
* @brief PB中断服务函数
* @param None
* @retval None
*/
void EXTIB_Handler(void)
{
}

/**
* @brief PC中断服务函数
* @param None
* @retval None
*/
void EXTIC_Handler(void)
{
}

/**
* @brief PD中断服务函数
* @param None
* @retval None
*/
void EXTID_Handler(void)
{	
}

/**
* @brief ADC中断服务函数
* @param None
* @retval None
*/
WEEK void ADC_Handler(void)
{
}

/**
* @brief TIMER1中断服务函数
* @param None
* @retval None
*/
void TIM1_Handler(void)
{	
}

///**
//* @brief TIMER2中断服务函数
//* @param None
//* @retval None
//*/
//void TIM2_Handler(void)
//{	
//}

///**
//* @brief TIMER3中断服务函数
//* @param None
//* @retval None
//*/
//void TIM3_Handler(void)
//{
//}

/**
* @brief TIMER4中断服务函数
* @param None
* @retval None
*/
void TIM4_Handler(void)
{
}

/**
* @brief PVD中断服务函数
* @param None
* @retval None
*/
void PVD_Handler(void)
{
}

/**
* @brief I2C0中断服务函数
* @param None
* @retval None
*/
void I2C0_Handler(void)
{
}


/**
* @brief SPI0中断服务函数
* @param None
* @retval None
*/
void SPI0_Handler(void)
{
}


/**
* @brief UART0中断服务函数
* @param None
* @retval None
*/
WEEK void UART0_Handler(void)
{	
}


/**
* @brief UART1中断服务函数
* @param None
* @retval None
*/
void UART1_Handler(void)
{	
}


/**
  * @}
  */

