  /******************************************************************************
  * @file    PT32Y003x_ID.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PT32Y003x_id.h"


/** @defgroup ID
  * @brief ID driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Get the User define ID
  * @param  None
  * @retval  User define ID
  */
u32 ID_GetCustomerID(void)
{
	return ( ID->UDID );
}


/**
  * @brief  Get the unique ID
  * @param  UID_Number: specifies the unique ID number
  *               @arg   This parameter can be 1 to 3
  * @retval  unique ID
  */
u32 ID_GetUID(u8 UID_Number)
{
	u32 UID;
	if(UID_Number==1)	UID=ID->UID1;
	else if(UID_Number==2)	UID=ID->UID2;
	else if(UID_Number==3)	UID=ID->UID3;
	else
	{
		UID=0;
	}
	return UID;
}

/**
  * @brief  Get the chip ID
  * @param  None
  * @retval  chip ID
  */
u32 ID_GetCID(void)
{
	return ( ID->CID );
}


/**
  * @}
  */

