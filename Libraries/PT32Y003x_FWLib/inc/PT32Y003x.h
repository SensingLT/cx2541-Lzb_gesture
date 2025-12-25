
/******************************************************************************
  * @file    PT32Y003x.h
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

    
#ifndef PT32Y003x_H
#define PT32Y003x_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (__CC_ARM)
#pragma anon_unions
#endif	

#define __CM0_REV			0 	/*!< Core Revision r0p0	*/
#define __MPU_PRESENT		0 	/*!< 003 do not provide MPU	*/
#define __NVIC_PRIO_BITS	2 	/*!< 003 uses 2 Bits for the Priority Levels  */
#define __Vendor_SysTickConfig	0 /*!< Set to 1 if different SysTick Config is used  */
#define _PT32Y003x				/*!< MCU Type*/

/**
 * @brief 003 Interrupt Number Definition
 */	
typedef enum IRQn
{
	/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
	NMI_IRQn        = -14,	    /*!< 2 Non Maskable Interrupt	        */
	HardFault_IRQn	= -13,	    /*!< 3 Cortex-M0 Hard Fault Interrupt	*/
	SVCall_IRQn		= -5,	    /*!< 11 Cortex-M0 SV Call Interrupt	    */
	PendSV_IRQn	    = -2,	    /*!< 14 Cortex-M0 Pend SV Interrupt	    */
	SysTick_IRQn	= -1,	    /*!< 15 Cortex-M0 System Tick Interrupt	*/

	/****** MCU Specific Interrupt Numbers *******************************************************/	    
	HSEFAIL_IRQn 	=  1 ,      /* HSEFAIL     Interrupt 	*/
	IMMC_IRQn    	=  3 ,      /* IMMC        Interrupt 	*/
	EXTIA_IRQn      =  5 ,      /* EXTIA       Interrupt 	*/
	EXTIB_IRQn    	=  6 ,      /* EXTIB       Interrupt 	*/
	EXTIC_IRQn      =  7 ,	    /* EXTIC       Interrupt 	*/
	EXTID_IRQn      =  8 ,	    /* EXTID       Interrupt 	*/
	ADC_IRQn        =  12,      /* ADC         Interrupt 	*/
	TIM1_IRQn       =  13,      /* TIM1        Interrupt 	*/ 
	TIM4_IRQn       =  15,      /* TIM4        Interrupt 	*/
	TIM3_IRQn       =  16,      /* TIM3        Interrupt 	*/
	TIM2_IRQn       =  17,      /* TIM2        Interrupt 	*/
	PVD_IRQn        =  20,      /* PVD         Interrupt 	*/
	I2C0_IRQn       =  23,      /* I2C0        Interrupt 	*/
	SPI0_IRQn       =  25,      /* SPI0        Interrupt 	*/	
	UART0_IRQn      =  27,      /* UART0       Interrupt 	*/
    UART1_IRQn      =  28,      /* UART1       Interrupt 	*/	
} IRQn_Type;



#include "core_cm0.h"
#include "PT32_Type.h"
#include "system_PT32Y003x.h"
#include <stdint.h>


/** @addtogroup Exported_types
  * @{
  */  
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, RemapStatus, ProtectStatus,BitAction;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/**
  * @}
  */

/**
 * @brief Cyclic Redundancy Check
 */
typedef struct
{                                                                              
	__IO u32 CR;               /*!< 0x000 CRC Control Register                                           */
	__IO u32 SEED;             /*!< 0x004 CRC Seed Register                                              */	
	__IO u32 POLY;             /*!< 0x008 CRC polynomial Register                                        */
	__IO u32 DIN;              /*!< 0x00C CRC Data INPUT Register                                        */
	__IO u32 DOUT;             /*!< 0x010 CRC Data INPUT Register                                        */
} CRC_TypeDef;

/**
 * @brief PWR
 */
typedef struct 
{
	__IO u32 PVDR;	/*!< Offset: 0x000 VDD Low Voltage Detect Control Register (R/W) */
}  PWR_TypeDef;

/**
 * @brief RCC
 */
typedef struct 
{
	__IO u32 HSECR1;  	/*!< Offset: 0x000 Crystal Control Register1                (R/W) */
	__IO u32 HSECR2;  	/*!< Offset: 0x004 Crystal Control Register2                (R/W) */
	__IO u32 HSICR;	    /*!< Offset: 0x008 48MHZ IOSC Control Register              (R/W) */
	__IO u32 LSICR;	    /*!< Offset: 0x00C 32KHZ IOSC Control Register              (R/W) */
	__IO u32 PCR;       /*!< Offset: 0x010 Frequency Doubling Control Register      (R/W) */
	u32 RESERVED0[2];  	
	__IO u32 MCOR;	    /*!< Offset: 0x01C MCO Frequency Division Control Register  (R/W) */
	u32 RESERVED1[30201];
	__IO u32 CFGR;	    /*!< Addr: 0x1F00C Clock configuration register             (R/W) */
	__IO u32 RSR;	    /*!< Addr: 0x1F010 Reset Status Register                    (R/W) */
	__IO u32 ASFCR;	    /*!< Addr: 0x1F014 Advanced software reset control register (R/W) */
	__IO u32 RCR;	    /*!< Addr: 0x1F018 Reset control register                   (R/W) */
}  RCC_TypeDef;

/** 
  * @brief ID
**/
typedef struct
{
	__I  u32  UDID;     /* Offset: 0x000 Customer ID information Register       (R) */
	u32 RESERVED0[3]; 	
	__I  u32  UID1;   	/* Offset: 0x010 UID information Register               (R) */ 
	__I  u32  UID2;   	/* Offset: 0x014 UID information Register 				(R) */
	__I  u32  UID3;   	/* Offset: 0x018 UID information Register 				(R) */ 
	__I  u32  CID;      /* Offset: 0x01C CID information Register 				(R) */
} ID_TypeDef;

/** 
  * @brief General Purpose IO  
  */
typedef struct
{
	__IO u32  DR;        		/*!< Offset: 0x000 DATA Register (R/W) */
	u32  RESERVED1;         	/*!< Offset: 0x004 Data Output Latch Register (R/W) */
	__IO u32  OES;	            /*!< Offset: 0x008 Output Enable Set Register  (R/W) */
	__IO u32  OEC; 	            /*!< Offset: 0x00C Output Enable Clear Register  (R/W) */
	u32  RESERVED2[12];
	__IO u32  PUS;		        /*!< Offset: 0x040 Pull Up Set Register  (R/W) */
	__IO u32  PUC;		        /*!< Offset: 0x044 Pull Up Clear Register  (R/W) */
	__IO u32  PDS;	            /*!< Offset: 0x048 Pull Down Set Register  (R/W) */
	__IO u32  PDC;	            /*!< Offset: 0x04C Pull Down Clear Register  (R/W) */
	__IO u32  ODS;		        /*!< Offset: 0x050 Open Drain Set Register  (R/W) */
	__IO u32  ODC;		        /*!< Offset: 0x054 Open Drain Clear Register  (R/W) */
	u32  RESERVED3[6];
	__IO u32  CSS;              /*!< Offset: 0x070 Input Schmidt trigger set register  (R/W) */
	__IO u32  CSC;            /*!< Offset: 0x074 Input Schmidt trigger clear register   (R/W) */
	__IO u32  BSR;            /*!< Offset: 0x078 Port Bit Set Register  (R/W) */
	__IO u32  BRR;             /*!< Offset: 0x07C Port Bit Reset Regist  (R/W) */
	u32  RESERVED4[224];
	__O u32  MASKL[256];	    /*!< Offset: 0x400 - 0x7FC Lower byte Masked Access Register (R/W) */
	__O u32  MASKH[256];	    /*!< Offset: 0x800 - 0xBFC Upper byte Masked Access Register (R/W) */
} GPIO_TypeDef;

