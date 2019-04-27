
#include <MFRC522.h>
#include <SPI.h>
extern  MFRC522   gMFRC522Obj;
void hardwareinit(){
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB8, INPUT_PULLUP);
  SPI.begin();  
  Serial1.begin(115200, SERIAL_8N1);
  Serial1.println("Serial1 Start");
  Serial1.println("Serial1 Start");
  Serial1.println("Serial1 Start");
  Serial3.begin(115200);
  Serial1.println("RFID Reader Ready");
  gMFRC522Obj.PCD_Init(); 
  gMFRC522Obj.PCD_SetAntennaGain(gMFRC522Obj.RxGain_max); 
}


