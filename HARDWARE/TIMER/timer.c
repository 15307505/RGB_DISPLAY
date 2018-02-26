#include "bsp.h"

//V1.1 20160106
//����TIM3_PWM_Init����,����PWM��� 
//V1.2 20160106
//����TIM5_CH1_Cap_Init����,�������벶��
//V1.3 20160620
//����TIM7_Init����,���ڴ���3���ݽ��ճ�ʱ�ж�
////////////////////////////////////////////////////////////////////////////////// 

TIM_HandleTypeDef TIM2_Handler;         //��ʱ��3PWM��� 
TIM_OC_InitTypeDef TIM2_CH1Handler;	    //��ʱ��3ͨ��4���


/***************************************************************************
****************************************************************************
  ������PWM���ʵ����غ���Դ��
****************************************************************************
****************************************************************************/
 
//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr,u16 psc)
{ 
    TIM2_Handler.Instance=TIM2;            //��ʱ��3
    TIM2_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM2_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM2_Handler);       //��ʼ��PWM
    
    TIM2_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM2_CH1Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM2_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH1Handler,TIM_CHANNEL_1);//����TIM3ͨ��4
    HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_1);//����PWMͨ��4
}

//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
		
	  __HAL_RCC_TIM2_CLK_ENABLE();			//ʹ�ܶ�ʱ��2
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_15;           	//PB1
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	  GPIO_Initure.Alternate= GPIO_AF1_TIM2;	//PA15����ΪTIM2_CH1
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}


//����TIMͨ��4��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM2Compare1(u32 compare)
{
	TIM2->CCR1=compare;
}

//��ȡTIM����/�ȽϼĴ���ֵ
u32 TIM_GetTIM2Capture1(void)
{
	return  HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_1);
}


/***************************************************************************
****************************************************************************
  ���������벶�����Դ��ʵ����غ���Դ��
****************************************************************************
****************************************************************************/


TIM_HandleTypeDef TIM5_Handler;         //��ʱ��5���


//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{  
    TIM_IC_InitTypeDef TIM5_CH1Config;  
    
    TIM5_Handler.Instance=TIM5;                          //ͨ�ö�ʱ��5
    TIM5_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM5_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_IC_Init(&TIM5_Handler);//��ʼ�����벶��ʱ������
    
    TIM5_CH1Config.ICPolarity=TIM_ICPOLARITY_RISING;    //�����ز���
    TIM5_CH1Config.ICSelection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM5_CH1Config.ICPrescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM5_CH1Config.ICFilter=0;                          //���������˲��������˲�
    HAL_TIM_IC_ConfigChannel(&TIM5_Handler,&TIM5_CH1Config,TIM_CHANNEL_1);//����TIM5ͨ��1
	
    HAL_TIM_IC_Start_IT(&TIM5_Handler,TIM_CHANNEL_1);   //����TIM5�Ĳ���ͨ��1�����ҿ��������ж�
    __HAL_TIM_ENABLE_IT(&TIM5_Handler,TIM_IT_UPDATE);   //ʹ�ܸ����ж�
}


//��ʱ��5�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_IC_Init()����
//htim:��ʱ��5���
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM5_CLK_ENABLE();            //ʹ��TIM5ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //�����������
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    GPIO_Initure.Alternate=GPIO_AF2_TIM5;   //PA0����ΪTIM5ͨ��1
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

    HAL_NVIC_SetPriority(TIM5_IRQn,2,0);    //�����ж����ȼ�����ռ���ȼ�2�������ȼ�0
    HAL_NVIC_EnableIRQ(TIM5_IRQn);          //����ITM5�ж�ͨ��  
}


//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)


//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM5_Handler);//��ʱ�����ô�����
}
 

//��ʱ�������жϣ�����������жϴ���ص������� �ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
{
	
	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
	}		
}

//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
		if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
        {	  			
            TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
            TIM5CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM5_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
            TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
            TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
		}else  								//��δ��ʼ,��һ�β���������
        {
            TIM5CH1_CAPTURE_STA=0;			//���
            TIM5CH1_CAPTURE_VAL=0;
            TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
            __HAL_TIM_DISABLE(&TIM5_Handler);        //�رն�ʱ��5
            __HAL_TIM_SET_COUNTER(&TIM5_Handler,0);
            TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
            TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
            __HAL_TIM_ENABLE(&TIM5_Handler);//ʹ�ܶ�ʱ��5
        }		    
	}		
}

/***************************************************************************
****************************************************************************
  ������TIM7���Դ��ʵ����غ���Դ�룬ͨ�ö�ʱ��
****************************************************************************
****************************************************************************/

TIM_HandleTypeDef TIM7_Handler;         //��ʱ��7���

//ͨ�ö�ʱ��7�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��7!(��ʱ��7����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM7_Init(u16 arr,u16 psc)
{  
    __HAL_RCC_TIM7_CLK_ENABLE();                        //ʹ��TIM7ʱ��
    
    TIM7_Handler.Instance=TIM7;                          //ͨ�ö�ʱ��7
    TIM7_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM7_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM7_Handler);
    HAL_TIM_Base_Start_IT(&TIM7_Handler);   //ʹ�ܶ�ʱ��7�Ͷ�ʱ��7�����жϣ�TIM_IT_UPDATE   
    
    HAL_NVIC_SetPriority(TIM7_IRQn,0,1);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
    HAL_NVIC_EnableIRQ(TIM7_IRQn);          //����ITM7�ж� 

    __HAL_TIM_ENABLE(&TIM7_Handler);        //�򿪶�ʱ��7	
}

//��ʱ��7�жϷ�����
void TIM7_IRQHandler(void)
{
    if(__HAL_TIM_GET_FLAG(&TIM7_Handler,TIM_FLAG_UPDATE)!=RESET)    //�����ж�
    {
        __HAL_TIM_CLEAR_IT(&TIM7_Handler,TIM_IT_UPDATE);            //����ж�
        //__HAL_TIM_DISABLE(&TIM7_Handler);                           //�رն�ʱ��7 
			  if(USART1_RXD_Chaoshi != 0)
				{
					USART1_RXD_Chaoshi--;
					if(USART1_RXD_Chaoshi == 0)
					{
						//GPS_Analysis(&gpsx,(u8*)USART1_RX_BUF);//�����ַ���
						USART1_RXD_Flag = 1;
					}
				}
			  tp_dev.scan(1);//����ɨ��
    }
}