/**
 * @brief AFIO
**/
typedef struct
{   
    __IO u32  AFS0;	  	/* Offset: 0x000 Alternate Function Set Register0 		(R/W) */
    u32 RESERVED0;
	__O  u32  AFC;    	/* Offset: 0x008 Alternate Function Clear Register0  	(W) 	*/
	u32 RESERVED1[15];
	__IO u32  ANAS;		/* Offset: 0x048 Analog function Set Register  				(R/W) */ 
	__O  u32  ANAC;		/* Offset: 0x04C Analog function Clear Register  			(W) 	*/ 
} AFIO_TypeDef;
	
/**
 * @brief EXTI
**/
typedef struct
{   
	__IO u32  IES;     	/* Offset: 0x000 Interrupt Enable Set Register  	 (R/W) */ 
	__O  u32  IEC;    	/* Offset: 0x004 Interrupt Enable Clear Register   (W)   */ 
	__IO u32  ITS;      /* Offset: 0x008 Interrupt Type Set Register0  		 (R/W) */ 
	__O  u32  ITC;      /* Offset: 0x00C Interrupt Type Clear Register0    (W)   */ 
	__IO u32  ITDS;	    /* Offset: 0x010 Interrupt Type Set Register1  		 (R/W) */ 
	__O  u32  ITDC;	    /* Offset: 0x014 Interrupt Type Clear Register1  	 (W)	  */ 
	__IO u32  PTS;      /* Offset: 0x018 Interrupt Polarity Set Register   (R/W) */ 
	__O  u32  PTC;   	/* Offset: 0x01C Interrupt Polarity Clear Register (W)   */ 
	__IO u32  IF;	    /* Offset: 0x020 Interrupt Status Register  			 (R/W) */
} EXTI_TypeDef;
	
	/** 
  * @brief TIM0&TIM1
  */
typedef struct	
{
	__IO u32 SR;            			 /*!< offset: 0x000 Interrupt status Register   (R/W)         */
	__IO u32 CR1;            			 /*!< offset: 0x004 Control Register            (R/W)         */
  u32 RESERVED0;             			 /*!< DELETED!! offset: 0x008 Prescale Counter Register   (R/W)         */
	__IO u32 ITARR;            	        /*!< offset: 0x00C Interrupt Repeat Timers     (R/W)         */
	__IO u32 ITCNT;            	        /*!< offset: 0x010 Interrupt Repeat Timers CNT (R/W)         */
	__IO u32 PSC;            		  	 /*!< offset: 0x014 Prescale Register           (R/W)         */
	u32 RESERVED1;             			 /*!< DELETED!! offset: 0x018 Prescale Counter Register   (R/W)         */
	__IO u32 CNT;             			 /*!< offset: 0x01C Timer Counter Register      (R/W)         */
	__IO u32 CR2;            			 /*!< offset: 0x020 Match Control Register      (R/W)         */
	__IO u32 ARR;            			 /*!< offset: 0x024 Match Value Register0       (R/W)         */
	__IO u32 OCR1;            			 /*!< offset: 0x028 Match Value Register1       (R/W)         */	
	__IO u32 OCR2;            			 /*!< offset: 0x02C Match Value Register2       (R/W)         */
	__IO u32 OCR3;            		   /*!< offset: 0x030 Match Value Register3       (R/W)         */
	__IO u32 OCR4;             			 /*!< offset: 0x034 Match Value Register4       (R/W)         */
	__IO u32 CAPR;             			 /*!< offset: 0x038 Capture Control Register    (R/W)         */
	u32 RESERVED2;             			 /*!< DELETED!! offset: 0x03C Prescale Counter Register   (R/W)         */    
	__IO u32 ICR1;            			 /*!< offset: 0x040 Capture Value Register1     (R/W)         */
	__IO u32 ICR2;            			 /*!< offset: 0x044 Capture Value Register2     (R/W)         */
	__IO u32 ICR3;            			 /*!< offset: 0x048 Capture Value Register3     (R/W)         */
	__IO u32 ICR4;            			 /*!< offset: 0x04C Capture Value Register4     (R/W)         */	
	__IO u32 OCMR;            			 /*!< offset: 0x050 Compare Output Register     (R/W)         */
	__IO u32 BDTR;             		   /*!< offset: 0x04C Death Time Register         (R/W)         */
  __IO u32 CR3;
	u32 RESERVED3;
  __IO u32 TACR;
  __IO u32 BKICR;
} PWM_TypeDef;

/** 
  * @brief TIMx
  */
typedef struct
{
	__IO u32 SR;            			 /*!< offset: 0x000 Interrupt status Register   (R/W)         */
	__IO u32 CR1;            			 /*!< offset: 0x004 Control Register            (R/W)         */
	__IO u32 PSC;            		  	 /*!< offset: 0x008 Prescale Register           (R/W)         */
	     u32 RESERVED0;             			 /*!<DELETED!! offset: 0x00C Prescale Counter Register   (R/W)         */
	__IO u32 CNT;             			 /*!< offset: 0x010 Timer Counter Register      (R/W)         */
	__IO u32 CR2;            			 /*!< offset: 0x014 Match Control Register      (R/W)         */
	__IO u32 ARR;            			 /*!< offset: 0x018 Match Value Register0       (R/W)         */
} TIMx_TypeDef;

/** 
  * @brief Independent WATCHDOG
  */
typedef struct
{
	__IO u32 RLR;   	/*!< Offset: 0x000   IWDG Reload register,     */
	__I  u32 CNT; 	    /*!< Offset: 0x004   IWDG COUNT register,      */
	__IO u32 CR;    	/*!< Offset: 0x008   IWDG Control register,    */
	__IO u32 KR;  	    /*!< Offset: 0x00C   IWDG Status register,     */
	__IO u32 SR;   	    /*!< Offset: 0x010   IWDG Window register,     */
	     u32 RESERVED0[251];        
	__IO u32 LOCK;    	/*!< Offset: 0x400   IWDG Window register,     */		
} IWDG_TypeDef; 

/** 
  * @brief UART 
  */
typedef struct	
{
	__IO u32 DR;     	/*!< Offset: 0x000 Buffer Register 		(R/W) */
	__IO u32 CR;		/*!< Offset: 0x004 Control Register		(R/W) */
	__IO u32 BRR;     	/*!< Offset: 0x008 Baud Rate Register		(R/W) */
	__IO u32 IE;    	/*!< Offset: 0x00C Interrupt Enable Register	(R/W) */
	__IO u32 SR;     	/*!< Offset: 0x010 Status Register		(R/W) */
	u32 RESERVED0; /*!< RESERVED0,      Address offset: 0x10*/	
	u32 RESERVED1; /*!< RESERVED1,      Address offset: 0x14 */
	__IO u32 TXFR; 	/*!< Offset: 0x01C TX Buffer Reset Register  	(WO)  */
	__IO u32 RXFR;   	/*!< Offset: 0x020 RX Buffer Reset Register  	(WO)  */	
  u32 RESERVED2; /*!< RESERVED2,      Address offset: 0x24 */
	__IO u32 IMCR;			/*!< Offset: 0x028 Infra-red Control Register  	(R/W) */	
	__IO u32 IMDCR;		/*!< Offset: 0x02C IR TX PWM Control Register  	(R/W) */   
} UART_TypeDef;

/** 
  * @brief Serial Peripheral Interface
  */
typedef struct		
{
	__IO u32 CR1;       /*!< SPI Control register 1                               Address offset: 0x00 */
	__IO u32 CR2;       /*!< SPI Control register 2,                              Address offset: 0x04 */
	__IO u32 DR;        	/*!< SPI data register,                                   Address offset: 0x08 */
	__IO u32 SR1;        	/*!< SPI Status register,                                 Address offset: 0x0C */	
	__IO u32 BR; 	/*!< SPI Clock prescaler register                         Address offset: 0x10 */
	__IO u32 IE;        	/*!< SPI Interrupt ENABLE register                        Address offset: 0x14 */	
	__IO u32 SR2;       	/*!< SPI Interrupt Raw Int Status register                Address offset: 0x18 */	
	     u32 RESERVED0;
	__IO u32 IC;       	/*!< SPI Interrupt Clear Register register                Address offset: 0x20 */	
	     u32 RESERVED1;	/*0X24*/
	__IO u32 CSS;      /*!< SPI Chip-Select Control register                     Address offset: 0x28*/	
    __IO u32 TXFR;
    __IO u32 RXFR;
} SPI_TypeDef;

