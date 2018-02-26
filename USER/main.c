#include "bsp.h"

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

u16 BL_PWM=100;		

void RTC_Show(void)
{
		u8 tbuf[40];
		HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
		sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds); 
		LCD_ShowString(50,140,210,16,16,tbuf);	
		HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
		sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date); 
		LCD_ShowString(50,160,210,16,16,tbuf);	
		sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.WeekDay); 
		LCD_ShowString(50,180,210,16,16,tbuf);
}
int main(void)
{
	  u8 i;
	  bsp_Init(); //硬件初始化
	
	  GPS_On(); //打开GPS
	  RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS,0); //配置WAKE UP中断,1秒钟中断一次  
    POINT_COLOR=RED;
	  LCD_Clear(WHITE);
	  Beep = !Beep;
	  
	  //TMP75_Get_Temperature();
	  TIM_SetTIM2Compare1(BL_PWM);		//500 最暗  0最亮	
    while(1)
    {
		  POINT_COLOR=RED;	  
			LCD_ShowString(50,40,260,32,32,"Super RGB Display"); 	
			LCD_ShowString(50,80,240,32,32,"LTDC TEST");     					       					 
			
      RTC_Show();
			DS1=!DS1;	 
			//SEGGER_RTT_printf(0,"Test: %ld\r\n",Get_Adc(6));      //Jlink打印数据
			//SEGGER_RTT_Read(0,rtt_buf,sizeof(rtt_buf));           //获取JLINK调试台发送的数据
			//SEGGER_RTT_WriteString(0,"字符串");                   //直接输出字符串
			delay_ms(50);
      Gps_Msg_Show();	//屏幕显示GPS信息
      if(USART1_RXD_Flag == 1)
			{
				USART1_RXD_Flag = 0;
				//gps_pro(USART1_RX_BUF,USART1_RX_STA);//分析字符串
				SEGGER_RTT_printf(0,"%d\r\n",USART1_RX_STA);      //Jlink打印数据
				USART1_RX_STA = 0;
			}				
	}
}

