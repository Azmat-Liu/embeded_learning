#include "includes.h"
#ifndef _UNITS_H_
#define _UNITS_H_

#define GEAR0  (adValue >= 150 && adValue <= 750)
#define GEAR1  (adValue > 750)
#define GEAR2  (adValue < 150)

struct Transmission_Tags 
{
  byte pid_p;
  byte pid_i;
  byte pid_d;
  word mspeed_up;
  word mspeed_uplimit;
  word mspeed_dn;
  word mspeed_dnlimit;
  word mspeed_dnreserve;
  
  word adTarget_upoff;
  word adTarget_upsync;
  word adTarget_upon;
  word adTarget_upend;
  word adTarget_dnoff;
  word adTarget_dnsync;
  word adTarget_dnon;
  word adTarget_dnend;
};

extern word ccptest;
extern word speed;
extern word adValue;
extern word adVoltage;
extern word adTarget;
extern struct Transmission_Tags Trans;

extern void memorycopy(byte *from,byte *to,word len);
extern void DFlashmemorycopy(dword from,byte *to,word len);
extern void sciCmd_Decode(void);


  
#endif 