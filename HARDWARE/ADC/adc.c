#include "bsp.h"	

ADC_HandleTypeDef ADC3_Handler;//ADC���

//��ʼ��ADC
//ch: ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
void MY_ADC_Init(void)  //PF8  ADC3_6
{ 
    ADC3_Handler.Instance=ADC3;
    ADC3_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;   //4��Ƶ��ADCCLK=PCLK2/4=90/4=22.5MHZ
    ADC3_Handler.Init.Resolution=ADC_RESOLUTION_12B;             //12λģʽ
    ADC3_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //�Ҷ���
    ADC3_Handler.Init.ScanConvMode=DISABLE;                      //��ɨ��ģʽ
    ADC3_Handler.Init.EOCSelection=DISABLE;                      //�ر�EOC�ж�
    ADC3_Handler.Init.ContinuousConvMode=DISABLE;                //�ر�����ת��
    ADC3_Handler.Init.NbrOfConversion=1;                         //1��ת���ڹ��������� Ҳ����ֻת����������1 
    ADC3_Handler.Init.DiscontinuousConvMode=DISABLE;             //��ֹ����������ģʽ
    ADC3_Handler.Init.NbrOfDiscConversion=0;                     //����������ͨ����Ϊ0
    ADC3_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //�������
    ADC3_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//ʹ���������
    ADC3_Handler.Init.DMAContinuousRequests=DISABLE;             //�ر�DMA����
    HAL_ADC_Init(&ADC3_Handler);                                 //��ʼ�� 
}

//ADC�ײ��������������ã�ʱ��ʹ��
//�˺����ᱻHAL_ADC_Init()����
//hadc:ADC���
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC3_CLK_ENABLE();            //ʹ��ADC3ʱ��
    __HAL_RCC_GPIOF_CLK_ENABLE();			      //����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_8;            //P
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
}

//���ADCֵ
//ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//����ֵ:ת�����
u16 Get_Adc(u32 ch)   
{
    ADC_ChannelConfTypeDef ADC3_ChanConf;
    
    ADC3_ChanConf.Channel=ch;                                   //ͨ��
    ADC3_ChanConf.Rank=1;                                       //��1�����У�����1
    ADC3_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //����ʱ��
    ADC3_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&ADC3_Handler,&ADC3_ChanConf);        //ͨ������
	
    HAL_ADC_Start(&ADC3_Handler);                               //����ADC
	
    HAL_ADC_PollForConversion(&ADC3_Handler,10);                //��ѯת��
 
	return (u16)HAL_ADC_GetValue(&ADC3_Handler);	        //�������һ��ADC3�������ת�����
}
//��ȡָ��ͨ����ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u32 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
