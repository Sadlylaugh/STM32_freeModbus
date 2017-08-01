/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#define HTIMx htim4
/* ----------------------- static functions ---------------------------------*/
void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
	/*
	 * 90MHz APB1频率下，使用4500分频使得计数周期为20 000,即50us一周期
	 * 加上usTim1timeout50us作溢出上限，可以由软件自己根据波特率值计算得到3.5字符的超时中断时间
	 * 当波特率大于19200时，超时时间会固定为35*50us = 1750us
	 * 但是目前测试来看，使用时钟频率为180Mhz的STM32F429，当串口波特率工作在14400波特率以下时，
	 * modbus_poll软件无法获取到数据，暂时不知道问题出在哪里
	 */
	MX_TIM4_Init(4500, usTim1Timerout50us);
    return TRUE;
}


inline void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
	__HAL_TIM_CLEAR_IT(&HTIMx,TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&HTIMx,TIM_IT_UPDATE);
	__HAL_TIM_SET_COUNTER(&HTIMx,0);
	__HAL_TIM_ENABLE(&HTIMx);
}

inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
	__HAL_TIM_DISABLE(&HTIMx);
	__HAL_TIM_SET_COUNTER(&HTIMx,0);
	__HAL_TIM_DISABLE_IT(&HTIMx,TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&HTIMx,TIM_IT_UPDATE);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}


