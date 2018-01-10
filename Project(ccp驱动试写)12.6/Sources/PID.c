#include "PID.h"



/**********************************************/
/*              定义PID结构体                 */
/**********************************************/

struct PIDSING pid;
 
int pidCalc(word GiveValue,word MeasureValue,struct PIDSING *pp)
{
 long dError,Error;
 long Uk,Duk;
 Error = GiveValue-MeasureValue;     // 偏差
 dError = Error - pp->LastError;     // 当前微分
 Duk=pp->Proportion*dError+pp->Integral*Error;
 Uk=pp->lastUk+Duk;
 pp->LastError = Error;
 pp->lastUk=Uk;
 if(Uk>pp->PostivePIDLimit)
    Uk=pp->PostivePIDLimit;
 if(Uk<pp->NegativePIDLimit)
    Uk=pp->NegativePIDLimit;
 pp->lastUk=Uk;
 return Uk;
}








