  /******************************************************************************
  * @file    PT32Y003x_retarget.c
  * @author  应用开发团队
  * @version V1.6.0
  * @date    2023/12/18
  * @brief    该文件重映射fputc()和fgetc()，以支持标准C/C++的printf和scanf函数
  *            
  ******************************************************************************
  * @attention
  *
  *
  *****************************************************************************/
  
/* Includes ------------------------------------------------------------------------------------------------*/
#include "PT32Y003x.h"

#define RETARGET_UART0 0	
#define RETARGET_UART1 1	
#define RETARGET_UART2 2	
#define RETARGET_UART3 3

#define RETARGET_PORT 0

#if (RETARGET_PORT==RETARGET_UART0)
#define RETARGET_UART_PORT UART0
#define RETARGET_COM_PORT COM0
#define RETARGET_UART_IRQn UART0_IRQn
#elif (RETARGET_PORT==RETARGET_UART1)
#define RETARGET_UART_PORT UART1
#define RETARGET_COM_PORT COM1
#define RETARGET_UART_IRQn UART1_IRQn
#elif (RETARGET_PORT==RETARGET_UART2)
#define RETARGET_UART_PORT UART2
#define RETARGET_COM_PORT COM2
#define RETARGET_UART_IRQn UART2_IRQn
#elif (RETARGET_PORT==RETARGET_UART3)
#define RETARGET_UART_PORT UART3
#define RETARGET_COM_PORT COM3
#define RETARGET_UART_IRQn UART3_IRQn
#endif
#if defined (__CC_ARM)
	#pragma import(__use_no_semihosting_swi)
#endif

#include <stdio.h>

#if defined (__CC_ARM)
	#include <rt_misc.h>
#endif
 

/* Global variables ----------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Global_Variable Retarget global variables
  * @{
  */
#if defined (__CC_ARM)
struct __FILE
{
	int handle; /* Add whatever you need here */
};
FILE __stdout;
FILE __stdin;
#endif
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RETARGET_Exported_Functions Retarget exported functions
  * @{
  */

u8 SERIAL_PutChar(u8 ch);
u8 SERIAL_GetChar(void);



int __backspace(FILE *stream)
{
	return 0;
}

int fputc (int ch, FILE *f)
{
	return (SERIAL_PutChar(ch));
}

int fgetc (FILE *f)
{
	return (SERIAL_GetChar());
}



void _sys_exit(int return_code)
{
label:
	goto label;  /* endless loop */
}

/*********************************************************************************************************//**
 * @brief  Put char to UART.
 * @param  ch: The char put to UART.
 * @retval The char put to UART.
 ************************************************************************************************************/
u8 SERIAL_PutChar(u8 ch)
{
	while(UART_GetFlagStatus(RETARGET_UART_PORT,UART_FLAG_TXF));
	RETARGET_UART_PORT->DR = ch;
	return ch;
}

/*********************************************************************************************************//**
 * @brief  Get char from UART.
 * @retval The char got from UART.
 ************************************************************************************************************/
u8 SERIAL_GetChar(void)
{
	while ((RETARGET_UART_PORT->SR & 0x0001) == 0); // Wait if Receive Holding register is empty
	return (RETARGET_UART_PORT->DR);
}
/**
* @brief Retrim
* @param none
* @retval None
*/
void Retrim(void)
{
	int cid_chip=0x1,flag_por=0,flag_cwr=0,flag_immc1=0,flag_immc2=0;
	cid_chip=(ID->CID)&0xF0000>>16;
	flag_immc1=(IMMC->RPSR&0xFF00)>>8;
	flag_immc2=(IMMC->RPSR&0x6)>>1;
	flag_por=(RCC->RSR&RCC_RSR_POR)>>6;
	flag_cwr=(RCC->RSR&RCC_RSR_CWR)>>11;

	if((cid_chip==0x0)||(cid_chip==0xF))
	{
		if((flag_immc1!=0x5)||(flag_immc2!=0x3)||(flag_por==1))
		{
			if(flag_por)
			{
				RCC->RSR=RCC_RSR_POR;
			}
			RCC->ASFCR = 0xAB56;
		}
		if(flag_cwr)
		{
			RCC->RSR=RCC_RSR_CWR;
		}
	}
}
/**
  * @}
  */


