#include <MFRC522.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "ssb/SSBEPaper.hpp"

extern  U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
extern  MFRC522   gMFRC522Obj;
extern  GxEPD2_BW<GxEPD2_213, MAX_HEIGHT(GxEPD2_213)> display;

void hardwareinit(){
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB8, INPUT_PULLUP);
  SPI.begin();  
  Serial1.begin(115200, SERIAL_8N1);
  Serial1.println("Serial1 Start");
  Serial3.begin(115200);
  Serial1.println("RFID Reader Ready");
  gMFRC522Obj.PCD_Init(); 
  gMFRC522Obj.PCD_SetAntennaGain(gMFRC522Obj.RxGain_max); 

  display.init(115200);
  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX
  EPaperStart();
}