/** 
  * @brief Inter-integrated Circuit Interface
  */
typedef struct
{
	__IO u32 CR;		/*!< I2C0 Control Set register ,         Address offset: 0x00 */
	__I  u32 SR; 		/*!< I2C0 status register,               Address offset: 0x04 */
	__IO u32 DR;  	/*!< I2C0 data register,                 Address offset: 0x08 */	
	__IO u32 OAR;	/*!< I2C0 Own address register,          Address offset: 0x0C */
	__IO u32 RESERVED0; /*!< RESERVED0,      Address offset: 0x10*/	
	__IO u32 RESERVED1; /*!< RESERVED0,      Address offset: 0x14 */	
	__IO u32 CCR; 		/*!< I2C0 Control Reset register 2,      Address offset: 0x18 */	
} I2C_TypeDef;

typedef struct
{
	__IO u32 CR1;       	/*!< Offset: 0x000 ADC Control register */
    __IO u32 CR2;       	/*!< Offset: 0x000 ADC Control register */
	__IO u32 SR;    	/*!< Offset: 0x004 ADC Status Register  (R/W) */
	__IO u32 DR;    	/*!< Offset: 0x008 ADC data register (R/W) */
	  u32 RESERVED0;
    __IO u32 SCHR1;
    __IO u32 SCHR2;
	  u32 RESERVED1[2];
    __IO u32 BGCR;
	  u32 RESERVED2[6];
    __IO u32 SCHDR0;
    __IO u32 SCHDR1;
    __IO u32 SCHDR2;
    __IO u32 SCHDR3;
    __IO u32 SCHDR4;
    __IO u32 SCHDR5;
    __IO u32 SCHDR6;
    __IO u32 SCHDR7;
} ADC_TypeDef;	

/** 
  * @brief IMMC  
  */
typedef struct
{
	__IO u32 CR; 	/*!< Offset: 0x000 Flash Command Register (R/W) */
	__IO u32 SR;   	/*!< Offset: 0x004 Flash Interrupt status Register (R/W) */
	__IO u32 IE;  	/*!< Offset: 0x008 Flash Interrupt Enable Register  (R/W) */
	__IO u32 AR;    	/*!< Offset: 0x00C Flash Address Register (R/W) */
	__IO u32 DR;  	/*!< Offset: 0x010 Flash Programming Data Register0  (R/W) */
	     u32 RESERVED0[5];
	__IO u32 PSC;  	/*!< Offset: 0x028 Flash Erase Clock Division Register  (R/W) */
	     u32 RESERVED1[31733];
	__IO u32 BSR;  	/*!< Offset: 0x1F000 BOOT Status Register  (R/W) */
    __IO u32 IAPAR;  	/*!< Offset: 0x1F000 BOOT Status Register  (R/W) */
	     u32 RESERVED2[7];
	__IO u32 RPSR;  	/*!< Offset: 0x1F024 READ Protect Register  (R/W) */
} IMMC_TypeDef;	

/*Peripheral and SRAM base address */
#define SRAM_BASE             (0x20000000)     /*!< (SRAM      ) Base Address */
#define FLASH_BASE            (0x00000000)     /*!< (FLASH      ) Base Address */

#define APB_BASE              (0x40000000)
#define AHB_BASE              (0x48000000)

/* AHB peripherals */
#define GPIOA_BASE               (AHB_BASE + 0x00000000)
#define GPIOB_BASE               (AHB_BASE + 0x00001000)
#define GPIOC_BASE               (AHB_BASE + 0x00002000)
#define GPIOD_BASE               (AHB_BASE + 0x00003000)

#define EXTIA_BASE	(AHB_BASE + 0x0000001C)
#define EXTIB_BASE	(AHB_BASE + 0x0000101C)
#define EXTIC_BASE	(AHB_BASE + 0x0000201C)
#define EXTID_BASE	(AHB_BASE + 0x0000301C)

#define AFIOA_BASE	(AHB_BASE + 0x00000010)
#define AFIOB_BASE	(AHB_BASE + 0x00001010)
#define AFIOC_BASE	(AHB_BASE + 0x00002010)
#define AFIOD_BASE	(AHB_BASE + 0x00003010)

/* APB peripherals */
#define IMMC_BASE    	    (APB_BASE + 0x00000000)
#define TIM2_BASE       	(APB_BASE + 0x00001000)
#define TIM3_BASE       	(APB_BASE + 0x00001400)
#define RCC_BASE     	    (APB_BASE + 0x00001808)
#define PWR_BASE        	(APB_BASE + 0x00001800)
#define TIM4_BASE        	(APB_BASE + 0x00001C00)
#define IWDG_BASE       	(APB_BASE + 0x00003000)
#define CRC_BASE         	(APB_BASE + 0x00003C00)
#define I2C_BASE            (APB_BASE + 0x00005400)
#define ADC_BASE            (APB_BASE + 0x00012400)
#define TIM0_BASE		    (APB_BASE + 0x00012800)
#define TIM1_BASE        	(APB_BASE + 0x00012C00)
#define SPI0_BASE           (APB_BASE + 0x00013000)
#define UART0_BASE    	    (APB_BASE + 0x00004400)
#define UART1_BASE   	  	(APB_BASE + 0x00013800)
#define ID_BASE		        (APB_BASE + 0x0001F020)
/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  
#define GPIOA	((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB	((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC	((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD	((GPIO_TypeDef *) GPIOD_BASE)

#define AFIOA	((AFIO_TypeDef *)AFIOA_BASE)
#define AFIOB	((AFIO_TypeDef *)AFIOB_BASE)
#define AFIOC	((AFIO_TypeDef *)AFIOC_BASE)
#define AFIOD	((AFIO_TypeDef *)AFIOD_BASE)

#define EXTIA	((EXTI_TypeDef *) EXTIA_BASE)
#define EXTIB	((EXTI_TypeDef *) EXTIB_BASE)
#define EXTIC	((EXTI_TypeDef *) EXTIC_BASE)
#define EXTID	((EXTI_TypeDef *) EXTID_BASE)

#define UART0   ((UART_TypeDef *) UART0_BASE)
#define UART1   ((UART_TypeDef *) UART1_BASE)
#define IMMC	((IMMC_TypeDef *) IMMC_BASE)
#define ADC     ((ADC_TypeDef  *) ADC_BASE)
#define I2C0	((I2C_TypeDef  *) I2C_BASE)
#define SPI0    ((SPI_TypeDef  *) SPI0_BASE)
#define TIM1	((PWM_TypeDef  *) TIM1_BASE)
#define TIM2	((TIMx_TypeDef *) TIM2_BASE)
#define TIM3	((TIMx_TypeDef *) TIM3_BASE)
#define TIM4	((TIMx_TypeDef *) TIM4_BASE)
#define CRC		((CRC_TypeDef  *) CRC_BASE)
#define IWDG	((IWDG_TypeDef *) IWDG_BASE)
#define PWR	    ((PWR_TypeDef  *) PWR_BASE)
#define RCC	    ((RCC_TypeDef  *) RCC_BASE)
#define ID		((ID_TypeDef   *) ID_BASE)

/**
  * @}
  */
  /** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */
    
/******************************************************************************/
/*                         Peripheral Registers Bits Definition               */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                      CRC Registers                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_CR register  *******************/  
#define CRC_CR_EN                          ((u32)0x00000001)          /*!< CRC Enable */
#define CRC_CR_CRS                         ((u32)0x00000002)          /*!< CRC Initial */
#define CRC_CR_CIS                         ((u32)0x00000004)          /*!< CRC DataIn Width */
#define CRC_CR_CISN                        ((u32)0x00000008)          /*!< CRC DataIn Width */
#define CRC_CR_CBN                         ((u32)0x00000010)          /*!< CRC DataIn Width */
#define CRC_CR_COSN                        ((u32)0x00000020)          /*!< CRC DataIn Width */
/*******************  Bit definition for CRC_SEED register  *******************/  
#define CRC_SEED_MASK                      ((u32)0x0000FFFF)          /*!< CRC SEED */
/*******************  Bit definition for CRC_POLY register  *******************/  
#define CRC_POLY_MASK                      ((u32)0x0000FFFF)          /*!< CRC POLY */
/*******************  Bit definition for CRC_POLY register  *******************/  
#define CRC_DIN_MASK                       ((u32)0x0000FFFF)          /*!< CRC DATA INPUT */
/*******************  Bit definition for CRC_POLY register  *******************/  
#define CRC_DOUT_MASK                      ((u32)0x0000FFFF)          /*!< CRC DATA OUT */

