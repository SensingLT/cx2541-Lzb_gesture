#ifndef __UART_H__
#define __UART_H__

#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "tick.h"
#include "protocol.h"

//接收消息的最大长度
#define UART_MAX_REV_LEN 64

#if (DEBUG_MODE > 0)
	#define DBG(fmt, ...) Uart_SendStr(fmt, ##__VA_ARGS__)
	#define DBG_LN(fmt, ...) Uart_SendStr("T%d:"fmt"\r\n", Tick_Get(), ##__VA_ARGS__)
#else
	#define DBG(fmt, ...)
	#define DBG_LN(fmt, ...)
#endif

//不管是否调试模式，都能正常打印，在相应cmd命令的时候使用
#define Uart_SendStrForCmd(fmt, ...)  Uart_SendStr(fmt, ##__VA_ARGS__)

void Uart_Init(uint32_t baud);

void Uart_SendData(const uint8_t* pData, uint16_t length);

int Uart_SendStr(const char* fmt, ...);



//返回值为正，表示成功；为0表示没有要接收的数据；如果为负，说明pBuf长度不够，取绝对值为本次所需长度
int Uart_GetRevMsg(uint8_t* pBuf, uint16_t bufSize);

#endif //__UART_H__