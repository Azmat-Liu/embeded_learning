#include "includes.h"


word heartbeat;  //程序运行时循环相加
  
/***********************************************************
*                   main函数（函数主体）                 
***********************************************************/
void main(void) 
{
	
	ERRNO=sysInit(); //系统初始化
	
	for(;;)
	{
	  _FEED_COP();       //喂狗
	  ERRNO = early_selfDiagnose();   //早期自检
	  reportError(ERRNO);             //错误报告
	  while(ERRNO == TCU_NONEERR)     //若系统正常
	  {
	    heartbeat++;
      _FEED_COP();     //喂狗
      
      schUpdate();     //换挡任务调度
	  }
	}
    /*
    ccp.DaqList[0].odt[0][0].ptr = (CCP_DAQBYTEPTR)&aaaa;
    bbbb = *ccp.DaqList[0].odt[0][0].ptr; 
    */
}  
