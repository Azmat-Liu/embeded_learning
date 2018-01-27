#include "includes.h"
#ifndef _EXTCCP_H_
#define _EXTCCP_H_

  //解锁的seed
  #define PL_CAL_SEED 0x0AE38E3A
  #define PL_PGM_SEED 0x0AEF8EA3
  #define PL_DAQ_SEED 0x0AE38E38
  
  //该文件中所有需要外部调用的函数均已在CCP.h文件中声明
  extern CCP_BYTE ccpCalBuffer[256];  //定义ccp标定的Buffer共256个字节
  extern CCP_BYTE ccpPROGRAMBuffer[256];   //定义ccp程序刷新Buffer共1024个字节



#endif