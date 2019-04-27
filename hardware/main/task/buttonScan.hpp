
extern int globalFSM ;
static void ThButtonScan(void* arg);
static void ThButtonScan(void* arg) {
  while (1) {
      switch (globalFSM) {
      case 0: break;
      case 1: if(!digitalRead(PB6))
          globalFSM=2;
      case 2: if(!digitalRead(PB8))
          globalFSM=1;
      }
    vTaskDelay(50);
  }
}