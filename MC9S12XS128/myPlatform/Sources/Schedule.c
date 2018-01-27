#include "Schedule.h"

/**********************************************************************
*  说明:  任务调度相关函数
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/
#define PROCESS0  0
#define PROCESS1  2
#define PROCESS2  3
#define PROCESS3  4
#define PROCESS4  5
#define PROCESS5  6
#define PROCESS6  7
#define PROCESS7  8

#define CanCmdTxPeriod   10     //CAN命令发送周期(与计数周期有关)

 
static byte taskstartTable[8]=
{
  PROCESS0,PROCESS1,PROCESS2,PROCESS3,
  PROCESS4,PROCESS5,PROCESS6,PROCESS7
};//此数组控制开始计数的时刻(保证为递增的)

static word taskperiodTable[8]=
{
  CanCmdTxPeriod,10,10,2,2,10,10,10
};//此数组控制任务执行的周期

//任务就绪掩码掩码
static byte startmaskTable[8]=
{
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};//此数组控制那些任务开始计数(不可更改)
static byte taskrdyTable[8]=
{
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};//此数组用以指示哪些任务就绪(不可更改)

/***********************************************************************
*  说明:  计算任务就绪状态变量的值，调用位置在PIT中断中
*         调度方式为周期性调度。可更改taskstartTable中的值
          来控制任务1至8的开始时刻，可通过更改taskperiodTable
          中的值来控制任务1至8的就绪周期。
*        
*  作者:  Azmat
*  日期:  2017.12.3
************************************************************************/
struct scheduleTable Sch; //任务就绪状态结构体
void rdyStateUpdate(void) 
{
   byte i; 
   static word Tik;
   static byte startState;
   //开始状态   
   if(Tik<=8)           //查询taskstartTable，控制任务开始时刻
   {
     for(i=0;i<8;i++)
     {
       if(Tik == taskstartTable[i])
         startState |= startmaskTable[i];  
     }
     Tik++;             //记满八个任务就不再开始其它任务了
   }
   //分别累加
   for(i=0;i<8;i++)     //根据任务的开始状态分别累加
   {
      if(startState&startmaskTable[i])
        Sch.rdytaskTik[i]++;
   }
   //计时更新就绪状态
   for(i=0;i<8;i++)     //根据任务的开始状态分别累加
   {
      if(Sch.rdytaskTik[i] >= taskperiodTable[i])
        Sch.rdystate |= taskrdyTable[i];
   } 
}


/***********************************************************************
*  说明:  处理就绪的任务，可直接将函数放在相应的就绪表内
*        
*  作者:  Azmat
*  日期:  2017.12.3
************************************************************************/

void schUpdate(void) 
{
  byte schedule;
  schedule = Sch.rdystate;  //读取就绪状态
  if(schedule & 0x01)  //周期发送CAN报文
  {
    //add you functions here
    CANMsg_Update();
    //Sch.rdytaskTik[0] = 0;由于CAN的发送中断存在故特殊对待
    Sch.rdystate &= ~(0x01); //清除就绪状态
  } //任务就绪
  if(schedule & 0x02)  //周期检测BUS_OFF状态
  {
    //add you functions here
    BusOff_Update();
    Sch.rdytaskTik[1] = 0;
    Sch.rdystate &= ~(0x02);
  }
  if(schedule & 0x04)
  {
    //add you functions here
    speed = readSpeed();  //读取转速
    adValue = atdChannel(1);  //读取ad值
    Sch.rdytaskTik[2] = 0;
    Sch.rdystate &= ~(0x04);
  }
  if(schedule & 0x08)
  {
    //add you functions here
    //adTarget = ccpCalBuffer[0]*256 + ccpCalBuffer[1];
   
    (byte)motorCtl(adTarget,adValue,30);   //换挡电机控制
    Sch.rdytaskTik[3] = 0;
    Sch.rdystate &= ~(0x08);
  }
  if(schedule & 0x10)
  {
    //add you functions here
    Sch.rdytaskTik[4] = 0;
    Sch.rdystate &= ~(0x10);
  }
  if(schedule & 0x20)
  {
    //add you functions here
    Sch.rdytaskTik[5] = 0;
    //Sch.rdystate &= ~(0x20);
  }
  if(schedule & 0x40)
  {
    //add you functions here
    Sch.rdytaskTik[6] = 0;
    Sch.rdystate &= ~(0x40);
  }
  if(schedule & 0x80)
  {
    //add you functions here
    (void)ccpBackground();       //ccp背景维护函数
    Sch.rdytaskTik[7] = 0;
    Sch.rdystate &= ~(0x80);
  }
  
}