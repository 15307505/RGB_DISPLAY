#include "bsp.h"

/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ��Ӳ���豸��ֻ��Ҫ����һ�Ρ��ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����
*			 ȫ�ֱ�����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
	/*
		����ST�̼���������ļ��Ѿ�ִ����CPUϵͳʱ�ӵĳ�ʼ�������Բ����ٴ��ظ�����ϵͳʱ�ӡ�
		�����ļ�������CPU��ʱ��Ƶ�ʡ��ڲ�Flash�����ٶȺͿ�ѡ���ⲿSRAM FSMC��ʼ����

		ϵͳʱ��ȱʡ����Ϊ168MHz�������Ҫ���ģ������޸� system_stm32f4xx.c �ļ�
	*/
	  HAL_Init(); 
	  Stm32_Clock_Init(360,25,2,8);   //����ʱ��,168Mhz
    delay_init(180);                //��ʼ����ʱ����
    usart1_init(115200);            //��ʼ��USART
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    SDRAM_Init();                   //SDRAM��ʼ��
    LCD_Init();                     //LCD��ʼ��
		GPS_Init();                     //GPS��ʼ��
		RTC_Init();                     //RTC��ʼ��
		//MY_ADC_Init();                  //ADC��ʼ��
	  tp_dev.init();				          //��������ʼ��
		TIM7_Init(10-1,9000-1);	        //1ms�ж�һ�� 
		TIM2_PWM_Init(500-1,90-1);      //90M/90=1M�ļ���Ƶ�ʣ��Զ���װ��Ϊ500����ôPWMƵ��Ϊ1M/500=2kHZ
		Beep_Init();                    //��������ʼ��
		
		PrintfLogo();                   //RTT ��ӡ�豸��Ϣ
		//MX_I2C1_Init();                 //Ӳ��IIC��ʼ��
		//TMP75_Init();                   //TMP75 �¶ȴ�������ʼ��
		
		delay_ms(500);
}

#define EXAMPLE_NAME	"Super GPS"
#define EXAMPLE_DATE	"2018-2-3"
#define DEMO_VER		  "1.1"
/*
*********************************************************************************************************
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷�������, ���ϴ����ߺ󣬴�PC���ĳ����ն�������Թ۲���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void PrintfLogo(void)
{
	/* ���CPU ID */
	{
		/* �ο��ֲ᣺
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
	SEGGER_RTT_printf(0,"* Name   : %s\r\n", EXAMPLE_NAME);	/* ��ӡ�������� */
	SEGGER_RTT_printf(0,"* Demo   : %s\r\n", DEMO_VER);		/* ��ӡ���̰汾 */
	SEGGER_RTT_printf(0,"* Date   : %s\r\n", EXAMPLE_DATE);	/* ��ӡ�������� */

	/* ��ӡST�̼���汾����3���������stm32f4xx.h�ļ��� */
	//SEGGER_RTT_printf(0,"* Hardware Ver : V%d.%d.%d (STM32F4xx_StdPeriph_Driver)\r\n", __STM32F4XX_STDPERIPH_VERSION_MAIN,__STM32F4XX_STDPERIPH_VERSION_SUB1,__STM32F4XX_STDPERIPH_VERSION_SUB2);

	SEGGER_RTT_printf(0,"* \r\n");	/* ��ӡһ�пո� */
	SEGGER_RTT_printf(0,"* QQ    : 15307505 \r\n");
	SEGGER_RTT_printf(0,"* Email : 15307505@qq.com \r\n");
	SEGGER_RTT_printf(0,"* WWW.WOQIONG.CC\r\n");
	SEGGER_RTT_printf(0,"*************************************************************\n\r");
	SEGGER_RTT_printf(0,"\n\r");
}

