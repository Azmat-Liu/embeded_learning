#include "PID.h"



/*************************************************************************
*  说明:  增量型PI算法
*        
*  作者:  Azmat
*  日期:  2017.12.13
**************************************************************************/

struct PIDSING pid;
 
static int do_pidCalc(word GiveValue,word MeasureValue,struct PIDSING *pp)
{
   int dError,Error;
   int Uk,Duk;
   Error = GiveValue-MeasureValue;     // 偏差
   dError = Error - pp->LastError;     // 当前微分
   Duk=pp->Proportion*dError+pp->Integral*Error;
   Uk=pp->lastUk + Duk/100;
   pp->LastError = Error;
   pp->lastUk = Uk;
   if(Uk>pp->PostivePIDLimit)
      Uk=pp->PostivePIDLimit;
   if(Uk<pp->NegativePIDLimit)
      Uk=pp->NegativePIDLimit;
   pp->lastUk=Uk;
   return Uk;
}
//*pid参数初始化
void pidInit(void)
{
  pid.Proportion       = Trans.pid_p;
  pid.Integral         = Trans.pid_i;
  pid.Derivative       = Trans.pid_d;
  pid.LastError        = 0;
  pid.lastUk           = 0;
  pid.NegativePIDLimit = -1000;
  pid.PostivePIDLimit  = 1000;
}

//*计算pid返回值
char pidCalc(word GiveValue,word MeasureValue) 
{
  int  pidValue;
  char rtnValue;
  
  pidValue = do_pidCalc(GiveValue,MeasureValue,&pid);
  rtnValue = (char)(pidValue/10); 
  
  if(rtnValue >= 0 && rtnValue < 20)
    rtnValue = 20;
  else if(rtnValue <=0 && rtnValue > -20)
    rtnValue = -20;
  return rtnValue;  
}

//设置pid参数
void pidSetPara(int P_t,int I_t,int D_t,int lastError,int lastUk,int n_limit,int p_limit)
{
  pid.Proportion       = P_t;
  pid.Integral         = I_t;
  pid.Derivative       = D_t;
  pid.LastError        = lastError;
  pid.lastUk           = lastUk;
  if(n_limit > -1000)
    pid.NegativePIDLimit = n_limit;
  else
    pid.NegativePIDLimit = -1000;
  if(p_limit < 1000)
    pid.PostivePIDLimit  = p_limit;
  else
    pid.PostivePIDLimit  = 1000;
}



















