/******************************************************************************
  * @file   PT32Y003x_conf.h
  * @author  应用开发团队
  * @version V1.0.0
  * @date    2020/10/19
  * @brief    
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_CONF_H
#define PT32Y003x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Comment the line below to disable peripheral header file inclusion */
#include "PT32Y003x_gpio.h"
#include "PT32Y003x_tim.h"
#include "PT32Y003x_nvic.h"
#include "PT32Y003x_uart.h"
#include "PT32Y003x_pwm.h"
#include "PT32Y003x_wdg.h"
#include "PT32Y003x_i2c.h"
#include "PT32Y003x_spi.h"
#include "PT32Y003x_crc.h"
#include "PT32Y003x_immc.h"
#include "PT32Y003x_adc.h"
#include "PT32Y003x_pwr.h"
#include "PT32Y003x_rcc.h"
#include "PT32Y003x_id.h"
#include "PT32Y003x_exti.h"
#include "system_PT32Y003x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/


#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, u32 line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif 


