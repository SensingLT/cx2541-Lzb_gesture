#include <stdarg.h>
#include <string.h>
#include "PT32Y003x.h"
#include "uart.h"
#include "tick.h"
//#include "inner_defines.h"


/*
 * 特殊点说明：
 * 485半双工通信，PD4高电平发送，PD4低电平接收
 *
 */
//接收时间间隔超过这个时长认为是2条消息
#define MSG_GAP_TICKS 5



static volatile uint8_t gRevBuf[UART_MAX_REV_LEN + 1];
static volatile uint16_t gRevLen = 0;
static volatile uint32_t gLastRevTick = 0;
static volatile uint32_t gOtherInts = 0;


//uart0中断服务程序
#if 1
void UART0_Handler(void) {
    if (UART_GetFlagStatus(UART0, UART_FLAG_RXNE) == SET) {
        uint32_t curTick = Tick_Get();
        
        uint32_t passedTick = curTick - gLastRevTick;
        if (passedTick > MSG_GAP_TICKS) {
            //task as a new msg
            gRevLen = 0;
            //接收字符串后，保证有个\0结尾
            memset((void*)&gRevBuf, 0, sizeof(gRevBuf));
        }
        gLastRevTick = curTick;
        
        do {
            uint8_t revByte = (uint8_t)UART_ReceiveData(UART0);
            if (gRevLen < UART_MAX_REV_LEN) {
                gRevBuf[gRevLen++] = revByte;
            }
            //else 清空不要了
        } while (UART_GetFlagStatus(UART0, UART_FLAG_RXNE) == SET);
    } else {
        gOtherInts++;
    }
}
#else 
void UART0_Handler(void) {
    while (UART_GetFlagStatus(UART0, UART_FLAG_RXNE)) {
        printf("%c", UART_ReceiveData(UART0));
    }
    if (UART_GetFlagStatus(UART0, UART_FLAG_RXF)) {
        printf("FULL");
    }
}
#endif


//返回值为正，表示成功；为0表示没有要接收的数据；如果为负，说明pBuf长度不够，取绝对值为本次所需长度
int Uart_GetRevMsg(uint8_t* pBuf, uint16_t bufSize) {
    //需要关中断执行
    UART_ITConfig(UART0, UART_IT_RXNEI, DISABLE);
    if (Tick_Since(gLastRevTick) > MSG_GAP_TICKS) {
        if (bufSize < gRevLen) {
            UART_ITConfig(UART0, UART_IT_RXNEI, ENABLE);
            return -gRevLen;
        }
        
        int revLen = gRevLen;
        
        if (revLen > 0) {
            memcpy(pBuf, (const void*)gRevBuf, revLen);
            gRevLen = 0;
        }
        UART_ITConfig(UART0, UART_IT_RXNEI, ENABLE);
        return revLen;
    }
    UART_ITConfig(UART0, UART_IT_RXNEI, ENABLE);
    return 0;
}

static void switchToSendMode(bool sendMode) {
    if (sendMode) {
        GPIO_SetBits(GPIOD, GPIO_Pin_4);
    } else {
        GPIO_ResetBits(GPIOD, GPIO_Pin_4);
    }
}

//9600的时候，第32个字节会被改写，容易出问题，115200的时候，比较正常
void Uart_Init(uint32_t baud)
{
    //初始化接收管理控制块
    //gLastRevTick = 0;
    //gRevLen = 0;

    /* 配置UART管脚的复用功能 */
    GPIO_DigitalRemapConfig(AFIOD, GPIO_Pin_5, AFIO_AF_0,ENABLE); //PD5 TX0
    GPIO_DigitalRemapConfig(AFIOD, GPIO_Pin_6, AFIO_AF_0,ENABLE); //PD6 RX0

    //配置485收发控制引脚，PD4高电平发送，PD4低电平接收
    GPIO_InitTypeDef gpioCfg;
    GPIO_StructInit(&gpioCfg);
    gpioCfg.GPIO_Pin = GPIO_Pin_4;
    gpioCfg.GPIO_Mode = GPIO_Mode_OutPP;
    gpioCfg.GPIO_Pull = GPIO_Pull_NoPull;
    GPIO_Init(GPIOD, &gpioCfg);

    /*NVIC配置*/
    NVIC_InitTypeDef nvicCfg;
    nvicCfg.NVIC_IRQChannel = UART0_IRQn; //设置中断向量号
    nvicCfg.NVIC_IRQChannelCmd = ENABLE; //设置是否使能中断
    nvicCfg.NVIC_IRQChannelPriority = 2; //设置中断优先级
    NVIC_Init(&nvicCfg);
    UART_ITConfig(UART0, UART_IT_RXNEI, ENABLE);


    /*初始化UART0*/
    UART_InitTypeDef uartCfg;
    uartCfg.UART_BaudRate = baud;
    uartCfg.UART_WordLengthAndParity = UART_WordLengthAndParity_8D;
    uartCfg.UART_StopBitLength = UART_StopBitLength_1;
    uartCfg.UART_ParityMode = UART_ParityMode_Even;
    uartCfg.UART_Receiver = UART_Receiver_Enable;
    uartCfg.UART_LoopbackMode = UART_LoopbackMode_Disable;
    UART_Init(UART0, &uartCfg);

    /*开启UART0的收发功能*/
    UART_Cmd(UART0, ENABLE);
    
    switchToSendMode(false);
}

void Uart_SendData(const uint8_t* pData, uint16_t length)
{
    switchToSendMode(true);

    for (int i = 0; i < length; i++) {
        //UART_SendData(UART0, pData[i]);
        
        //只要发送队列没满，就写入
        while((UART0->SR & UART_SR_TXF));
        UART0->DR = pData[i];
    }
    //等待发送队列为空（发送完成），关闭发送模式
    while(!(UART0->SR & UART_SR_TXE));
    
    Tick_Delay(2); //mcu发送完毕，不代表485控制器发送完成，所以需要稍微等一下
    
    switchToSendMode(false);
}

//这个函数不能调用太频繁，不然接收状态一直被打断从而导致接收不到数据
int Uart_SendStr(const char* fmt, ...) {
    static char buf[128]; //根据应用需求调整大小
    va_list args;

    va_start(args, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    
    if (n > 0) {
        Uart_SendData((const uint8_t*)buf, n);
    }

    return n;
}

//cmd交互场景下的打印, release模式也能使用
int Uart_SendCmdStr(const char* fmt, ...) {
    static char buf[128]; //根据应用需求调整大小
    va_list args;

    va_start(args, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    
    if (n > 0) {
        Uart_SendData((const uint8_t*)buf, n);
    }

    return n;
}

