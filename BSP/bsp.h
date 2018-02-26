#ifndef _BSP_H
#define _BSP_H

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "SEGGER_RTT.h"  //使用JLink SEGGER RTT来打印和输入调试信息
#include "gps.h"
#include "rtc.h"
//#include "adc.h"

#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
#include "timer.h"
#include "beep.h"
#include "myiic.h"
//#include "sensor.h"
//#include "i2c.h"
#include "TMP75.h"
#include "iic.h"  //硬件IIC
#include "gt5688.h"
#include "touch.h"
#include "stdlib.h"
#include "math.h"

void bsp_Init(void);
void PrintfLogo(void);
#endif