/******************************************************************************/
/*                                                                            */
/*                      PWR Registers                                         */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for PWR_VDDLVDCTRL register  ******************/
#define PWR_PVDR_PVDE                       ((u32)0x00000001)        /*!<  */
#define PWR_PVDR_PLS                        ((u32)0x0000000E)        /*!<  */

/******************************************************************************/
/*                                                                            */
/*                      RCC Registers                                         */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RCC_HSECR1 register  ******************/
#define RCC_HSECR1_EN               ((u32)0x00000001)        /*!< Enable  */
#define RCC_HSECR1_AAC              ((u32)0x00000002)        /*!< Automatic amplitude control */
#define RCC_HSECR1_ECEN             ((u32)0x00000004)        /*!< External clock enable */
#define RCC_HSECR1_HSEFR            ((u32)0x00000010)        /*!< HSE frequency range */
#define RCC_HSECR1_LPF              ((u32)0x00000300)        /*!< Low pass filter */
#define RCC_HSECR1_LPFB             ((u32)0x00000400)        /*!< Low pass filter bypass */
#define RCC_HSECR1_RDY              ((u32)0x80000000)        /*!< Ready flag */
/********************  Bits definition for RCC_HSECR2 register  ******************/
#define RCC_HSECR2_CAD              ((u32)0x00000007)        /*!< Current adjust */
#define RCC_HSECR2_FDR              ((u32)0x00000300)        /*!< Feedback resistance selection */
/********************  Bits definition for RCC_HSICR register  ******************/
#define RCC_HSICR_EN                ((u32)0x00000001)        /*!< HSI enable */
/********************  Bits definition for RCC_LSICR register  ******************/
#define RCC_LSICR_EN                ((u32)0x00000001)        /*!< LSI enable */
/********************  Bits definition for RCC_PCR register  ******************/
#define RCC_PCR_EN                  ((u32)0x00000001)        /*!< PLL enable */
/********************  Bits definition for RCC_MCOR register  ******************/
#define RCC_MCOR_COPRE              ((u32)0x00000007)        /*!< Clock output prescale */
#define RCC_MCOR_COS                ((u32)0x00000070)        /*!< Clock output Selection */
/********************  Bits definition for RCC_CFGR register  ******************/
#define RCC_CFGR_SCW                ((u32)0x00000003)        /*!< System clock selection */
#define RCC_CFGR_HPRE               ((u32)0x000001F0)        /*!< AHB Prescaler */
#define RCC_CFGR_HSEDE              ((u32)0x00001000)        /*!< HSE fail detection Enable */
#define RCC_CFGR_HSEF               ((u32)0x00002000)        /*!< HSE fail detection Enable */
#define RCC_CFGR_WKCK               ((u32)0x00100000)        /*!< system clock after wakeup */
#define RCC_CFGR_PPRE               ((u32)0x1F000000)        /*!< APB Prescaler */
/********************  Bits definition for RCC_RSR register  ******************/
#define RCC_RSR_SFR                 ((u32)0x00000001)        /*!< software reset */
#define RCC_RSR_IWDR                ((u32)0x00000002)        /*!< iwdg reset */
#define RCC_RSR_CPU                 ((u32)0x00000008)        /*!< CPU reset */
#define RCC_RSR_HSE                 ((u32)0x00000010)        /*!< HSE fail reset */
#define RCC_RSR_POR                 ((u32)0x00000040)        /*!< power reset */
#define RCC_RSR_PVD                 ((u32)0x00000100)        /*!< PVD low voltage reset */
#define RCC_RSR_PIN                 ((u32)0x00000400)        /*!< pin reset */
#define RCC_RSR_CWR                 ((u32)0x00000800)        /*!< Configuration Word reset */
/********************  Bits definition for RCC_ASFCR register  ******************/
#define RCC_ASFCR_KEY               ((u32)0x0000FFFF)        /*!< key */
/********************  Bits definition for RCC_RCR register  ******************/
#define RCC_RCR_PDRE                ((u32)0x00000100)        /*!< PVD low voltage reset enable */

/******************************************************************************/
/*                                                                            */
/*                      IMMC Registers                      */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for IMMC_ACR register  ******************/
#define  IMMC_CR_STAR   		      ((u32)0x00000001)        /*!< 启动IMMC操作 */
//#define  IMMC_CR_CMD              ((u32)0x00000006)        /*!< IMMC操作命令 */
#define  IMMC_CR_WAIT             ((u32)0x000000F0)        /*!< IMMC访问等待周期 */
#define  IMMC_CR_MODE       	    ((u32)0x00000100)        /*!< IMMC读写访问方式 */
#define  IMMC_CR_AINC             ((u32)0x00002000)        /*!< IMMC地址自动递增 */
#define  IMMC_CR_KEY                ((u32)0xFFFF0000)
/*******************  Bit definition for IMMC_ISR register  ******************/																																						
#define  IMMC_SR_WOV                     ((u32)0x00000001)        /*!< 写命令完成 */
#define  IMMC_SR_URPT                    ((u32)0x00000004)  
#define  IMMC_SR_BUSY                    ((u32)0x00000008)        /*!< IMMC忙标志 */
#define  IMMC_SR_CERR                    ((u32)0x00000010)        /*!< IMMC操作命令错误标志 */
#define  IMMC_SR_KERR                    ((u32)0x00000020)        /*!< IMMC密码错误标志 */
#define  IMMC_SR_AERR                    ((u32)0x00000040)        /*!< IMMC地址错误标志 */
#define  IMMC_SR_WTO                     ((u32)0x00000080)
/*******************  Bit definition for IMMC_IER register  ******************/																																							
#define  IMMC_IE_WOVI                   ((u32)0x00000001)        /*!< 写命令完成中断使能 */
#define  IMMC_IE_URPTI                  ((u32)0x00000002)  
#define  IMMC_IE_CERI                   ((u32)0x00000010)        /*!< IMMC操作命令错误中断使能 */
#define  IMMC_IE_KERI                   ((u32)0x00000020)        /*!< IMMC密码错误中断使能 */
#define  IMMC_IE_AERI                   ((u32)0x00000040)        /*!< IMMC地址错误中断使能 */
#define  IMMC_IE_WTOI                   ((u32)0x00000080)
/*******************  Bit definition for IMMC_AR register  *******************/
#define  IMMC_AR_AR                        ((u32)0x0001FFFC)        /*!< Flash Address */
/*******************  Bit definition for IMMC_DR register  *******************/
#define  IMMC_DR_DR                        ((u32)0xFFFFFFFF)        /*!< Flash Address */
/*******************  Bit definition for IMMC_DIV register  *******************/
#define  IMMC_PSC_PSC                      ((u32)0x0000003F)        /*!< Flash Address */
/********************  Bits definition for IMMC_BSR register  ******************/
#define  IMMC_BSR_IAPF                      ((u32)0x00000002)        /*  */
/********************  Bits definition for IMMC_IAPAR register  ******************/
#define  IMMC_IAPAR_AR                      ((u32)0x0003FE00)        /*  */
/********************  Bits definition for IMMC_RPT register  ******************/
#define  IMMC_RPSR_PSR                      ((u32)0x00000001)        /*  */

