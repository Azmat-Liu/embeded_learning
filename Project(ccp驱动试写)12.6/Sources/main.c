#include "includes.h"


word heartbeat;  //程序运行时循环相加
  
/***********************************************************
*                   main函数（函数主体）                 
***********************************************************/
dword Address=0,Address2=0;
CCP_BYTE test;
CCP_BYTE testTab[4]={0x00,0x7f,0x04,0x00};
CCP_MTABYTEPTR aaa;
dword bbb,testaddress=0;
byte aaaa,bbbb,ccc;
void main(void) 
{
  /*DisableInterrupts;
   InitPLL();
   (void)DFlash_Init();
   (void)InitMSCAN0();
   InitSCI0();
   InitPIT();
   InitECT();
   ccpInit();     //初始化CCP
   ccpInitCalPage();  //初始化标定页
   ccpDaqOdtInit();   //初始化DAQ列表
   _ENABLE_COP_X();   //使能看门狗
	EnableInterrupts;*/
	
	(void)sysInit();
	   
  
  for(;;) 
  {
    heartbeat++;
    _FEED_COP();     //喂狗
    
    schUpdate();
    
    if(ccpBackground())
      ;

    /*aaa=ccpGetPointer(0,(*(CCP_DWORD*)&testTab[0]));
    aaa=testTab;
    bbb=*(CCP_DWORD*)&testTab[0];
    aaaa +=1;
    //ccp.DaqList[0].odt[0][0].ptr = (CCP_DAQBYTEPTR)&aaaa;
    bbbb = *ccp.DaqList[0].odt[0][0].ptr; 
    //aaa=(byte *)bbb;
    testaddress = (dword)aaa;
    ccc = *(volatile unsigned char *__far)testaddress; 
    //*(char *)(8448) = 34;
    //*(char *)(8449) = 43;
    //test = ccpUnlock(&testTab[2]); 
    //ccpCalibrationBuffer[9] = DFlash_READbyte(2,0,0,0);
    //ccpCalBuffer[8] =*(volatile unsigned char *__far)(0x100000+1024);
    Address = (dword)(&ccpCalBuffer[0]);
    *(char *)Address =0xff;
    Address2 = (dword)((CCP_MTABYTEPTR)&ccpCalBuffer[1]);
    *(CCP_MTABYTEPTR)Address2 =0xaa; */


  }              
}  
