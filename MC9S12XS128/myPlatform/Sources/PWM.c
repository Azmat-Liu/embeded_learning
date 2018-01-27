#include "PWM.h"


void InitPWM(void)     //使用锁相环后频率变为2kHZ,输出转速6000rpm
{
   PWMPOL_PPOL1   = 1;           //1通道先高后低
   PWMCLK_PCLK1   = 1;           //1使用SA时钟源
   PWMPRCLK_PCKA  = 0x04;        //A时钟为总线16分频，clockA=32M/16=2M
   PWMCAE         = 0x00;        //左线形输出
   PWMSCLA        = 0x04;        //Clock SA = Clock A / (2 * PWMSCLA) = 250KHZ
   PWMPER1        = 0x64;        //PWMxPeriod = PWMPERx / Clock SA = 100 / 250KHZ = 2.5KHZ
}


byte do_ctlDuty(char duty_t,byte dir)      
{
   if(duty_t > 100 || duty_t < 0)
      return 1;
   if(dir == SHIFT_DOWN)
   {
     MotorINA = Enable;
     MotorINB = Disable;
     PWMDTY1  = duty_t;        //读取占空比
     PWME_PWME1 = Enable;   //使能1通道
   } 
   else if(dir == SHIFT_UP)
   { 
     MotorINA = Disable;
     MotorINB = Enable;                                                                  
     PWMDTY1  = duty_t;        //读取占空比
     PWME_PWME1 = Enable;   //使能1通道
   }
   return 0;
}

void do_motorStop(void) 
{
   MotorINA = Disable;
   MotorINB = Disable;                                                                  
   PWMDTY1  = 0;        //读取占空比
   PWME_PWME1 = Disable;   //使能1通道  
}