/******************************************************************************/
/*                                                                            */
/*      Universal Asynchronous Receiver Transmitter (UART)       */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for UART_BR register  *******************/
#define  UART_DR                          ((u16)0x01FF)               /*!< BR[8:0] bits (Receiver Transmitter Buffer value) */
/******************  Bit definition for UART_CR register  *******************/
#define  UART_CR_WP                        ((u32)0x00000007)           /*!< MODE[2:0] bits (工作模式选择) */
#define  UART_CR_STOP                      ((u32)0x00000018)           /*!< STOP[1:0] bits (停止位长度选择) */
#define  UART_CR_PS                        ((u32)0x00000020)           /*!< 奇偶校验方式 */
#define  UART_CR_LPB                       ((u32)0x00000040)           /*!< 回绕模式控制 */
#define  UART_CR_EN                        ((u32)0x00000080)           /*!< 波特率发生器使能 */
#define  UART_CR_RE                        ((u32)0x00000100)           /*!< 数据接收使能 */
#define  UART_CR_RXP                       ((u32)0x00010000)           /*!< 数据接收极性控制 */
#define  UART_CR_TXP                       ((u32)0x00020000)           /*!< 数据发送极性控制 */
#define  UART_CR_SLME                       ((u32)0x00100000)           /*!< OneWire模式使能 */
#define  UART_CR_SLDS                       ((u32)0x00200000)           /*!< OneWire模式收发方向控制 */
/******************  Bit definition for UART_BRR register  *******************/
#define  UART_BRR_BR                       ((u32)0x0000FFFF)               /*!< BRR[15:0] bits (波特率配置) */
#define  UART_BRR_SRC                      ((u32)0x00030000)               /*!< BRR[1:0] bits (采样率控制) */
/******************  Bit definition for UART_IE register  *******************/
#define  UART_IE_RXNEI                   ((u32)0x00000001)        /*!< 接收缓冲队列非空中断允许控制位 */
#define  UART_IE_RXFI                    ((u32)0x00000004)        /*!< 接收缓冲队列全满中断允许控制位 */
#define  UART_IE_PEI                     ((u32)0x00000020)        /*!< 奇偶校验错误中断允许控制位 */      
#define  UART_IE_FEI                     ((u32)0x00000040)        /*!< 帧错误中断允许控制位 */
#define  UART_IE_OVRI                    ((u32)0x00000080)        /*!< 接收缓冲队列溢出中断允许控制位 */    
#define  UART_IE_TXEI                    ((u32)0x00000100)        /*!< 发送缓冲队列全空中断允许控制位 */                
#define  UART_IE_TXFI                    ((u32)0x00000400)        /*!< 发送缓冲队列全满中断允许控制位 */   
#define  UART_IE_TXOI                    ((u32)0x00000800)        /*!< 发送全部完成中断允许控制位 */  
/******************  Bit definition for UART_SR register  *******************/
#define  UART_SR_RXNE                     ((u32)0x00000001)        /*!< 接收缓冲队列非空中断标识位 */
#define  UART_SR_RXF                      ((u32)0x00000004)        /*!< 接收缓冲队列全满中断标识位 */
#define  UART_SR_PE                       ((u32)0x00000020)        /*!< 奇偶校验错误中断标识位 */      
#define  UART_SR_FE                       ((u32)0x00000040)        /*!< 帧错误中断标识位 */
#define  UART_SR_OVR                      ((u32)0x00000080)        /*!< 接收缓冲队列溢出中断标识位 */    
#define  UART_SR_TXE                      ((u32)0x00000100)        /*!< 发送缓冲队列全空中断标识位 */               
#define  UART_SR_TXF                      ((u32)0x00000400)        /*!< 发送缓冲队列全满中断标识位 */   
#define  UART_SR_TXO                      ((u32)0x00000800)        /*!< 发送全部完成中断标识位 */  
/******************  Bit definition for UART_TXFR register  *******************/
#define  UART_TXFR_TXFR                    ((u32)0xFFFFFFFF)        /*!< TXFR[31:0] bits (发送队列复位) */
/******************  Bit definition for UART_RXFR register  *******************/
#define  UART_RXFR_RXFR                    ((u32)0xFFFFFFFF)        /*!< RXFR[31:0] bits (接收队列复位) */ 
/******************  Bit definition for UART_IMCR register  *******************/
#define  UART_IMCR_IRE                       ((u32)0x00000001)        /*!<红外功能使能控制 */
#define  UART_IMCR_IRPN                      ((u32)0x00000002)        /*!<红外发送极性控制 */
#define  UART_IMCR_IRBD                      ((u32)0x00000030)        /*!<SPD[1:0]红外速率选择控制 */
/******************  Bit definition for UART_IMDCR register  *******************/
#define  UART_IMDCR_DUTY                ((u32)0x00000FFF)        /*!< PWMC[11:0] bits (红外调制占空比控制) */

/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for ADC_CR1 register  ******************/
/** @defgroup ADC_channels **/
#define ADC_CR1_EN                          ((u32)0x00000001)       /*!< ADC使能控制            */
#define ADC_CR1_MODE                        ((u32)0x00000002)       /*!< ADC转换模式控制        */
#define ADC_CR1_TRIGS                       ((u32)0x0000000C)  
#define ADC_CR1_TIMS		                ((u32)0x00000070)
#define ADC_CR1_ADVRPS                      ((u32)0x00000300)
#define ADC_CR1_EOCIE                       ((u32)0x00000400)
#define ADC_CR1_ALIGN                       ((u32)0x00000800)
#define ADC_CR1_SOC                         ((u32)0x00001000)
#define ADC_CR1_INNS                        ((u32)0x00002000)
#define ADC_CR1_SCANE                       ((u32)0x00004000)
#define ADC_CR1_EOSIE                       ((u32)0x00008000)
#define ADC_CR1_CHS                         ((u32)0x001F0000)            
#define ADC_CR1_BGS                         ((u32)0x00200000)
#define ADC_CR1_AVGE                        ((u32)0x02000000)
/********************  Bits definition for ADC_CR2 register  ******************/
#define ADC_CR2_RDTC                        ((u32)0x000000FF)
#define ADC_CR2_SMP                         ((u32)0x0000FF00)                
#define ADC_CR2_PSC                         ((u32)0x00FF0000)
#define ADC_CR2_AVGT                        ((u32)0x07000000)
#define ADC_CR2_DFD                         ((u32)0x10000000)
/********************  Bits definition for ADC_SR register  ******************/
#define ADC_SR_RDY                          ((u32)0x00000001)
#define ADC_SR_EOC                          ((u32)0x00000002)
#define ADC_SR_EOS                          ((u32)0x00000004)
/********************  Bits definition for ADC_DR register  ******************/
#define ADC_DR_DATA                         ((u32)0x0000FFFF)
/********************  Bits definition for ADC_SCHR1 register  ******************/
#define ADC_SCHR1_CH0                       ((u32)0x0000001F)
#define ADC_SCHR1_CH1                       ((u32)0x000003E0)
#define ADC_SCHR1_CH2                       ((u32)0x00007C00)
#define ADC_SCHR1_CH3                       ((u32)0x000F8000)
#define ADC_SCHR1_CH4                       ((u32)0x01F00000)
#define ADC_SCHR1_CH5                       ((u32)0x3E000000)
/********************  Bits definition for ADC_SCHR2 register  ******************/
#define ADC_SCHR2_CH6                       ((u32)0x0000001F)
#define ADC_SCHR2_CH7                       ((u32)0x000003E0)
#define ADC_SCHR2_SCNT                      ((u32)0x00070000)
/********************  Bits definition for ADC_BGCR register  ******************/
#define ADC_BGCR_BGNC                       ((u32)0x00000100)    
#define ADC_BGCR_BGE                        ((u32)0x00001000)
#define ADC_BGCR_BGOE                       ((u32)0x00002000)
#define ADC_BGCR_TRIM                       ((u32)0x003F0000)
#define ADC_BGCR_KEY                        ((u32)0xFF000000)
/********************  Bits definition for ADC_SCHDRx register  ******************/
#define ADC_SCHDR0_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR1_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR2_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR3_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR4_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR5_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR6_DATA                     ((u32)0x0000FFFF)    
#define ADC_SCHDR7_DATA                     ((u32)0x0000FFFF)    

