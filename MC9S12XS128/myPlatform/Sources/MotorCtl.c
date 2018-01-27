#include "MotorCtl.h"

/**********************************************************************
*  说明:  电机自动控制函数，输入目标值、测量值和控制精度
*         即可实现对电机的自动控制
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/
int pidError;   //偏差
char duty;
byte motorCtl(word target,word measure,byte accuracy)
{
  char range;
  if(accuracy > 100 || accuracy < 0){
    printk("out of range \n");
    return 1;
  }
  range = (char)accuracy;   //必须强制转换为有符号的类型否则比较的结果不正确
  pidError = target - measure; 
  
  if(pidError > range || pidError < -range){
    duty = pidCalc(target,measure);
    
    if(duty >= 0){
      if(do_ctlDuty(duty,SHIFT_UP))
        printk("duty out of range \n");
    }
    else{
      if(do_ctlDuty(-duty,SHIFT_DOWN))
        printk("duty out of range \n");
    }
  }else{
    do_motorStop();
    pid.lastUk = 0;
    pid.LastError = 0;
  }
  return 0;
}