/**
	******************************************************************************
	* @file          	MyUart.h
	* @author			sadlylaugh
	* @version
	* @date			2017年6月29日
	* @brief		STM32的简易自定义程序，实现了串口IDLE空闲中断方式+DMA发送与接收
	* 				目前在STM32F407和STM32F429测试通过
	*
	******************************************************************************
	*/


#ifndef _MYUART_H_
#define _MYUART_H_

#include "usart.h"

#define USE_MYUARTLIB
#define USE_UARTx 2

#define RECIVE_BUF_SIZE 200
#define MyUart_BUSY 1
#define MyUart_READY 0

/* 根据需要确定要使用的串口，默认认为串口和DMA都已经完成初始化 */
#if USE_UARTx == 1
	#define MyUart_Handle huart1
#elif USE_UARTx == 2
	#define MyUart_Handle huart2
#endif

typedef struct
{
	uint8_t rx_flag;	//确认是否有接收帧
	uint8_t tx_flag;	//判断串口是否发送忙
	uint16_t rx_len;
	uint8_t rx_buf[RECIVE_BUF_SIZE];
}MyUart_TypeDef;

extern MyUart_TypeDef MyUart;


void MyUart_Init();
void MyUart_SendData_DMA(uint8_t *data, uint16_t size);
void MyUart_ReciveIDLE_IT(UART_HandleTypeDef *huart);
void MyUart_RxThenTxTest(void);
#endif


