#include "includes.h"
#ifndef _SYSINIT_H_
#define _SYSINIT_H_

  #define BUS_CLOCK		   32000000	   //总线频率
  #define OSC_CLOCK		   16000000	   //晶振频率
  //can芯片端口
  #define CANSlope           PTP_PTP0  
  #define CANSlope_Dir       DDRP_DDRP0
  //电机驱动芯片端口
  #define MotorINA_Dir       DDRA_DDRA7   
  #define MotorINB_Dir       DDRA_DDRA3
  #define MotorINA           PORTA_PA7 
  #define MotorINB           PORTA_PA3
extern byte sysInit(void);
  
#endif 