/******************************************************************************/
/*                                                                            */
/*                   Inter-integrated Circuit Interface (I2C0)                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for I2C_CR register  *******************/
#define  I2C_CR_ACK                         ((u32)0x00000004)        /* ACK generation (slave mode) */
#define  I2C_CR_SI                          ((u32)0x00000008)        /* Interrupt status */
#define  I2C_CR_STOP                        ((u32)0x00000010)        /* STOP generation (master mode) */
#define  I2C_CR_STAR                        ((u32)0x00000020)        /* START generation */
#define  I2C_CR_EN                          ((u32)0x00000040)        /* Peripheral enable */
#define  I2C_CR_HCT                         ((u32)0x0000F000)        /* CLK filtering delay*/
#define  I2C_CR_BR                          ((u32)0x03FF0000)        /* CLK DIV*/
/*******************  Bit definition for I2C_SR register  *******************/
#define  I2C_SR_SR                           ((u32)0x000000F8)      
/*******************  Bit definition for I2C_DR register  *******************/
#define  I2C_DR_DR                          ((u32)0x000000FF)        /* Enable Broadcast addressing*/    
/*******************  Bit definition for I2C_OAR register  *******************/
#define  I2C_OAR_BC				            ((u32)0x00000001)        /* Enable Broadcast addressing  */    
#define  I2C_OAR_ADDR                       ((u32)0x000000FE)        /* Enable Broadcast addressing  */ 
/*******************  Bit definition for I2C_CCR register  *******************/
#define  I2C_CCR_ACK                        ((u32)0x00000004)        /* ACK generation (slave mode) */
#define  I2C_CCR_SI                         ((u32)0x00000008)        /* Interrupt status */
#define  I2C_CCR_STOP                       ((u32)0x00000010)        /* STOP generation (master mode) */
#define  I2C_CCR_STAR                       ((u32)0x00000020)        /* START generation */
#define  I2C_CCR_EN                         ((u32)0x00000040)        /* Peripheral enable */
#define  I2C_CCR_HCT                        ((u32)0x0000F000)        /* CLK filtering delay*/
#define  I2C_CCR_BR                         ((u32)0x03FF0000)        /* CLK DIV*/

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface (SPI)                   */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for SPI_CR1 register  ********************/
#define  SPI_CR1_DFF                         ((u32)0x0000000F)         /* SPI_data_size */
#define  SPI_CR1_CPOL		                     ((u32)0x00000040)         /* Clock Polarity */
#define  SPI_CR1_CPHA		                     ((u32)0x00000080)         /* Clock Phase */
#define  SPI_CR1_PSC                         ((u32)0x0000FF00)         /* Post-division factor */
/*******************  Bit definition for SPI_CR2 register  ********************/
#define  SPI_CR2_LBM				                 ((u32)0x00000001)         /* Loopback Mode */
#define  SPI_CR2_EN				                 ((u32)0x00000002)         /* SPI ENABLE*/
#define  SPI_CR2_MSM			                   ((u32)0x00000004)         /* Master-slave selection */
#define  SPI_CR2_SOD                         ((u32)0x00000008)       /* 从机输出控制   */
/********************  Bit definition for SPI_DR register  ********************/
#define  SPI_DR_DR                           ((u16)0xFFFF)            /* Data Register */
/********************  Bit definition for SPI_SR1 register  ********************/
#define  SPI_SR1_TXE                            ((u32)0x00000001)         /* Transmission FIFO is empty */
#define  SPI_SR1_TNF                            ((u32)0x00000002)         /* Transmission FIFO is not empty */
#define  SPI_SR1_RXNE                           ((u32)0x00000004)         /* Receiver FIFO is not empty */
#define  SPI_SR1_RXF                            ((u32)0x00000008)         /* Receiver FIFO is Full */
#define  SPI_SR1_BSY                            ((u32)0x00000010)         /* Transmission module is busy */	
#define  SPI_SR1_RXFS                           ((u32)0x00000F00)       /* RXFIFO数据个数控制 */
#define  SPI_SR1_TXFS                           ((u32)0x0000F000)       /* TXFIFO数据格式控制 */
/********************  Bit definition for SPI_BR register  ********************/
#define  SPI_BR_BR                          ((u32)0x000000FF)         /* Prescaler factor */
/********************  Bit definition for SPI_IE register  ********************/
#define  SPI_IE_OVRE                        ((u32)0x00000001)         /* Receiver FIFO overflow */
#define  SPI_IE_OTE                         ((u32)0x00000002)         /* Receiver FIFO Non-empty timeout */
#define  SPI_IE_RXHE                        ((u32)0x00000004)         /* Receiver FIFO Half-full */
#define  SPI_IE_TXHE                        ((u32)0x00000008)         /* Transmission FIFO Half-full */
/********************  Bit definition for SPI_SR2 register  ********************/
#define  SPI_SR2_OVR                        ((u32)0x00000001)         /* Receiver FIFO overflow */
#define  SPI_SR2_OT                         ((u32)0x00000002)         /* Receiver FIFO Non-empty timeout */
#define  SPI_SR2_RXH                        ((u32)0x00000004)         /* Receiver FIFO Half-full */
#define  SPI_SR2_TXH                        ((u32)0x00000008)         /* Transmission FIFO Half-full */
/********************  Bit definition for SPI_IFC register  ********************/
#define  SPI_IC_OVR                       ((u32)0x00000001)         /* Receiver FIFO overflow */
#define  SPI_IC_OT                         ((u32)0x00000002)         /* Receiver FIFO Non-empty timeout */
/********************  Bit definition for SPI_CSS register  ********************/
#define  SPI_CSS_CSS				((u32)0x00000004)         /* CS is controlled by software  */
#define  SPI_CSS_SWCS			    ((u32)0x00000008)         /* CS Set Bit by software  */

#define  SPI_TXFR_TXFR              ((u32)0xFFFFFFFF) 
#define  SPI_RXFR_RXFR              ((u32)0xFFFFFFFF)

/******************************************************************************/
/*                                                                            */
/*                      TIM Registers                                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for TIM_ISR register  *******************/  
#define  TIM_SR_ARF                        ((u32)0x00000001)       /*!<定时器与MR0值匹配中断标志位       */
/*******************  Bit definition for TIM_TCR register  *******************/  
#define  TIM_CR1_EN                        ((u32)0x00000001)       /*!<定时器使能控制位        */
#define  TIM_CR1_UG                        ((u32)0x00000002)       /*!<定时器匹配值更新        */
#define  TIM_CR1_DBGE                      ((u32)0x00000100)
#define  TIM_CR1_BUSY                      ((u32)0x00008000)
/*******************  Bit definition for TIM_PSC register  *******************/  
#define  TIM_PSC_PSC                       ((u32)0x0000FFFF)               /*!<PR[7:0]定时器预分频系数   */
/*******************  Bit definition for TIM_CNT register  *******************/  
#define  TIM_CNT_CNT                       ((u16)0xFFFF)            /*!<PC[15:0]定时器当前计数值   */
/*******************  Bit definition for TIM_MCR register  *******************/  
#define  TIM_CR2_ARI                       ((u32)0x00000001)        /*!<TIM_CNT与MR0值匹配时产生中断控制位          */
#define  TIM_CR2_OPM                       ((u32)0x00000004)        /*!<TIM_CNT与MR0值匹配时计数器停止控制位        */
#define  TIM_CR2_DIR                       ((u32)0x00000008)       /*!<TIM_CNT计数方向控制位                       */
/*******************  Bit definition for PWM_ARR register  *******************/  
#define  TIM_ARR                           ((u32)0x0000FFFF)            /*!<MR0[15:0]定时器MR0匹配值   */

