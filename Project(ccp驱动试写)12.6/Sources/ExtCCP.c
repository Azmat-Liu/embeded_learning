#include "includes.h"

/*************************************************************************
*  说明:  以下为:ccp驱动的扩展函数
*         移植ccp驱动时需要基于不同的设计方案修改此扩展函数
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/



/*************************************************************************
*  说明:  ccp总中断关闭和使能
*         分层次使能中断，即每关闭一次中断需要开启一次，否则中断开启无效
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/
CCP_BYTE disable_interrupt_count = 0;
void ccpDisableInterrupts(void) 
{
  _asm("SEI");                          // set I-Bit
  disable_interrupt_count++;            // incr. counter
}

void ccpEnableInterrupts(void) 
{
  if (--disable_interrupt_count==0) {   // if interrupts only one time disabled
    _asm("CLI");                        // enable them
  }
}

/*************************************************************************
*  说明:  ccp获取MTA指针
*        
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/
/*获取全局地址的指针*/       
CCP_MTABYTEPTR ccpGetPointer( CCP_BYTE addr_ext, CCP_DWORD addr )
{ 
  addr_ext=0;  //拓展地址位，暂时无用       
  return (CCP_MTABYTEPTR) addr;
}

/*************************************************************************
*  说明:  ccp获取解锁函数
*        
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/
/*获取seed*/
CCP_DWORD ccpGetSeed( CCP_BYTE resourceMask )  //获取种子
{
  CCP_DWORD seed;
  switch(resourceMask)
  {
    case PL_CAL:  seed=PL_CAL_SEED;  break;
    case PL_PGM:  seed=PL_PGM_SEED;  break;
    case PL_DAQ:  seed=PL_DAQ_SEED;  break;
    default:
      break;
  }
  return (CCP_DWORD) seed; 
}
/*分析密钥序列,解锁相应功能*/
CCP_BYTE ccpUnlock( CCP_BYTE *key )       
{
  CCP_BYTE ProtectionStatus=0;
  CCP_BYTE i,KeyTable[6];
  CCP_DWORD KEY;      //解算出的密钥序列
  for(i=0;i<6;i++)    //取密钥序列
    KeyTable[i] = *((CCP_BYTE *)key+i);
  KEY = *((dword *)&KeyTable[0]);    
  //KEY *= 3;
  KEY &= 0xaa5a5aaa;
  //KEY /= 5;
  switch(KEY)
  {
    case PL_CAL_SEED:  ProtectionStatus=PL_CAL;  break;   //获取的权限
    case PL_PGM_SEED:  ProtectionStatus=PL_PGM;  break;
    case PL_DAQ_SEED:  ProtectionStatus=PL_DAQ;  break;
    default:
      break;
  } 
  return ProtectionStatus;
}

