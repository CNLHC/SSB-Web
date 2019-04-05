#include "CRC.h"
#include <SPI.h>
#include <MFRC522.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>


#define SS_PIN PA4  // CS Pin
#define RST_PIN PA3 // Reset Pin
#define CARTID "000000"
#define START "00000000"
#define SEND "00000001"
#define DELETE "00000011"
#define END "FFFFFFFF" //COMMAND
#define LINK "01010101"
#define DATA "000000"
// HardwareSerial Serial2(PA3,PA2);
// HardwareSerial Serial3(PB11,PB10);

#if defined(_BOARD_GENERIC_STM32F103C_H_)
#define MAX_DISPAY_BUFFER_SIZE 15000ul // ~15k is a good compromise
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_213, MAX_HEIGHT(GxEPD2_213)> display(GxEPD2_213(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
#endif
#include "bitmaps/Bitmaps128x250.h" // 2.13" b/w


unsigned char CRC8(unsigned char *p, char counter);

String rx_buffer = "";
int netConnected = 0;
int serverConnected = 0;
int firstConnect = 1;
bool startPressed = 0;
bool deletePressed = 0;
bool endPressed = 0;
bool started = 0;
int counter = 0;
long link_counter = 0;

char *str;
byte readCard[4] = {123, 123, 123, 123}; // Stores scanned ID read from RFID Module
uint8_t successRead;    // Variable integer to keep if we have Successful Read from Reader
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.






//////////////////////// CRC8 ///////////////////////

unsigned char CRC8(unsigned char *p, char counter) {
  unsigned char crc8 = 0;
  for (; counter > 0; counter--)
  {
    crc8 = crc_array[crc8 ^ *p]; //Generate CRC Code from Table
    p++;
  }
  return crc8;
}




///////////////////RxFind//////////////////////

char RxFind(const char* target, int a) {
//Find Keyword in Serial Response
  while (!Serial3.available());
  while (Serial3.available())
    {
      rx_buffer = Serial3.readString();
    }
    Serial1.println(String("") + "Received:" + rx_buffer);
    Serial1.println("---END---");
    // const char *p = rx_buffer.c_str();
  char *str1 = strstr(rx_buffer.c_str(), target);  //Position of the Keyword
  return str1[a];
}

////////////////ServerState////////////////////
int ServerState(){
//Return Sever State: 1-Connecting  2-Connected 3-Closed
  rx_buffer = "NULL";
  Serial3.println("AT+QISTATE=0,1"); 
  char find = RxFind("3001", 5);
  // Serial1.println(String("") + "RE:" + find[0] + find[1] + find[2] + find[3] + find[4] + find[5] + find[6]);
  Serial1.println(String("") + find);
  switch (find)
      {
        case '2':
          return 2;
          break;

        case '1':{
          delay(5000);  //Retry every 5 sec
          return ServerState();
          break;
        }

        case '3':
          return 3;
          break;

        default:{
          delay(10000);  //Retry every 10 sec
          return ServerState();
          Serial1.println("State Error");
        }
          break;
      }
}

void sendData(int mode) { 
//Send Package
////////////////Package Generate//////////////////////
  String UID = "";
  String cmd = "";
  for(int i = 0; i < 4; i++){
    UID.concat(String(readCard[i], HEX));
  }
  UID.toUpperCase();    //Get UID
  cmd.concat(UID);
  cmd.concat(CARTID);
//   if(mode==0)   //Scan UID and Send Package to Server
//     cmd.concat(SEND);
//   else if(mode==1)
//     cmd.concat(START);      //Start Shopping
//   else if (mode==2)
//     cmd.concat(DELETE);     //Delete Item


  switch(mode){
      case 0:   cmd.concat(START); break;   //Start Shopping
      case 1:   cmd.concat(SEND); break;    //Scan UID and Send Package to Server
      case 2:   cmd.concat(DELETE); break;  //Delete Item
      case 3:   cmd.concat(END); break;     //Shopping Ends
      case 4:   cmd.concat(LINK); break;    //Link Test
  }

  cmd.concat(DATA);     //CMD=UID+CARTID+COMMAND+DATA=88bit

  unsigned char package[24]={0};
  char temp[30];
  cmd.toCharArray(temp, 30);
  for(int i = 0; i < 22; i++){
    package[i]=(unsigned char)temp[i]; 
  }
  
  Serial1.println("Package:" + String((const char *)&package));

  unsigned char crcResult;
  crcResult = CRC8(package, 22);                                           //CRC-8/MAXIM
  

  Serial1.println(String("") + "CRC:" + crcResult);
  String result = "";
  if(crcResult <= 16) 
    result = String((const char *)&package) + "0" + String(crcResult, HEX); //Result=UID+CARTID+COMMAND+DATA+CRC=96bit
  else
    result = String((const char *)&package) + String(crcResult, HEX);
  Serial1.println(String("") + "Result:" + result);
  result.toUpperCase();
  result.toCharArray(temp, 30);

//   Serial1.println(String("") + "temp:" + temp[22] + temp[23]);

  String final = ""; //Convert to HEX ASCII
  for (int i = 0; i < 24; i++)
  {
    final.concat((temp[i] >= '0' && temp[i] <= '9') ? (temp[i] - '0') + 30 : (temp[i] >= 'A' && temp[i] <= 'F') ? (temp[i] - 'A') + 41 : (temp[i] >= 'a' && temp[i] <= 'f') ? (temp[i] - 'a') + 41 : 0);
  }
  delay(300);
  Serial1.println("Sending:" + final);

//////////////////////Server Connect///////////////////
  while (!serverConnected)
    {
    int state = 0;

    if(firstConnect) {
      Serial1.println(String("") + "Server State:" + serverConnected);
      Serial3.println("AT+QIOPEN=1,1,\"TCP\",\"39.105.151.150\",2334,3001,1,0"); //Open TCP Socket
      delay(300);
      firstConnect = 0;
    }
    state = ServerState();
    
    if (state == 2){
      delay(300);
      serverConnected = 1;
      Serial1.println("Server Connected!");
    }
    else if(state == 3){
      delay(1000);
      Serial3.println("AT+QICLOSE=1");
      Serial1.println("Server Disconnected! Retry...");
      firstConnect = 1;
    }

    Serial1.println(String("") + "Server State:" + serverConnected);
    delay(800);
    }

////////////////////Sending/////////////////////////
  while (serverConnected)
  {
    Serial1.println("Sending:" + final);
    Serial3.println("AT+QISENDEX=1,24," + final);
    /*Response Check...

    */

    serverConnected = 0;  //Test Server Connection before Sending

  }

  Serial1.println("Package Sent!");
  delay(3000);
}

////////////////Show Reader Detials///////////////
void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial1.print(F("MFRC522 Software Version: 0x"));
  Serial1.print(v, HEX);
  if (v == 0x91)
    Serial1.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial1.print(F(" = v2.0"));
  else
    Serial1.print(F(" (unknown)"));
  Serial1.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
  if ((v == 0x00) || (v == 0xFF)) {
    Serial1.println(F("WARNING: Communication failure"));
    Serial1.println(F("SYSTEM HALTED: Check connections."));
    // Visualize system is halted
    while (true); // Do not go further
  }
}

////////////////Get UID//////////////
uint8_t getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  Serial.println(F("Scanned PICC's UID:"));
  for ( uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
  }
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

const char E_START[] = "START!";

void EPAPER_START()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + tbh) / 2; // y is base line!
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(E_START);
  }
  while (display.nextPage());
}
//////////////////////////////////////////////////


