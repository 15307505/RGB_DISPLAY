#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化硬件设备。只需要调用一次。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。
*			 全局变量。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Init(void)
{
	/*
		由于ST固件库的启动文件已经执行了CPU系统时钟的初始化，所以不必再次重复配置系统时钟。
		启动文件配置了CPU主时钟频率、内部Flash访问速度和可选的外部SRAM FSMC初始化。

		系统时钟缺省配置为168MHz，如果需要更改，可以修改 system_stm32f4xx.c 文件
	*/
	  HAL_Init(); 
	  Stm32_Clock_Init(360,25,2,8);   //设置时钟,168Mhz
    delay_init(180);                //初始化延时函数
    usart1_init(115200);            //初始化USART
    LED_Init();                     //初始化LED 
    KEY_Init();                     //初始化按键
    SDRAM_Init();                   //SDRAM初始化
    LCD_Init();                     //LCD初始化
		GPS_Init();                     //GPS初始化
		RTC_Init();                     //RTC初始化
		//MY_ADC_Init();                  //ADC初始化
	  tp_dev.init();				          //触摸屏初始化
		TIM7_Init(10-1,9000-1);	        //1ms中断一次 
		TIM2_PWM_Init(500-1,90-1);      //90M/90=1M的计数频率，自动重装载为500，那么PWM频率为1M/500=2kHZ
		Beep_Init();                    //蜂鸣器初始化
		
		PrintfLogo();                   //RTT 打印设备信息
		//MX_I2C1_Init();                 //硬件IIC初始化
		//TMP75_Init();                   //TMP75 温度传感器初始化
		
		delay_ms(500);
}

#define EXAMPLE_NAME	"Super GPS"
#define EXAMPLE_DATE	"2018-2-3"
#define DEMO_VER		  "1.1"
/*
*********************************************************************************************************
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void PrintfLogo(void)
{
	/* 检测CPU ID */
	{
		/* 参考手册：
			32.6.1 MCU device ID code
			33.1 Unique device ID register (96 bits)
		*/
		uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;

		CPU_Sn0 = *(__IO uint32_t*)(0x1FFF7A10);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FFF7A10 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FFF7A10 + 8);
    SEGGER_RTT_printf(0,"*************************************************************\n\r");
		SEGGER_RTT_printf(0,"\r\nCPU : STM32F429II, LQFP176, FREQ: %dMHz\r\n", SystemCoreClock / 1000000);
		SEGGER_RTT_printf(0,"UID = %08X %08X %08X\n\r", CPU_Sn2, CPU_Sn1, CPU_Sn0);
	}

	SEGGER_RTT_printf(0,"\n\r");
	SEGGER_RTT_printf(0,"*************************************************************\n\r");
	SEGGER_RTT_printf(0,"* Name   : %s\r\n", EXAMPLE_NAME);	/* 打印例程名称 */
	SEGGER_RTT_printf(0,"* Demo   : %s\r\n", DEMO_VER);		/* 打印例程版本 */
	SEGGER_RTT_printf(0,"* Date   : %s\r\n", EXAMPLE_DATE);	/* 打印例程日期 */

	/* 打印ST固件库版本，这3个定义宏在stm32f4xx.h文件中 */
	//SEGGER_RTT_printf(0,"* Hardware Ver : V%d.%d.%d (STM32F4xx_StdPeriph_Driver)\r\n", __STM32F4XX_STDPERIPH_VERSION_MAIN,__STM32F4XX_STDPERIPH_VERSION_SUB1,__STM32F4XX_STDPERIPH_VERSION_SUB2);

	SEGGER_RTT_printf(0,"* \r\n");	/* 打印一行空格 */
	SEGGER_RTT_printf(0,"* QQ    : 15307505 \r\n");
	SEGGER_RTT_printf(0,"* Email : 15307505@qq.com \r\n");
	SEGGER_RTT_printf(0,"* WWW.WOQIONG.CC\r\n");
	SEGGER_RTT_printf(0,"*************************************************************\n\r");
	SEGGER_RTT_printf(0,"\n\r");
}

