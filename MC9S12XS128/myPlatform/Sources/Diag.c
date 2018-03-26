#include "Diag.h"
/**********************************************************************
*  说明:  软件自检及错误处理相关函数
*        
*  作者:  Azmat
*  日期:  2017.1.8
***********************************************************************/

int ERRNO;   //错误码(关键变量)


//*初始化诊断函数
byte early_selfDiagnose(void) 
{
  #if 0
  speed = readSpeed();  //读取转速
  adValue = atdChannel(1);  //读取ad值
  if(speed < 0 || speed > 1000) {
    printk("please check speed sensor");
    return TCU_SENSORERR;
  }
  if(adValue < 100 || adValue > 900){
    printk("please check gear sensor");
    return TCU_SENSORERR;  
  }
  if(adVoltage > 1000){
    printk("battery voltage too high/low");
    return TCU_SENSORERR;
  }
  //if(CANACCESS)   can连接异常(由中断来读取)
    //return TCU_COMMUERR;
  #endif
  
  return TCU_NONEERR;
}

void reportError(int errno)
{
  if(errno)
    ;
}