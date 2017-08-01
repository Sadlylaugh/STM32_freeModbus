```
文件目录
.
├── freeModbus_STM32.ioc
├── Inc
│   ├── dma.h
│   ├── gpio.h
│   ├── main.h
│   ├── modbus.h
│   ├── MyUart.h
│   ├── stm32f4xx_hal_conf.h
│   ├── stm32f4xx_it.h
│   ├── tim.h
│   └── usart.h
├── modbus
│   ├── functions
│   │   ├── mbfunccoils.c
│   │   ├── mbfuncdiag.c
│   │   ├── mbfuncdisc.c
│   │   ├── mbfuncholding.c
│   │   ├── mbfuncinput.c
│   │   ├── mbfuncother.c
│   │   └── mbutils.c
│   ├── include
│   │   ├── mbconfig.h
│   │   ├── mbframe.h
│   │   ├── mbfunc.h
│   │   ├── mb.h
│   │   ├── mbport.h
│   │   ├── mbproto.h
│   │   └── mbutils.h
│   ├── mb.c
│   ├── port
│   │   ├── portevent.c
│   │   ├── port.h
│   │   ├── portserial.c
│   │   └── porttimer.c
│   └── rtu
│       ├── mbcrc.c
│       ├── mbcrc.h
│       ├── mbrtu.c
│       └── mbrtu.h
├── README.md
└── Src
    ├── dma.c
    ├── gpio.c
    ├── main.c
    ├── modbus.c
    ├── MyUart.c
    ├── stm32f4xx_hal_msp.c
    ├── stm32f4xx_it.c
    ├── system_stm32f4xx.c
    ├── tim.c
    └── usart.c

7 directories, 44 files
```

* 基于STM32F429与STM32CubeMx实现的freeModbus移植，目前只实现了RTU从机模式，使用的资源有UART1和TIM4
* 主要的modbus库位于modbus/中，其中modbus/port/包括主要的移植工作，其中对于Cube代码的修改主要为MX_TIM4_Init,增加了分频和计数重载值的形参，目的是实现不同串口波特率下modbus也可以自适应工作。
* 中断处理程序位于Src/stm32f4xx_it.c，使用RXNE和TXE中断调用modbus回调函数进行单字符的接收发送处理
* Src/modbus.c定义了modbus寄存器结构和实现了所有处理函数，使用时main.c中请务必包括modbus.h
* 注释掉了modbus/functions/*.c中所有的usRegAddress++，以便地址寻址从0开始
* 附有个人使用的UART库MyUart，实现了UART2的IDLE空闲中断接收帧+全DMA传输，为了使用方便将中断处理程序放在了Src/MyUart.c
* 参考教程：
    https://www.dhlx.wang/STM32F411VET6/Porting_FreeModbus_to_STM32F411VET6_based_on_STM32CubeF4.html

    http://www.stm32cube.com/question/19

    http://www.tuicool.com/articles/iQF7ba

    http://blog.sina.com.cn/s/blog_502ad2450102x1sh.html