/*************************************************************************
*  说明:  ccp标定数据写入DFlash相关函数
*        
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/

byte ccpCalBuffer[256]@0x3C00={1,2,3,4,5,6,7,8,9};       //定义ccp标定的Buffer共256个字节
byte ccpPROGRAMBuffer[256]={0};  //定义ccp程序刷新Buffer共1024个字节
byte ccpCalPage=0;                //定义ccp标定页(对应扇区号)
//标定RAM的空间起始位置
#define CCP_CAL_RAM_START ((CCP_DWORD)((CCP_MTABYTEPTR)&ccpCalBuffer[0]))    
#define CCP_CAL_RAM_END   (CCP_CAL_RAM_START+256)
/*检验标定地址是否超出范围*/
CCP_BYTE ccpCheckWriteAccess( CCP_MTABYTEPTR a, CCP_BYTE s )
{
  CCP_DWORD address;
  address = (CCP_DWORD)a;
  if (address>CCP_CAL_RAM_START || (address+s)<CCP_CAL_RAM_END) 
  {
    return (TRUE);   //允许写  
  } 
  else
    return (FALSE); //不允许写
}
/*将Buffer中的数据写入DFlash中*/
void cppCheckWriteDFlash(void)  
{ 
  byte i,calPage;                                        
  //字节数大于256时由标定页来控制擦写地址
  DFlash_EraseSector(ccpCalPage);              //擦除扇区
  for(calPage=0;calPage<=ccpCalPage;calPage++) //根据总标定页数来擦写扇区
  {
    for(i=0;i<32;i++)                          //写整个扇区
    {
      DFlash_WriteBlock(calPage,i,
                        *(word *)&ccpCalBuffer[256*calPage+8*i],
                        *(word *)&ccpCalBuffer[256*calPage+8*i+2],
                        *(word *)&ccpCalBuffer[256*calPage+8*i+4],
                        *(word *)&ccpCalBuffer[256*calPage+8*i+6]
                        );  
    }
  }
}
/*************************************************************************
*  说明:  ccp标定页设置相关函数
*        
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/

void ccpInitCalPage( void )         //初始化标定页
{
  ccpCalPage=0;  
}

void ccpSetCalPage( CCP_DWORD a )  //设置标定页(从0开始往上加)
{
  if(a>CCP_CAL_RAM_START)
    ccpCalPage = (a-CCP_CAL_RAM_START)%256;
}

CCP_DWORD ccpGetCalPage( void )   //获取使用的标定页
{
  return (CCP_DWORD)(ccpCalPage*256+CCP_CAL_RAM_START);     
}


/*************************************************************************
*  说明:  ccp发送函数(与CAN.c关系密切)
*        
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/

/*发送CRM或DTM*/
void ccpSend( CCP_BYTEPTR msg )
{
  byte i;
  msg_send.id = CCP_DTO_ID; /* CAN identifier ECU -> Master */
  for(i=0;i<8;i++)
    msg_send.data[i] = *(msg+i);
  
  msg_send.len = CAN_DLC;
  msg_send.RTR = FALSE;
  msg_send.prty = 0;
  //发送CRM/DTM
  if( MSCAN0SendMsg(msg_send) != CanTxOK )
    ccp.SendStatus |= CCP_TX_PENDING;
  else
    ccp.SendStatus &= ~CCP_TX_PENDING;
}

/*获取MTA[0]指针的全局地址(目前无作用)*/
void ccpGetMTA0( CCP_BYTE *e, CCP_DWORD *a)   
{
  *e = 0;                      //地址扩展为0(与ccpGetPointer需要对应)
  *a = (CCP_DWORD)ccp.MTA[0];  //返回ccp.MTA[0]的地址
}




/*************************************************************************
*  说明:  ccp后台运行任务管理
*        
*  作者:  Azmat
*  日期:  2017.9.22
**************************************************************************/

/*用户定义的CCPBackground*/
byte Stamp1,Stamp2;
void ccpUserBackground(void)
{
  if(ccp.SendStatus & CCP_TX_PENDING)  //若CCP发送被挂起，则重新发送
  {
    if( MSCAN0SendMsg(msg_send) == CanTxOK )
    {
      ccp.SendStatus &= ~CCP_TX_PENDING;
    }
    else
    {
      //需要考虑发送成功后会不会多次发送的问题,谨慎考虑
      ccpSendCrm();   //发送被挂起的Crm(即当发送被挂起时,CCP发送状态变为CCP_CRM_REQUEST,在ccpSendCallBack函数中重新发送)
      ccpSendDtm();   //同理
    }
  }
  
  ccpDaq(1);  //Daq

  if(ccp.UserSessionStatus&SS_CAL)  //若用户会话状态变为标定状态则开始标定
  {
    cppCheckWriteDFlash();  //擦写标定数据入DFlash
    memorycopy(ccpCalBuffer,&Trans,sizeof(Trans)); //将Buffer中的数据写入Trans
    ccp.UserSessionStatus &= ~SS_CAL; //清除标志 
  }
}