void setup() {
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB8, INPUT_PULLUP);

  
////////////////BC26 Initializaion///////////////
  Serial1.begin(115200, SERIAL_8N1);
  Serial1.println("Start!");
  Serial3.begin(115200);
  delay(5000);  //Waiting for SIM Card Registration

  Serial3.println("AT\r\n");  //Auto Baud Rate Synchronization
  while (Serial3.available()) {
    char ch;
    ch = Serial3.read();
    Serial1.print(ch);
  } //Get response: AT OK

  while (!Serial3.available()); //Wait for Response

  Serial1.println("Baud Rate Synchronized!");
  delay(1000);

  Serial3.println("ATE0\r\n");  //Echo Disabled
  while (Serial3.available()) {
    char ch;
    ch = Serial3.read();
    Serial1.println(ch);
  } //Get response: OK

  Serial1.println("Echo Disabled!\r\n");
  delay(500);

  while (!netConnected) //Connecting with IoT Network
  {
    Serial3.println("AT+CGATT?\r\n");
    while (Serial3.available())
      rx_buffer = Serial3.readString();

    const char *p = rx_buffer.c_str();
    delay(500); //Get response: +CGATT:1
    char *str1 = strstr(p, (const char*)"+CGATT: 1");
//    char *str1 = strstr(p, (const char*)"+CGATT");
    if (str1 == NULL){
      netConnected=0;
      Serial1.println(String("") + str1[0] + str1[1]+ str1[2]+ str1[3]+ str1[4]+ str1[5]+"6:"+ str1[6]+"7:"+ str1[7]+ "8:"+str1[8]+ "!");
    }
    else {
      netConnected = 1;
    Serial1.println(String("") + str1[0] + str1[1]+ str1[2]+ str1[3]+ str1[4]+ str1[5]+"6:"+ str1[6]+"7:"+ str1[7]+ "8:"+str1[8]+ "!");
    }
    rx_buffer = "";
    delay(500);
  }
  delay(500);
  Serial1.println("Net Connected!");

