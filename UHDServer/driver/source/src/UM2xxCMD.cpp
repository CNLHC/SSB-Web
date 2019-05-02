//
// Created by cn on 2019/5/2.
//

#include "../inc/UM2xx.h"
#include <bits/unordered_set.h>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace um2xx;
UM2xxData UM2xx::CMDGetHarwareInfo() {
  return CMDSimpleGet(OP_GET_HARDWARE_VERSION);
}
UM2xxData UM2xx::CMDSimpleGet(um2xx::opcode code) {
  if (!isConnected()) {
    std::cerr << "Not Connected" << std::endl;
    return DataEmpty;
  }
  auto frame = encodeFrame(code, nullptr, 0);
  mSerial->setTimeout(serial::Timeout::max(), 5, 0, 250, 0);
  mSerial->write(frame);
  UM2xxFrame response = readFrame(100);
  return parseDataFromFrame(response);
}

UM2xxData UM2xx::CMDFindTagSingle(uint16_t timeout) {
  if (!isConnected()) {
    std::cerr << "Not Connected" << std::endl;
    return DataEmpty;
  }
  um2xx::UM2xx a;
  uint8_t payload[2] = {(uint8_t)(timeout >> 8), (uint8_t)timeout};
  auto frame = encodeFrame(OP_FIND_TAG_SIGNLE, payload, 2);
  mSerial->setTimeout(serial::Timeout::max(), timeout, 0, 250, 0);
  mSerial->write(frame);
  UM2xxFrame response = readFrame(100);
  return parseDataFromFrame(response);
}

std::unordered_map<std::string, int> UM2xx::CMDFindTags(uint16_t MaxTimes) {
  std::unordered_map<std::string, int> TagDataList;

  if (!isConnected()) {
    std::cerr << "Not Connected" << std::endl;
    return TagDataList;
  }
  um2xx::UM2xx a;
  uint8_t payload[2] = {(uint8_t)(MaxTimes >> 8), (uint8_t)MaxTimes};
  auto frame = encodeFrame(OP_FIND_TAGS_MULTI, payload, 2);

  // start
  mSerial->setTimeout(serial::Timeout::max(), 3000, 0, 250, 0);
  mSerial->write(frame);

  // define thread
  typedef std::chrono::steady_clock Clock;
  auto t0 = Clock::now();
  auto t1 = t0 + std::chrono::seconds(5);
  bool timeToQuit = false;

  auto ThreadWorker = [&]() {
    auto twT1 = Clock::now() + std::chrono::seconds(2);
    while (Clock::now() < twT1 && !timeToQuit) {
      UM2xxData frameRes = readFrame(100);
      auto data = parseDataFromFrame(frameRes);
      auto ECR = dataToECR(data);
      auto ECRHexStr = DataToHexString(ECR);
      if (ECRHexStr.size() < 10)
        continue; // may be error
      if (TagDataList.find(ECRHexStr) != TagDataList.end())
        TagDataList[ECRHexStr]++;
      else
        TagDataList[ECRHexStr] = 1;
      twT1 = Clock::now() + std::chrono::seconds(2);
    }
    timeToQuit = true;
    return;
  };
  std::thread workThreadHandle(ThreadWorker);

  // run and guard
  while (!timeToQuit && Clock::now() < t1)
    ;
  timeToQuit = true;
  workThreadHandle.join();

  // stop
  frame = encodeFrame(OP_FIND_TAGS_STOP, nullptr, 0);
  mSerial->write(frame);
  return TagDataList;
}

UM2xxFrame UM2xx::readFrame(int timeOut) {
  auto s = mSerial->readline(65536, "\r\n");
  return UM2xxFrame(s.begin(), s.end());
}

UM2xxECR UM2xx::dataToECR(UM2xxData data) {
  if (data.size() > 8)
    return UM2xxECR(data.begin() + 2, data.end() - 3);
  else
    return data;
}