#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

extern TIM_HandleTypeDef TIM2_Handler;      //定时器3PWM句柄 
extern TIM_OC_InitTypeDef TIM2_CH1Handler;  //定时器3通道4句柄
extern TIM_HandleTypeDef TIM5_Handler;      //定时器5句柄
extern TIM_HandleTypeDef TIM7_Handler;      //定时器7句柄

void TIM2_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM2Compare1(u32 compare);
u32 TIM_GetTIM2Capture1(void);
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);
void TIM7_Init(u16 arr,u16 psc);
#endif

