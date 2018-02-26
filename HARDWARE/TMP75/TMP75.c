#include "bsp.h"

/***************************************** TMP75 CODEBEGIN******************************************/
/**
* Function: TMP75_Write_Register();
* Description: Write TMP75 Register;
* Calls: HAL_I2C_Mem_Write();
* Called By: TMP75_Init(), TMP75_Get_Temperature;
* Input: uint8_t Address, uint8_t Pointer_Register, uint8_t Configuration_Byte;
* Output: None;
* Return: None;Page 3
* Other: Slave Address: 
* Pointer Register Byte : P7~P0 = 0 P1 P0 Register Bit
* 0 0 ONLY R Temperature Register 2Byte Byte1 ©\>High Byte2 ©\> Low
* 0 1 R/W Configuration Register 1Byte OS R1 R0F1 F0 POL TM SD
* 1 0 R/W T_low Register 2Byte Byte1 ©\>High Byte2 ©\> Low
* 1 1 R/W T_high Register 2Byte Byte1 ©\>High Byte2 ©\> Low
*
* OS ©\> One Shot The device When Shutdown StatusWrite 1 Start a SingleConversion
* R1/R0 ©\> Converter Resolution 00: 9bit@27.5ms 01: 10bit@55ms 10:11bit@110ms 11: 12bit@220ms
* F1/F0 ©\> Fault Queue 00: 1 00: 2 00: 4 00: 6
* POL ©\> Polarity 0: ALERT Active Low 1: ALERT ActiveHigh Default 0
* TM ©\> Thermostat Mode 0: comparator Mode 1: Interrupt Mode
* SD ©\> Shutdown Mode 0: Maintains a Continuous Conversion 1: Turnsoff When the Current Conversion Completed
*/
void TMP75_Write_Register(uint8_t Address, uint8_t Pointer_Register, uint8_t Configuration_Byte)
{
  HAL_I2C_Mem_Write(&hi2c1, Address, Pointer_Register, 1, &Configuration_Byte, 1, 0x10);
}

 /**
* Function: TMP75_Read_Register();
* Description: Read TMP75 Register;
* Calls: HAL_I2C_Master_Transmit(), HAL_I2C_Master_Receive();
* Called By: TMP75_Init(), TMP75_Get_Temperature;
* Input: uint8_t Address, uint8_t Pointer_Register, uint8_t* pData;
* Output: None;
* Return: None;
* Other: Slave Address: Write 0x90 ; Read 0x91
*/
void TMP75_Read_Register(uint8_t Address, uint8_t Pointer_Register, uint8_t* pData)
{
 HAL_I2C_Master_Transmit(&hi2c1, Address, &Pointer_Register, 1, 0x10);
 HAL_I2C_Master_Receive(&hi2c1, Address, pData , 2, 0x10);
}

 /**
* Function: TMP75_Init();
* Description: Init TMP75 Register;
* Calls: TMP75_Write_Register(), TMP75_Read_Register(), OLED_WriteCmd(),OLED_FillScreen();
* Called By: Int Main();
* Input: None;
* Output: None;
* Return: None;
* Other: OS R1 R0 F1 F0 POL TM SD 01100000 0x60
*/
void TMP75_Init(void)
{
	uint8_t Check[2];
  //´Ó»úµØÖ· 1 0 0 1 A2 A1 A0 R/W   0Ð´ 1¶Á
	TMP75_Write_Register(0x4E, 0x01, 0x60);
	TMP75_Read_Register(0x4F, 0x01, Check);
	if(Check[0] == 0x60)
	{
		SEGGER_RTT_printf(0,"Temp Sensor ok!");
	}
	else
	{
		SEGGER_RTT_printf(0,"Temp Sensor fail!");
	}
}

 /**
* Function: TMP75_Get_Temperature();
* Description: Read TMP75 Register To Get Temperature;
* Calls: TMP75_Read_Register();
* Called By: Int Main();
* Input: None;
* Output: None;
* Return: uint16_t Temperature;
* Other: None;
*/

uint16_t TMP75_Get_Temperature(void)
{
		uint8_t TMP75[2] = {0};
		uint16_t Temperature = {0};

		TMP75_Read_Register(0x4f, 0x00, TMP75);

		Temperature = ( (uint16_t)TMP75[0] << 4 ) | ( (uint16_t)TMP75[1] >> 4 );

		if(TMP75[0] > 0x7f)
		{
				Temperature = ~ Temperature + 1;
		}

		Temperature = (float)Temperature * 6.25; //up to 100

		return Temperature;
}
