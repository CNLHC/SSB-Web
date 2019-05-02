//
// Created by cn on 2019/5/2.
//

#include "gtest/gtest.h"
#include "UM2xx.h"
#include <iostream>
#define GTEST_COUT std::cerr <<std::hex<< "[          ] [ INFO ]"


/*!
 * \brief 单测帧构造时数据为空的情况
 */
TEST(UM2xxTest, TestEmptyFrameEncode) {
  um2xx::UM2xx a;
  uint8_t * empty= nullptr;

  // 测试读取硬件信息
  um2xx::UM2xxFrame HardResult=a.encodeFrame(um2xx::OP_GET_HARDWARE_VERSION,empty,0);
  um2xx::UM2xxFrame HardExpect={0xA5,0x5A,0x00,0x08,0x00,0x08,0x0D,0x0A};
  ASSERT_TRUE(HardExpect==HardResult);

  // 测试读取软件信息
  um2xx::UM2xxFrame FirmResult=a.encodeFrame(um2xx::OP_GET_FIRMWARE_VERSION,empty,0);
  um2xx::UM2xxFrame FirmExcept={0xA5,0x5A,0x00,0x08,0x02,0x0A,0x0D,0x0A};
  ASSERT_TRUE(FirmExcept==FirmResult);
}

TEST(UM2xxTest,TestFrameEncode){
  um2xx::UM2xx a;
  uint8_t payload[2] = {0,0x64};
  um2xx::UM2xxFrame Result=a.encodeFrame(um2xx::OP_FIND_TAG_SIGNLE,payload,2);
  um2xx::UM2xxFrame Except={0xA5,0x5A,0x00,0x0A,0x80,0x00,0x64,0xEE,0x0D,0x0A};
  ASSERT_TRUE(Result==Except);
}

TEST(UM2xxTest,TestParseData){
  um2xx::UM2xx a;
  um2xx::UM2xxFrame Frame={0xA5,0x5A,0x00,0x0A,0x80,0x00,0x64,0xEE,0x0D,0x0A};
  um2xx::UM2xxData Result = a.parseDataFromFrame(Frame);
  um2xx::UM2xxData Except = {0x00,0x64};
  ASSERT_TRUE(Except==Result);
}

