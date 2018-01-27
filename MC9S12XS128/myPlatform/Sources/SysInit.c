#include "SysInit.h"

/**********************************************************************
*  说明:  系统初始化相关函数
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/

//*初始化锁相环
static void InitPLL(void)           //总线时钟fbus=32M
{
    CLKSEL &= 0x7f;       //总线时钟=OSCCLK/2
    PLLCTL &= 0x8F;       //禁止PLL
    CRGINT &= 0xDF;
    
    #if(BUS_CLOCK == 40000000) 
      SYNR = 0x44;
    #elif(BUS_CLOCK == 32000000)
      SYNR = 0x43;     
    #elif(BUS_CLOCK == 24000000)
      SYNR = 0x42;
    #endif 

    REFDV = 0x81;         //PLLCLK=2×OSCCLK×(SYNDIV+1)/(REFDIV+1)＝64MHz ,fbus=32M
    PLLCTL =PLLCTL|0x70;  //Enable PLL circuit
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;        //set PLLCLK as sysclk
}

/***********************************************************************
*  说明:  板级驱动模块初始化相关函数
*        
*  作者:  Azmat
*  日期:  2017.12.3
************************************************************************/
static byte modulesInit(void)
{
  
   InitPLL();
   (void)InitDFlash();
   (void)InitMSCAN0();
   InitSCI0();
   InitPIT();
   InitECT();
   InitATD();
   InitPWM();
  
   return 0;
}
/***********************************************************************
*  说明:  GPIO端口设置
*        
*  作者:  Azmat
*  日期:  2017.12.3
************************************************************************/

static void gpioInit(void)
{
  //can芯片控制
  CANSlope_Dir  = 1;
  CANSlope      = 0;
  //电机驱动芯片端口设置
  MotorINA_Dir   = 1;
  MotorINB_Dir   = 1;
    
  MotorINA   = Disable;
  MotorINB   = Disable;
  
}

/***********************************************************************
*  说明:  用户函数及变量初始化
*        
*  作者:  Azmat
*  日期:  2017.12.3
************************************************************************/
static void dataInits(void)  //变量初始化
{
    word i;
    for(i=0;i<IC0_BUFFERSIZE;i++)     //初始化ectBuffer
          Pca.IC0_Buffer[i] = 250000; 
    adTarget = 200;
}

static void userInit(void)
{
  ccpInit();         //初始化CCP结构体
  ccpInitCalPage();  //初始化标定页
  ccpDaqOdtInit();   //初始化DAQ列表
  DFlashmemorycopy(DFLASH_START,(byte *)&ccpCalBuffer,sizeof(ccpCalBuffer));  //0x10 0000为DFlash的基址
  pidInit();         //初始化PID参数
  dataInits();
}

/**********************************************************************
*  说明:  系统初始化主函数
*        
*  作者:  Azmat
*  日期:  2017.12.22
***********************************************************************/

byte sysInit(void)
{
  DisableInterrupts;
    _DISABLE_COP();    //关闭看门狗
    
    if(modulesInit())
      return TCU_SYSINITERR;   //模块初始化故障
    gpioInit();
    userInit();
    
    _ENABLE_COP_X();   //使能看门狗
  EnableInterrupts;
  
  printk("System Initialization Finished !\n");    //打印信息
  
  return TCU_NONEERR;
}


