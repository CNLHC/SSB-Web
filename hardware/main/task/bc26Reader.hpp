
#pragma once
#include "../bc26util.hpp"
#include <MapleFreeRTOS900.h>

extern BC26 *gBC26Obj;

static void ThBC26Reader(void *arg);

static void ThBC26Reader(void *arg)
{
  int FrameFSM = 0;
  int  endFSM = 0;
  char readBuf[200];
  char ch;
  int i = 0;
  TickType_t startCount;
  TickType_t currentCount;


  while (1)
  {
    if (Serial3.available())
    {
      // Serial1.println("------\n");
      // Serial1.println(ch);
      // Serial1.println(FrameFSM);
      // Serial1.println(endFSM);
      // Serial1.println("------\n");
      ch = Serial3.read();
      switch (FrameFSM){
      case 0: if (ch == 13) FrameFSM = 1; else FrameFSM = 0; break;
      case 1: if (ch == 13) FrameFSM = 1; else if (ch == 10) {FrameFSM = 2; startCount=xTaskGetTickCount();} else FrameFSM = 0; break;
      case 2:{
          readBuf[i++] = ch;
          currentCount = xTaskGetTickCount();
          if(currentCount<startCount)
            #ifdef configUSE_16_BIT_TICKS
              startCount+=UINT16_MAX;
            #else
              startCount+=UINT32_MAX;
            #endif

          if (endFSM==4||endFSM==11||endFSM==3||endFSM==10||i>200||(currentCount-startCount)>1000)
          {
            readBuf[i] = '\0';
            gBC26Obj->setResponse(readBuf);
            FrameFSM = 0;
            endFSM=0;
            i = 0;
          }
          break;
        }
      }
      switch (endFSM){
        case 0 :if(ch=='O') endFSM= 1; else if(ch=='E') endFSM=5; break; 
        case 1 :if(ch=='K') endFSM= 2; else endFSM=0; break;
        case 2 :if(ch==13)  endFSM= 3; else endFSM=0; break;
        case 3 :if(ch==10)  endFSM= 4; else endFSM=0; break;
        case 4 :endFSM=0;
        case 5 :if(ch=='R') endFSM= 6; else endFSM=0; break;
        case 6 :if(ch=='R') endFSM= 7; else endFSM=0; break;
        case 7 :if(ch=='O') endFSM= 8; else endFSM=0; break;
        case 8 :if(ch=='R') endFSM= 9; else endFSM=0; break;
        case 9 :if(ch==13)  endFSM=10; else endFSM=0; break;
        case 10:if(ch==10)  endFSM=11; else endFSM=0; break;
        case 11:endFSM=0;
      }
    }
    vTaskDelay(5);
  }
}