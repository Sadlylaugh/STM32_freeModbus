/**
	******************************************************************************
	* @file          	MyUart.h
	* @author			moonwalker
	* @version
	* @date			2017年6月29日
	* @brief
	*
	******************************************************************************
	*/


#ifndef APPLICATION_USER_MYUART_H_
#define APPLICATION_USER_MYUART_H_

#include "usart.h"

#define RECIVE_BUF_SIZE 200
#define MyUart_BUSY 1
#define MyUart_READY 0
#define MyUart_Handle huart2
typedef struct
{
	uint8_t rx_flag;
	uint8_t tx_flag;
	uint16_t rx_len;
	uint8_t rx_buf[RECIVE_BUF_SIZE];
}MyUart_TypeDef;

extern MyUart_TypeDef MyUart1;
void MyUart_Init();
void MyUart_SendData_DMA(uint8_t *data, uint16_t size);
void MyUart_ReciveIDLE_IT(UART_HandleTypeDef *huart);

#endif


