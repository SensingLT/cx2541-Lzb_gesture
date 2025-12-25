  /******************************************************************************
  * @file    PT32Y003x_rcc.h
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    This file contains all the functions prototypes for the SYS firmware library.
  *          
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PT32Y003x_ID_H
#define PT32Y003x_ID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x.h"


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
u32 ID_GetCustomerID(void);
u32 ID_GetUID(u8 UID_Number);
u32 ID_GetCID(void);

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif 


