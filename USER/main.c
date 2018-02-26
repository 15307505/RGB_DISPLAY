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
	  bsp_Init(); //Ӳ����ʼ��
	
	  GPS_On(); //��GPS
	  RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS,0); //����WAKE UP�ж�,1�����ж�һ��  
    POINT_COLOR=RED;
	  LCD_Clear(WHITE);
	  Beep = !Beep;
	  
	  //TMP75_Get_Temperature();
	  TIM_SetTIM2Compare1(BL_PWM);		//500 �  0����	
    while(1)
    {
		  POINT_COLOR=RED;	  
			LCD_ShowString(50,40,260,32,32,"Super RGB Display"); 	
			LCD_ShowString(50,80,240,32,32,"LTDC TEST");     					       					 
			
      RTC_Show();
			DS1=!DS1;	 
			//SEGGER_RTT_printf(0,"Test: %ld\r\n",Get_Adc(6));      //Jlink��ӡ����
			//SEGGER_RTT_Read(0,rtt_buf,sizeof(rtt_buf));           //��ȡJLINK����̨���͵�����
			//SEGGER_RTT_WriteString(0,"�ַ���");                   //ֱ������ַ���
			delay_ms(50);
      Gps_Msg_Show();	//��Ļ��ʾGPS��Ϣ
      if(USART1_RXD_Flag == 1)
			{
				USART1_RXD_Flag = 0;
				//gps_pro(USART1_RX_BUF,USART1_RX_STA);//�����ַ���
				SEGGER_RTT_printf(0,"%d\r\n",USART1_RX_STA);      //Jlink��ӡ����
				USART1_RX_STA = 0;
			}				
	}
}

