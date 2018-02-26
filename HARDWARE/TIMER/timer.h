#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

extern TIM_HandleTypeDef TIM2_Handler;      //��ʱ��3PWM��� 
extern TIM_OC_InitTypeDef TIM2_CH1Handler;  //��ʱ��3ͨ��4���
extern TIM_HandleTypeDef TIM5_Handler;      //��ʱ��5���
extern TIM_HandleTypeDef TIM7_Handler;      //��ʱ��7���

void TIM2_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM2Compare1(u32 compare);
u32 TIM_GetTIM2Capture1(void);
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);
void TIM7_Init(u16 arr,u16 psc);
#endif

