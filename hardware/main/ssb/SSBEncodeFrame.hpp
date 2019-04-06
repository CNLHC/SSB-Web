#pragma once
#include "./CRC.hpp"

#define SSB_CARTID "000000"
#define SSB_START "00000000"
#define SSB_SEND "00000001"
#define SSB_DELETE "00000011"
#define SSB_END "FFFFFFFF" //COMMAND
#define SSB_LINK "01010101"
#define SSB_DATA "000000"

String SSBEncodeFrame(int opCode, uint32_t RFID){
  String UID = "";
  String cmd = "";
  String final = ""; 
  String result = "";
  unsigned char crcResult;
  unsigned char package[24]={0};
  char temp[30];
  for(int i = 0; i < 4; i++)
    UID.concat(String((uint8_t)((RFID>>i*8)&0x000000FF), HEX));
  UID.toUpperCase();    
  cmd.concat(UID);
  cmd.concat(SSB_CARTID);
  switch(opCode){
      case 0:   cmd.concat(SSB_START); break;   //Start Shopping
      case 1:   cmd.concat(SSB_SEND); break;    //Scan UID and Send Package to Server
      case 2:   cmd.concat(SSB_DELETE); break;  //Delete Item
      case 3:   cmd.concat(SSB_END); break;     //Shopping Ends
      case 4:   cmd.concat(SSB_LINK); break;    //SSB_Link Test
  }
  cmd.concat(SSB_DATA);     //CMD=UID+SSB_CARTID+COMMAND+SSB_DATA=88bit
  cmd.toCharArray(temp, 30);
  for(int i = 0; i < 22; i++)package[i]=(unsigned char)temp[i]; 
  crcResult = CRC8(package, 22);                                           //CRC-8/MAXIM
  if(crcResult <= 16) 
    result = String((const char *)&package) + "0" + String(crcResult, HEX); //Result=UID+SSB_CARTID+COMMAND+SSB_DATA+CRC=96bit
  else
    result = String((const char *)&package) + String(crcResult, HEX);
  result.toUpperCase();
  result.toCharArray(temp, 30);
  for (int i = 0; i < 24; i++)final.concat((temp[i] >= '0' && temp[i] <= '9') ? (temp[i] - '0') + 30 : (temp[i] >= 'A' && temp[i] <= 'F') ? (temp[i] - 'A') + 41 : (temp[i] >= 'a' && temp[i] <= 'f') ? (temp[i] - 'a') + 41 : 0);
  return final;
}