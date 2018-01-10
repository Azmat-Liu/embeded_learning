#include "includes.h"
#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

  struct scheduleTable 
  {
	 byte rdystate;      //指示任务就绪状态
	 word rdytaskTik[8]; //任务计时
  };
  extern struct scheduleTable Sch;
  
  extern void schUpdate(void);
  extern void rdyStateUpdate(void);
  
#endif 