#include "SCI.h"


#define BUS_CLOCK 32000000 
#define BAUD      9600 



void InitSCI0(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //设置SCI0波特率为9600
  SCI0CR1 = 0x00;               //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI0CR2 = 0x2c;               //允许发送数据，允许接收中断功能
}

static void sendSCI0(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;
} 


static byte receiveSCI0(void) 
{
  while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
  return(SCI0DRL);
}


void printk(char *str) 
{
  DisableInterrupts;
  while(*str != '\0')
      sendSCI0(*str++);
  EnableInterrupts;
}

/***********************************************************/
/*                     串口通讯接收中断                    */
/***********************************************************/
byte SCI0receivebuff[33];
#pragma CODE_SEG __NEAR_SEG NON_BANKED

  interrupt void receive_data(void)    //串口接收
  {
      unsigned char i;
      for(i=0;i<33;i++)          
        SCI0receivebuff[i] = receiveSCI0(); 
      //sciCommand(); 
  }


 #pragma CODE_SEG DEFAULT
 
 void sciCommand(void)
 {
    ;  //sci命令编写
 }





