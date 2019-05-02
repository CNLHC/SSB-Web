//
// Created by cn on 2019/5/2.
//

#include "../inc/UM2xx.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace um2xx;

UM2xxFrame UM2xx::encodeFrame(um2xx::opcode code, uint8_t *data,
                              uint16_t datasize) {

  // since c++ 11, return  locally  created  vector will be as efficient as
  // return point. just do it!
  UM2xxFrame out;
  // Frame head
  out.push_back(0xA5);
  out.push_back(0x5A);

  uint16_t frameSize = getFrameSize(datasize);

  out.push_back((uint8_t)(frameSize >> 8));
  out.push_back((uint8_t)(frameSize));

  out.push_back(code);

  for (int i = 0; i < datasize; i++)
    out.push_back(data[i]);

  out.push_back(getFrameCRC(code, data, datasize));
  out.push_back(0x0D);
  out.push_back(0x0A);
  return out;
}
uint16_t UM2xx::getFrameSize(uint16_t datasize) {
  return 2 + 2 + 1 + datasize + 1 + 2;
}
uint16_t UM2xx::getDataSize(uint16_t frameSize) {
  return frameSize - 2 - 2 - 1 - 1 - 2;
}
uint8_t UM2xx::getFrameCRC(opcode code, uint8_t *data, uint16_t datasize) {
  int frameSize = getFrameSize(datasize);
  uint8_t frameMSB = (uint8_t)(frameSize >> 8);
  uint8_t frameLSB = (uint8_t)frameSize;
  uint8_t cumu = frameMSB;
  cumu ^= frameLSB;
  cumu ^= code;
  for (int i = 0; i < datasize; i++)
    cumu ^= data[i];
  return cumu;
}
void UM2xx::connect(const std::string &port) {
  if (mSerial != nullptr) {
    return;
  } else {
    mSerial =
        new serial::Serial(port, 115200, serial::Timeout::simpleTimeout(300));
  }
  mSerial->setBytesize(serial::eightbits);
  mSerial->setStopbits(serial::stopbits_one);
  mSerial->setFlowcontrol(serial::flowcontrol_none);
  mSerial->setParity(serial::parity_none);
  if (mSerial->isOpen())
    std::cout << "Connect Successfully at: " << port << std::endl;
  else {
    std::cout << "Connect Failed " << std::endl;
    delete mSerial;
    mSerial = nullptr;
  }
}
bool UM2xx::isFrameAvailable(um2xx::UM2xxFrame &frame) {
  if(frame.size()<5)
    return false;

  if (!(frame[0] == 0xa5 && frame[1] == 0x5a))
    return false;
  uint16_t frameSize = ((uint16_t)frame[2] << 8) + frame[3];
  if (frame.size() != frameSize)
    return false;
  if (!(frame[frameSize - 2] == 0x0D && frame[frameSize - 1] == 0x0A))
    return false;

  return true;
}
UM2xxData UM2xx::parseDataFromFrame(um2xx::UM2xxFrame &frame) {
  if (!isFrameAvailable(frame)) {
    std::cerr << "frame format error!:" ;
    std::cerr<< DataToHexString(frame)<< std::endl;;
    UM2xxData empty;
    return empty;
  }
  uint16_t dataSize = getDataSize(frame.size());
  UM2xxData data(frame.begin() + 5, frame.begin() + 5 + dataSize);
  return data;
}

std::string UM2xx::DataToHexString(um2xx::UM2xxData &data) {
  std::ostringstream ss;
  ss << std::hex << std::uppercase << std::setfill( '0' );
  std::for_each( data.cbegin(), data.cend(), [&]( int c ) { ss << std::setw( 2 ) << c; } );
  return ss.str();
}


