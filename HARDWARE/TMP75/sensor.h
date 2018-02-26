#ifndef   _SENSOR_H_
#define   _SENSOR_H_

#include "sys.h"

#define CH0_SlaveAddress          0x48//0b1001000
#define CH1_SlaveAddress          0x49//0b1001001
#define CH2_SlaveAddress          0x4a//0b1001010

#define ConfigurationData         0x60;// OS R1 R0 F1 F0 POL TM SD R1=R0=1 12bit
#define ReadTempRegistet          0x00

#define ConfigurationRegiste      0x01
#define Ad12BitBasic              625

typedef struct                
{
    u16   TempData;
    u8    ActivationFlag;
    u8    Adderss;
    u8    SubZero;
}TempSensor;

extern TempSensor MY_TempSensor[3];

extern void IicPortInit(void);
extern u8 WriteToAdder(u8 DE_Adder,u8 RE_Adder,u8 *Com,u8 len);
extern u8 ReadFormAdder(u8 DE_Adder,u8 RE_Adder,u8 *P,u8 len);
extern void ReadFormAdderToData(u8 DE_Adder,u8 *P,u8 len);

extern void SetTempeSensor(void);
extern void ReadTempeSensor(void);

#endif