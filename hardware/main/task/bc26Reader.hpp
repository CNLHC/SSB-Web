
#pragma once
#include "../bc26util.hpp"
#include "../util/streamDetector.hpp"
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
  streamPatternDetector detectorOK("OK\r");
  streamPatternDetector detectorError("ERROR\r");
  streamPatternDetector detectorIURC("+QIURC");


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
      detectorOK.feed(ch);
      detectorError.feed(ch);
      detectorIURC.feed(ch);

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
          if(detectorIURC.getHitTimes()>0){
            FrameFSM = 0;
            endFSM=0;
            i = 0;
            detectorOK.reset();
            detectorError.reset();
            detectorIURC.reset();
          }
          else if (detectorOK.getHitTimes()>0   ||
              detectorError.getHitTimes()>0||
              i>200                      ||
              (currentCount-startCount)>1000){
            readBuf[i] = '\0';
            gBC26Obj->setResponse(readBuf);
            FrameFSM = 0;
            endFSM=0;
            i = 0;
            detectorOK.reset();
            detectorError.reset();
          }
          break;
        }
      }
    }
    vTaskDelay(5);
  }
}