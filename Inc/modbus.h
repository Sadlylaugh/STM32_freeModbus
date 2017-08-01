#ifndef __MODBUS_H_
#define __MODBUS_H_

#include "mb.h"
#include "mbport.h"
#include "port.h"



/*线圈状态寄存器*/
#define REG_COILS_START 0x0000
#define REG_COILS_SIZE 8

/*线圈状态输入寄存器*/
#define REG_DISCRETE_START 0x0000
#define REG_DISCRETE_SIZE 8

/*保持寄存器*/
#define REG_HOLDING_START 0x0000
#define REG_HOLDING_NREGS 10




#endif
