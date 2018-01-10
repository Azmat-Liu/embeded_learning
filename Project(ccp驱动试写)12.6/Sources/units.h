#include "includes.h"
#ifndef _UNITS_H_
#define _UNITS_H_

struct Transmission_Tags 
{
  byte a1;
  byte a2;
  byte a3;
  byte a4;
  byte a5;
  byte a6;
  byte a7;
  byte a8;
};

extern word ccptest;
extern word speed;
extern word adValue;
extern struct Transmission_Tags Trans;

extern void memorycopy(byte *from,byte *to,word len);
extern void DFlashmemorycopy(dword from,byte *to,word len);
extern void motorCtl(void);


  
#endif 