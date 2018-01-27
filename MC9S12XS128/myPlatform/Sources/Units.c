#include "Units.h"


/**********************************************************************
*  说明:  用户自行编写不易分类的函数集合
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/
word ccptest;
word speed;
word adValue;
word adVoltage;
word adTarget;


//*内存拷贝函数
void memorycopy(byte *from,byte *to,word len)
{
  word i;
  for(i=0;i<len;i++)
     *to++ = *from++; 
}

//*初始化ccpBuffer(从DFlash中读取)
struct Transmission_Tags Trans;
void DFlashmemorycopy(dword from,byte *to,word len)
{
  word i;
  word check;
  check = *(volatile unsigned int *__far)from;
  if(check != 0xffff) {                         //检测DFlash是否被写过
      for(i=0;i<len;i++) {
        *to++ = *(volatile unsigned char *__far)from++; 
        _FEED_COP();
    }
  }
  memorycopy(ccpCalBuffer,(byte *)&Trans,sizeof(Trans)); //将Buffer中的数据写入Trans
}



/**********************************************************************
*  说明:  串口命令解析函数,与SCI中断存在耦合，无法避免
*        
*  作者:  Azmat
*  日期:  2017.12.22
***********************************************************************/
//extern byte sciCmd[16];
void sciCmd_Decode(void)
 {
   //int sci_p,sci_i;
   //adTarget = sciCmd[1]*256+sciCmd[2];
   //sci_p = (int)sciCmd[3];
   //sci_i = (int)sciCmd[4];
   //pidSetPara(sci_p,sci_p,0,0,0,-600,600);
 }



/**********************************************************************
*  说明:  工况判断函数
*        
*  作者:  Azmat
*  日期:  2017.12.22
***********************************************************************/

int m_speed,m_torque,m_mode,m_brake;
int state;

const int Gear1_DefaTorqTab[25]={
		6400,6400,6400,6400,6400,6400,6400,6400,6400,6400,
		6400,6400,6400,6400,6400,6400,6400,6400,6400,6400,
		6400,6400,6400,6400,6400
};//3000-8000
const int Gear1_TorqLimitTab[25]={
		100,100,100,100,100,100,100,100,100,100,
		100,100,100,100,100,100,100,100,100,100,
		100,100,100,100,100
};//3000-8000
const int Gear2_DefaTorqTab[25]={
		6400,6400,6400,6400,6400,6400,6400,6400,6400,6400,
		6400,6400,6400,6400,6400,6400,6400,6400,6400,6400,
		6400,6400,6400,6400,6400
};//0-5000
const int Gear2_TorqLimitTab[25]={
		100,100,100,100,100,100,100,100,100,100,
		100,100,100,100,100,100,100,100,100,100,
		100,100,100,100,100
};//0-5000
int getTorqFromTab(int var,const int * tab,int offset)
{
	int p_at,rtn;
	p_at = (var - offset + 100)/200;
	rtn = *(tab+p_at);
	return rtn;
}
void stateCheck(void)
{
	if(GEAR1){    //&& SOC >30 && FORWARD
		if(m_speed >= Trans.mspeed_up && 
		m_torque - getTorqFromTab(m_speed,Gear1_DefaTorqTab,3000) <= 
		getTorqFromTab(m_speed,Gear1_TorqLimitTab,3000))
			state=1;
	}
	if(GEAR2){
		if(m_speed <= Trans.mspeed_dn && 
		m_torque - getTorqFromTab(m_speed,Gear2_DefaTorqTab,0) <= 
		getTorqFromTab(m_speed,Gear2_TorqLimitTab,0))
			state=4;
		if(m_speed <= Trans.mspeed_dnlimit)
			state=5;
	}
	if(GEAR0){
		;//check_t(a);
	}

}





