#ifndef _IIC_H_
#define _IIC_H_
#include "sys.h"

extern I2C_HandleTypeDef hi2c1;
void _Error_Handler(char *file, int line);
void MX_I2C1_Init(void);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c);
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c);

#endif
