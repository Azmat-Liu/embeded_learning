#include "includes.h"
#ifndef _ECT_H_                                                             
#define _ECT_H_


  #define IC0_BUFFERSIZE  15
  #define PULESECOUNT     64
  
  
  struct IC_Parameters_Tag
  { 
   byte  IC0_StopFlag;
   //u8  Speed_StopFlag;
   byte  OverFlowCount;
   word  IC0Counter;
   word  IC0LastCounter;
   dword IC0;
   dword IC0_Buffer[IC0_BUFFERSIZE];   
  };
  extern struct IC_Parameters_Tag Pca;
  
  void InitECT(void);
  word readSpeed(void);


#endif