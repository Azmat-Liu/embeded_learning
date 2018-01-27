#include "includes.h"
#ifndef _DIAG_H_
#define _DIAG_H_

  typedef enum ERR 
  {
    TCU_NONEERR=0,
    TCU_SYSINITERR,
    TCU_SENSORERR,
    TCU_COMMUERR,
  }ERR_TAG;
  
  extern int ERRNO;   //¹Ø¼ü±äÁ¿
  extern byte early_selfDiagnose(void);
  extern void reportError(int errno);
  
#endif 