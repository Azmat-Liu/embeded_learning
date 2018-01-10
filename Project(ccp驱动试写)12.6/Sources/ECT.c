#include "ECT.h"




struct IC_Parameters_Tag Pca;   //输入捕捉值储存 

void InitECT(void)
{
   PERT=0xff;           //使用拉电阻
   PPST=0x00;           //使用上拉电阻
   DDRT=0xfe;           //设置PORTT的方向寄存器
   
   TSCR2=0x87;          //设置分频因子为128 ,fECT=250KHZ,周期为4us,定时器溢出中断允许
   TIOS=0xfe;           //TC0、TC2设置为输入捕捉
   TCTL4=0x01;          //TC0、TC2上升沿触发
   TFLG1=0xff;	        // 清除各IC/OC中断标志位
   
   TFLG2_TOF=1;         //溢出标志位置0
   TIE=0x01;            //TC0、TC2中断允许
   TSCR1=0x80;          //TEN=1，标志位快速清除
   TCTL2_OM1=0;
   TCTL2_OL1=0;         //引脚1不对外输出
   CFORC_FOC1=1;        //强制输出比较
   OC7M_OC7M1=0;
   TTOV_TOV1=0;         //禁止溢出触发
}

/***********************************************************/
/*                   求平均转速函数                        */
/***********************************************************/
dword aveValue=0;
//dword Sum[5],Sum2;
word readSpeed(void) 
{
  byte i,j;
  word rtnValue;
  dword Max,Min;//,aveValue=0;
  static dword Sum[5],Sum2;  //此处需要单独为两者分配内存否则结果输出不正常(原因不明)
  if(Pca.IC0_Buffer[IC0_BUFFERSIZE] != 0)
  {
    for(i=0;i<3;i++)
    {
      Max = Pca.IC0_Buffer[6*i];    //必须在之前将MAX于MIN初始化，否则会遗传上一次的计数值，导致溢出
      Min = Pca.IC0_Buffer[6*i];
      for(j=0;j<6;j++)
      {
        Sum[i] += Pca.IC0_Buffer[6*i+j];
        if(Max <= Pca.IC0_Buffer[6*i+j])
          Max = Pca.IC0_Buffer[6*i+j];
        else if(Min >= Pca.IC0_Buffer[6*i+j])
          Min = Pca.IC0_Buffer[6*i+j];
      } 
      Sum2 += (Sum[i]-Max-Min)/4;
      Sum[i] = 0;  
    }
    aveValue = Sum2/3;
    rtnValue = (word)(15000000/(8*aveValue)); 
    Sum2 = 0;
  }else {
    rtnValue = 0;  
  }

  return (rtnValue);
}  
  
  
/***********************************************************/
/*                    ECT中断服务函数                      */
/***********************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED

  /*         TC0输入捕捉采集变速箱输出转速         */
  void interrupt 8  TC0_Capture(void)
  {
     static index=0;
     TFLG1_C0F = 1;
     Pca.IC0Counter = TC0;                          //获得当前IC0的计数值
     Pca.IC0 = Pca.IC0Counter + Pca.OverFlowCount*65536 - Pca.IC0LastCounter;       //用当前计数值减上个齿计数值得到计数值差
     if(Pca.IC0 >=250000)
        Pca.IC0 = 250000;
     if(Pca.IC0 <=250)
        Pca.IC0 = 250;
     Pca.OverFlowCount = 0;
     Pca.IC0_StopFlag = 0;
     Pca.IC0LastCounter = Pca.IC0Counter;     //当前计数值作为上个齿计数值保存，下次使用
     index++;                            //计数值数组序号自加，用于计算n个齿平均转速
     if(index >= IC0_BUFFERSIZE)                
        index = 0;                       //在这里计算n齿平均转速，记速到20后归零
     Pca.IC0_Buffer[index] = Pca.IC0;    //存储计数差到数组以计算平均转速
  }

  void interrupt 16 TimeOverFlow(void)      //溢出中断
  {
      byte i;
      TFLG2_TOF = 1;  //清标志
      Pca.OverFlowCount++;
      if(Pca.OverFlowCount >= 6)     //1.5s没有脉冲则储存375000
      {
        Pca.IC0_StopFlag = 1;
        for(i=0;i<IC0_BUFFERSIZE;i++)
          Pca.IC0_Buffer[i] = 250000;  
      }
  }

#pragma CODE_SEG DEFAULT

   
