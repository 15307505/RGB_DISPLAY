#include "bsp.h"

TempSensor MY_TempSensor[3]=
{
  {0,0,CH0_SlaveAddress<<1,0},
  {0,0,CH1_SlaveAddress<<1,0},
  {0,0,CH2_SlaveAddress<<1,0},

};


/****************************************
 * 函数名：SetTempeSensor
 * 描述  ：
 * MCU   ：STM8S105
 * 时钟  ：RC 16M
****************************************/
void SetTempeSensor(void)
{
  u8 temp=ConfigurationData;
  MY_TempSensor[0].ActivationFlag=WriteToAdder(MY_TempSensor[0].Adderss,ConfigurationRegiste,&temp,1);
  MY_TempSensor[1].ActivationFlag=WriteToAdder(MY_TempSensor[1].Adderss,ConfigurationRegiste,&temp,1);
  MY_TempSensor[2].ActivationFlag=WriteToAdder(MY_TempSensor[2].Adderss,ConfigurationRegiste,&temp,1);
}
/****************************************
 * 函数名：SetTempeSensor
 * 描述  ：
 * MCU   ：STM8S105
 * 时钟  ：RC 16M
****************************************/
void ReadTempeSensor(void)
{ u8  tempedata[2];
  u32 SceneTempe=0;
  u8 i;
  for(i=0;i<3;i++)
  {
    if(MY_TempSensor[i].ActivationFlag==0)continue;
    else
    {
      ReadFormAdder(MY_TempSensor[i].Adderss,ReadTempRegistet,tempedata,2);
      MY_TempSensor[i].TempData=0;
      MY_TempSensor[i].TempData|=tempedata[0];
      MY_TempSensor[i].TempData<<=8;
      MY_TempSensor[i].TempData|=tempedata[1];
      MY_TempSensor[i].TempData>>=4;
      if(MY_TempSensor[i].TempData&0x800)
      {
        MY_TempSensor[i].TempData=~MY_TempSensor[i].TempData;
        MY_TempSensor[i].TempData+=1;
        MY_TempSensor[i].SubZero=1;/*零下标示号*/
        
      }
      SceneTempe=0;
      SceneTempe=(u32)MY_TempSensor[i].TempData*Ad12BitBasic;
      SceneTempe/=1000;
      MY_TempSensor[i].TempData=(u16)SceneTempe;
      
    }
  
  }

  

  
  
}