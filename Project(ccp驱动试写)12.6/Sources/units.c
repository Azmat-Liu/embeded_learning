#include "units.h"

word ccptest;
word speed;
word adValue;



void memorycopy(byte *from,byte *to,word len)
{
  word i;
  for(i=0;i<len;i++)
     *to++ = *from++; 
}


struct Transmission_Tags Trans;

void DFlashmemorycopy(dword from,byte *to,word len)
{
  word i;
  word check;
  check = *(volatile unsigned int *__far)from;
  if(check != 0xffff) {                         //检测DFlash是否被写过
      for(i=0;i<len;i++) {
        *to++ = *(volatile unsigned char *__far)from++; 
        _FEED_COP();
    }
  }
  memorycopy(ccpCalBuffer,&Trans,sizeof(Trans)); //将Buffer中的数据写入Trans
}

void motorCtl(void)
{
  if(ccpCalBuffer[0] == 1)
    motorStop();
  else if(ccpCalBuffer[0] == 2)
    (void)ctlDuty(35,SHIFT_UP);
  else if(ccpCalBuffer[0] == 3)
    (void)ctlDuty(50,SHIFT_DOWN);
}


