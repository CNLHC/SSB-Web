
static void ThBC26Reader(void * arg);

static void ThBC26Reader(void * arg){
  while(1){
    int FrameFSM=0;
    while(Serial3.available()){
      char ch;
      ch=Serial3.read();
    }
  }
}