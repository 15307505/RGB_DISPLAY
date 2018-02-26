#include "beep.h"
    
void Beep_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOI_CLK_ENABLE();           //开启GPIOF时钟
	
    GPIO_Initure.Pin=GPIO_PIN_8; //
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET);	  //PB0置1   
}