//while (!netConnected) //Connecting with IoT Network
//  {
//    Serial3.println("AT+CGATT?\r\n");
//    while (Serial3.available())
//      rx_buffer = Serial3.readString();
//
//    const char *p = rx_buffer.c_str();
//    Serial1.println(String("") + "Net State:" + netConnected);
//    delay(1000); //Get response: +CGATT:1
//    char *str1 = strstr(p, "1");
//    if (str1[0] == '1'){
//      netConnected=1;
//      Serial1.println(String("") + "Net State:" + netConnected);
//    }
//    rx_buffer = "";
//  }
//  delay(1000);
//  Serial1.println("Net Connected!");

////////////////MFRC522 Initializaion///////////////
  SPI.begin();  // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  ShowReaderDetails();  //Check Version
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max); //Set Antenna Gain to 48 dB
  Serial1.println("RFID Reader Ready");
  Serial1.println();


/////////////E-Paper/////////////////
//  Serial1.println();
//  Serial1.println("E-paper setup");
//  delay(100);
//  display.init(115200);
}


void handler_button() {
    int startVal = digitalRead(PB6);
    int deleteVal = digitalRead(PB7);
    int endVal = digitalRead(PB8);

    if(startVal && deleteVal && endVal == 1) {
        counter = 0;
        startPressed=0;
        deletePressed=0;
        endPressed=0;
    }   //All Keys Released
        

    
    else if(startVal == LOW) {
        counter++;
        if(counter==2) {
            startPressed=1;
            counter=0;
        }
    }
    else if(deleteVal == LOW) {
        counter++;
        if(counter==2) {
            deletePressed=1;
            counter=0;
        }
    }
    else if(endVal == LOW) {
        counter++;
        if(counter==2) {
            endPressed=1;
            counter=0;
        }
    }
}


////////////////////////////////////////

void loop() {
    handler_button();
//    Serial1.println(String("") + "startPressed"+ startPressed + "/" + link_counter);
    link_counter++;
    if(link_counter==1000) {
    sendData(4);
    link_counter = 0;
    }
    
    if(startPressed == 1 && started == 0) {
//        EPAPER_START();
        sendData(0);
        startPressed = 0; 
        started = 1;  
        
    }
    if(started == 1 && deletePressed == 0) {
        if(getID())  //Scan UID
          sendData(1);
    }
    if(started == 1 && deletePressed == 1) {
        if(getID())  //Scan UID
        {
            sendData(2);
            deletePressed = 0;
        }

    }
    if(started == 1 && endPressed == 1) {
//        display.init(115200);
        started = 0;
        sendData(3);
        endPressed = 0;
        
    }
}
