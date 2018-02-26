#ifndef _TMP75_H_
#define _TMP75_H_
#include "sys.h"

void TMP75_Write_Register(uint8_t Address, uint8_t Pointer_Register, uint8_t Configuration_Byte);
void TMP75_Read_Register(uint8_t Address, uint8_t Pointer_Register, uint8_t* pData);
void TMP75_Init(void);
uint16_t TMP75_Get_Temperature(void);

#endif