/******************************************************************************/
/*                                                                            */
/*                      TIM1  Registers                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for PWM_SR register  *******************/  
#define  PWM_SR_ARF                      ((u32)0x00000001)       /*!<定时器匹配0标志位       */
#define  PWM_SR_OC1F                     ((u32)0x00000002)       /*!<定时器匹配1标志位       */
#define  PWM_SR_OC2F                     ((u32)0x00000004)       /*!<定时器匹配2标志位       */
#define  PWM_SR_OC3F                     ((u32)0x00000008)       /*!<定时器匹配3标志位       */
#define  PWM_SR_OC4F                     ((u32)0x00000010)       /*!<定时器匹配4标志位       */
#define  PWM_SR_IC1R                     ((u32)0x00000020)       /*!<定时器捕获1上升沿标志位 */
#define  PWM_SR_IC1F                     ((u32)0x00000040)       /*!<定时器匹配1下降沿标志位 */
#define  PWM_SR_IC2R                     ((u32)0x00000080)       /*!<定时器匹配2上升沿标志位 */
#define  PWM_SR_IC2F                     ((u32)0x00000100)       /*!<定时器匹配2下降沿标志位 */
#define  PWM_SR_IC3R                     ((u32)0x00000200)       /*!<定时器匹配3上升沿标志位 */
#define  PWM_SR_IC3F                     ((u32)0x00000400)       /*!<定时器匹配3下降沿标志位 */
#define  PWM_SR_IC4R                     ((u32)0x00000800)       /*!<定时器匹配4上升沿标志位 */
#define  PWM_SR_IC4F                     ((u32)0x00001000)       /*!<定时器匹配4下降沿标志位 */
#define  PWM_SR_BIF                      ((u32)0x00002000)       /*!<定时器刹车输入标志位    */
#define  PWM_SR_UIF                      ((u32)0x00004000)       /*!<更新事件标志位          */
/*******************  Bit definition for PWM_CR1 register  *******************/  
#define  PWM_CR1_EN                    ((u32)0x00000001)       /*!<定时器使能控制位          */
#define  PWM_CR1_UG                    	((u32)0x00000002)       /*!<定时器匹配值更新          */
#define  PWM_CR1_CLKS                   ((u32)0x00000004)       /*!<定时器时钟选择控制        */
#define  PWM_CR1_DBGE                   ((u32)0x00000100)
#define  PWM_CR1_DIR                    ((u32)0x00000200)
#define  PWM_CR1_CMS                    ((u32)0x00000400)
/*******************  Bit definition for PWM_ITARR register  *******************/  
#define  PWM_ITARR_ITARR                       ((u8)0xF)               /*!<INT_RPT[3:0]定时器中断累计次数控制位   */
/*******************  Bit definition for PWM_ITCNT register  *******************/  
#define  PWM_ITCNT_ITCNT                       ((u8)0xF)               /*!<INT_RPTC[3:0]定时器中断累计次数当前计数值   */
/*******************  Bit definition for PWM_PSC register  *******************/  
#define  PWM_PSC_PSC                         ((u8)0xFF)               /*!<PR[7:0]定时器预分频系数   */
/*******************  Bit definition for PWM_CNT register  *******************/  
#define  PWM_CNT_CNT                         ((u16)0xFFFF)            /*!<PC[15:0]定时器当前计数值   */
/*******************  Bit definition for PWM_CR2 register  *******************/  
#define  PWM_CR2_ARI                      ((u32)0x00000001)       /*!<PMW_TC和PWM_ARR匹配时产生中断控制位        */
#define  PWM_CR2_OC1I                     ((u32)0x00000002)       /*!<PMW_TC和PWM_OCR1匹配时产生中断控制位        */
#define  PWM_CR2_OC2I                     ((u32)0x00000004)       /*!<PMW_TC和PWM_OCR2匹配时产生中断控制位        */
#define  PWM_CR2_OC3I                     ((u32)0x00000008)       /*!<PMW_TC和PWM_OCR3匹配时产生中断控制位        */
#define  PWM_CR2_OC4I                     ((u32)0x00000010)       /*!<PMW_TC和PWM_OCR4匹配时产生中断控制位        */
#define  PWM_CR2_OPM                      ((u32)0x00000020)       /*!<PMW_TC和PWM_ARR匹配时计时器停止控制位      */
//#define  PWM_CR2_DIR                      ((u32)0x00000040)     /*!<PWM_CNT计数方向控制位                       */
//#define  PWM_CR2_CMS                      ((u32)0x00000080)     /*!<PWM_CNT计数方向交替控制位                   */
#define  PWM_CR2_UI                      ((u32)0x00000040)       /*!<更新中断使能                   */
/*******************  Bit definition for PWM_ARR register  *******************/  
#define  PWM_ARR_ARR                          ((u16)0xFFFF)            /*!<MR0[15:0]定时器MR0匹配值   */
/*******************  Bit definition for PWM_OCR1 register  *******************/  
#define  PWM_OCR1_OCR                         ((u16)0xFFFF)            /*!<MR1[15:0]定时器MR1匹配值   */
/*******************  Bit definition for PWM_OCR2 register  *******************/  
#define  PWM_OCR2_OCR                         ((u16)0xFFFF)            /*!<MR2[15:0]定时器MR2匹配值   */
/*******************  Bit definition for PWM_OCR3 register  *******************/  
#define  PWM_OCR3_OCR                         ((u16)0xFFFF)            /*!<MR3[15:0]定时器MR3匹配值   */ 
/*******************  Bit definition for PWM_OCR4 register  *******************/  
#define  PWM_OCR4_OCR                         ((u16)0xFFFF)            /*!<MR4[15:0]定时器MR4匹配值   */          
/*******************  Bit definition for PWM_CAPR register  *******************/  
#define  PWM_CAPR_IC1R                    ((u32)0x00000001)       /*!<通道1脉冲上升沿捕捉使能控制          */
#define  PWM_CAPR_IC1F                    ((u32)0x00000002)       /*!<通道1脉冲下降沿捕捉使能控制          */
#define  PWM_CAPR_IC1RC                   ((u32)0x00000004)       /*!<通道1脉冲沿捕捉计数器复位使能控制    */
#define  PWM_CAPR_IC1I                    ((u32)0x00000008)       /*!<通道1脉冲沿捕捉中断使能控制          */
#define  PWM_CAPR_IC2R                    ((u32)0x00000010)       /*!<通道2脉冲上升沿捕捉使能控制          */
#define  PWM_CAPR_IC2F                    ((u32)0x00000020)       /*!<通道2脉冲下降沿捕捉使能控制          */
#define  PWM_CAPR_IC2RC                   ((u32)0x00000040)       /*!<通道2脉冲沿捕捉计数器复位使能控制    */
#define  PWM_CAPR_IC2I                    ((u32)0x00000080)       /*!<通道2脉冲沿捕捉中断使能控制          */
#define  PWM_CAPR_IC3R                    ((u32)0x00000100)       /*!<通道3脉冲上升沿捕捉使能控制          */
#define  PWM_CAPR_IC3F                    ((u32)0x00000200)       /*!<通道3脉冲下降沿捕捉使能控制          */
#define  PWM_CAPR_IC3RC                   ((u32)0x00000400)       /*!<通道3脉冲沿捕捉计数器复位使能控制    */
#define  PWM_CAPR_IC3I                    ((u32)0x00000800)       /*!<通道3脉冲沿捕捉中断使能控制          */
#define  PWM_CAPR_IC4R                    ((u32)0x00001000)       /*!<通道4脉冲上升沿捕捉使能控制          */
#define  PWM_CAPR_IC4F                    ((u32)0x00002000)       /*!<通道4脉冲下降沿捕捉使能控制          */
#define  PWM_CAPR_IC4RC                   ((u32)0x00004000)       /*!<通道4脉冲沿捕捉计数器复位使能控制    */
#define  PWM_CAPR_IC4I                    ((u32)0x00008000)       /*!<通道4脉冲沿捕捉中断使能控制          */
#define  PWM_CAPR_IC1S                    ((u32)0x00070000)       /*!<通道1捕获源选择                     */
#define  PWM_CAPR_ICS1S                   ((u32)0x00080000)       /*!<TI1选择                 */
#define  PWM_CAPR_IC2S                    ((u32)0x00700000)       /*!<通道2捕获源选择          */
#define  PWM_CAPR_IC3S                    ((u32)0x07000000)       /*!<通道3捕获源选择          */
#define  PWM_CAPR_IC4S                    ((u32)0x70000000)       /*!<通道4捕获源选择          */
/*******************  Bit definition for PWM_CR1 register  *******************/  
#define  PWM_ICR1_ICR                       ((u32)0x0000FFFF)       /*!<CAP[15:0]捕捉通道1沿变化计数值   */
/*******************  Bit definition for PWM_CR2 register  *******************/ 
#define  PWM_ICR2_ICR                       ((u32)0x0000FFFF)       /*!<CAP[15:0]捕捉通道2沿变化计数值   */
/*******************  Bit definition for PWM_CR3 register  *******************/  
#define  PWM_ICR3_ICR                       ((u32)0x0000FFFF)       /*!<CAP[15:0]捕捉通道3沿变化计数值   */
/*******************  Bit definition for PWM_CR4 register  *******************/  
#define  PWM_ICR4_ICR                       ((u32)0x0000FFFF)       /*!<CAP[15:0]捕捉通道4沿变化计数值   */
/*******************  Bit definition for PWM_OCMR register  *******************/  
#define  PWM_OCMR_OC1M                       ((u32)0x00000007)       /*!<MC1[2:0]  输出通道1比较输出模式选择    */
#define  PWM_OCMR_OC2M                       ((u32)0x00000070)       /*!<MC2[6:4]  输出通道2比较输出模式选择    */
#define  PWM_OCMR_OC3M                       ((u32)0x00000700)       /*!<MC3[10:8] 输出通道3比较输出模式选择    */
#define  PWM_OCMR_OC4M                       ((u32)0x00007000)       /*!<MC4[14:12]输出通道4比较输出模式选择    */
#define  PWM_OCMR_OIS1              		 ((u32)0x00010000)       /*!<输出通道1初始值                        */
#define  PWM_OCMR_OIS2                 		 ((u32)0x00020000)       /*!<输出通道2初始值                        */
#define  PWM_OCMR_OIS3                 	     ((u32)0x00040000)       /*!<输出通道3初始值                        */
#define  PWM_OCMR_OIS4                       ((u32)0x00080000)       /*!<输出通道4初始值                        */
#define  PWM_OCMR_OIS1N           			 ((u32)0x00100000)       /*!<输出通道1互补输出初始值                */
#define  PWM_OCMR_OIS2N             	     ((u32)0x00200000)       /*!<输出通道2互补输出初始值                */
#define  PWM_OCMR_OIS3N             		 ((u32)0x00400000)       /*!<输出通道3互补输出初始值                */
#define  PWM_OCMR_OIS4N             		 ((u32)0x00800000)       /*!<输出通道4互补输出初始值                */
#define  PWM_OCMR_OC1NE             		 ((u32)0x01000000)       /*!<输出通道1互补输出使能                  */
#define  PWM_OCMR_OC2NE              		 ((u32)0x02000000)       /*!<输出通道2互补输出使能                  */
#define  PWM_OCMR_OC3NE               		 ((u32)0x04000000)       /*!<输出通道3互补输出使能                  */
#define  PWM_OCMR_OC4NE              		 ((u32)0x08000000)       /*!<输出通道4互补输出使能                  */
#define  PWM_OCMR_OC1E              		 ((u32)0x10000000)
#define  PWM_OCMR_OC2E              		 ((u32)0x20000000)
#define  PWM_OCMR_OC3E              		 ((u32)0x40000000)
#define  PWM_OCMR_OC4E              		 ((u32)0x80000000)
/*******************  Bit definition for PWM_BDTR register  *******************/ 
#define  PWM_BDTR_DT              		     ((u32)0x00000FFF)
#define  PWM_BDTR_BKE              		     ((u32)0x00010000)
#define  PWM_BDTR_BKP              		     ((u32)0x00020000)
#define  PWM_BDTR_BKI              		     ((u32)0x00040000)
#define  PWM_BDTR_BKSC              		 ((u32)0x00080000)
#define  PWM_BDTR_BKIC              		 ((u32)0x01000000)
/*******************  Bit definition for PWM_CR3 register  *******************/
#define  PWM_CR3_CC1P              		     ((u32)0x00000001)
#define  PWM_CR3_C1NP              		     ((u32)0x00000002)
#define  PWM_CR3_CC2P              		     ((u32)0x00000010)
#define  PWM_CR3_C2NP              		     ((u32)0x00000020)
#define  PWM_CR3_CC3P              		     ((u32)0x00000100)
#define  PWM_CR3_C3NP              		     ((u32)0x00000200)
#define  PWM_CR3_CC4P              		     ((u32)0x00001000)
#define  PWM_CR3_C4NP              		     ((u32)0x00002000)
/*******************  Bit definition for PWM_TACR register  *******************/
#define  PWM_TACR_OC1UE             		 ((u32)0x00000001)
#define  PWM_TACR_OC1DE             		 ((u32)0x00000002)
#define  PWM_TACR_OC2UE             		 ((u32)0x00000004)
#define  PWM_TACR_OC2DE             		 ((u32)0x00000008)
#define  PWM_TACR_OC3UE             		 ((u32)0x00000010)
#define  PWM_TACR_OC3DE             		 ((u32)0x00000020)
#define  PWM_TACR_OC4UE             		 ((u32)0x00000040)
#define  PWM_TACR_OC4DE             		 ((u32)0x00000080)
#define  PWM_TACR_UOAE             		     ((u32)0x00000100)
#define  PWM_TACR_DOAE             		     ((u32)0x00000200)
#define  PWM_TACR_IC1RAE             		 ((u32)0x00010000)
#define  PWM_TACR_IC1FAE             		 ((u32)0x00020000)
#define  PWM_TACR_IC2RAE             		 ((u32)0x00040000)
#define  PWM_TACR_IC2FAE             		 ((u32)0x00080000)
#define  PWM_TACR_IC3RAE             		 ((u32)0x00100000)
#define  PWM_TACR_IC3FAE             		 ((u32)0x00200000)
#define  PWM_TACR_IC4RAE             		 ((u32)0x00400000)
#define  PWM_TACR_IC4FAE             		 ((u32)0x00800000)
/*******************  Bit definition for PWM_BKICR register  *******************/
#define  PWM_BKICR_BKINE             		 ((u32)0x00000001)
#define  PWM_BKICR_PVDE             		 ((u32)0x00000010)
#define  PWM_BKICR_SWE             		     ((u32)0x00000020)

