#include "led.h"

//DS2 PF6  DS1 PF7    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOF_CLK_ENABLE();           //����GPIOFʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7; //
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET);	  //PB0��1 
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET);	  //PB1��1  
}
