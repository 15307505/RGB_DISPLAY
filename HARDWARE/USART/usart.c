#include "bsp.h"

UART_HandleTypeDef UART1_Handler; //UART1���
//TIM_HandleTypeDef TIM7_Handler;   //��ʱ��7���

//���ڷ��ͻ����� 	
__align(8) u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 	//���ͻ���,���USART1_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 				      //���ջ���,���USART1_MAX_RECV_LEN���ֽ�.
u16 USART1_RXD_Chaoshi;  //����1��ʱ��ʱ��
u8  USART1_RXD_Flag;

//ͨ���жϽ�������2���ַ�֮���ʱ������20ms�������ǲ���һ������������.
//���2���ַ����ռ������20ms,����Ϊ����1����������.Ҳ���ǳ���20msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
vu16 USART1_RX_STA=0;   	 
void USART1_IRQHandler(void)
{
	u8 res;
	//__HAL_TIM_ENABLE(&TIM7_Handler); //ʹ�ܶ�ʱ��7
	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
        HAL_UART_Receive(&UART1_Handler,&res,1,1000); 
        //__HAL_TIM_SET_COUNTER(&TIM7_Handler,0);	//���������			     
				USART1_RX_BUF[USART1_RX_STA++]=res;	//��¼���յ���ֵ
        USART1_RXD_Chaoshi = 20;		//15ms��ʱ���
        if(USART1_RX_STA > USART1_MAX_RECV_LEN)	
				{
						USART1_RX_STA = 0;
				}					
	}  													 
}   

//��ʼ��IO ����1
//bound:������ 
void usart1_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_Initure;
	       
	//UART3 ��ʼ������
	__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
	__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��

	GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
	GPIO_Initure.Pull=GPIO_PULLUP;			//����
	GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
	GPIO_Initure.Alternate=GPIO_AF7_USART1;	//����ΪUSART1
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PB10

	GPIO_Initure.Pin=GPIO_PIN_10;			      //PB11
	GPIO_Initure.Pull=GPIO_PULLDOWN;			//����
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PB11

	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()��ʹ��UART1
    
  __HAL_UART_ENABLE_IT(&UART1_Handler,UART_IT_RXNE);  //���������ж�
	HAL_NVIC_EnableIRQ(USART1_IRQn);				    //ʹ��USART1�ж�ͨ��
	HAL_NVIC_SetPriority(USART1_IRQn,0,2);			    //��2�����ȼ�0,2,������ȼ� 
 
	USART1_RX_STA=0;				    //���� 
}