/******************************************************************************/
/*                                                                            */
/*                        Independent WATCHDOG (IWDG)                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WDG_RLR register  *******************/
#define  IWDG_RLR_RL                         ((u32)0xFFFFFFFF)            /*!< Watchdog counter reload value */
/*******************  Bit definition for WDG_Count register  *******************/ 
#define  IWDG_CNT_CNT                        ((u32)0xFFFFFFFF)            /*!< Watchdog count value          */
/*******************  Bit definition for WDG_CR register  *******************/  
#define  IWDG_CR_EN                          ((u32)0x00000001)       /*!< Enable IWDG        */
#define  IWDG_CR_RSTE                        ((u32)0x00000002)       /*!< RESET IWDG         */
#define  IWDG_CR_DBGE                        ((u32)0x00000004)       /*!< DEBUG IWDG         */
#define  IWDG_KR_KEY                         ((u32)0xFFFFFFFF)
/*******************  Bit definition for WDG_RIS register  *******************/  
#define  IWDG_SR_HDF                         ((u32)0x00000001)               /*!< Watchdog counter reload value update */
/*******************  Bit definition for WDG_KR register  ********************/
#define  IWDG_LOCK_KEY                       ((u32)0xFFFFFFFF)            /*!< Key value (write only, read 0000h) */
#define  IWDG_LOCK_LOCK                      ((u32)0x00000001)            /*!< IWDG LOCK        */

/******************************************************************************/
/*                                                                            */
/*                         ID                                                 */
/*                                                                            */
/******************************************************************************/
#define ID_UDID_ID                          ((u32)0xFFFFFFFF)
#define ID_UID1_UID                         ((u32)0xFFFFFFFF)
#define ID_UID2_UID                         ((u32)0xFFFFFFFF)
#define ID_UID3_UID                         ((u32)0xFFFFFFFF)
#define ID_CID_SWPIN                        ((u32)0x0000F000)

/**
  * @}
  */


#ifdef USE_STDPERIPH_DRIVER
  #include "PT32Y003x_conf.h"
#endif

  
#ifdef __cplusplus
}
#endif

#endif 

