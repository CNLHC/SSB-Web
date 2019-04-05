
#include "../bc26util.hpp"

extern BC26 *gBC26Obj ;

static void ThBC26Reader(void * arg);

static void ThBC26Reader(void * arg){
  int FrameFSM=0;
  char readBuf[200];
  char ch;
  int i=0;
  while(1){
    if(Serial3.available()){
      ch=Serial3.read();
      switch (FrameFSM)
      {
        case 0:
          if (ch==13)
            FrameFSM=1;
          else
            FrameFSM=0;
          break;
        case 1:
          if (ch==13)
            FrameFSM=1;
          else if(ch==10)
            FrameFSM=2;
          else
            FrameFSM=0;
          break;
        case 2:
          if (ch==13)
            FrameFSM=3;
          else
            readBuf[i++] = ch;
          break;
        case 3:
          if (ch==10){
            readBuf[i] = '\0';
            gBC26Obj->releaseLock(readBuf);
            FrameFSM=0;
          }
          else
            FrameFSM=0;
          break;
      }
    }
  }
}