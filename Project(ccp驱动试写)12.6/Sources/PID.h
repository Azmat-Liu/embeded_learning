#include "includes.h"
#ifndef _PID_H_
#define _PID_H_


  struct PIDSING  
  {
   int  Proportion;         //  比例常数 Proportional Const
   int  Integral;           //  积分常数 Integral Const
   int  Derivative;         //  微分常数 Derivative Const
   dword  LastError;
   dword  lastUk;
   int    NegativePIDLimit;  
   int    PostivePIDLimit; 
  };
  
#endif                             