#include "includes.h"
#ifndef _PID_H_
#define _PID_H_


  struct PIDSING  
  {
   int  Proportion;         //  比例常数 Proportional Const
   int  Integral;           //  积分常数 Integral Const
   int  Derivative;         //  微分常数 Derivative Const
   int  LastError;
   int  lastUk;
   int  NegativePIDLimit;  
   int  PostivePIDLimit; 
  };
  extern struct PIDSING pid;
  extern void pidInit(void);
  extern char pidCalc(word GiveValue,word MeasureValue);
  extern void pidSetPara(int P_t,int I_t,int D_t,int lastError,int lastUk,int n_limit,int p_limit);
  
#endif                             