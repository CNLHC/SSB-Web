//
// Created by cn on 2019/5/2.
//

#ifndef DRIVER_UM210_H
#define DRIVER_UM210_H

#include "UM2xxOpCode.h"
#include "serial/serial.h"
#include <vector>
#include <unordered_map>

/*!
 * \brief UM2xx 设备驱动
 */
namespace um2xx {
typedef std::vector<uint8_t> UM2xxFrame;
typedef std::vector<uint8_t> UM2xxData;
typedef std::vector<uint8_t> UM2xxECR;




class UM2xx {




public:
   UM2xxData DataEmpty;

  /*!
   * \brief 编码一个UM2xx数据帧
   * \param buf  编码输出
   * \param code UM2xx帧类型
   * \param data UM2xx帧数据
   * \param datasize UM2xx 数据长度。(注意是数据长度，不是帧长度)
   */
  UM2xxFrame encodeFrame(opcode code, uint8_t *data, uint16_t datasize);

  bool isFrameAvailable(UM2xxFrame &frame);

  UM2xxData parseDataFromFrame(UM2xxFrame &frame);

  UM2xxData CMDGetHarwareInfo();

  UM2xxData CMDSimpleGet(opcode code);

  UM2xxData CMDFindTagSingle(uint16_t waitingTime);

  std::unordered_map<std::string,int> CMDFindTags(uint16_t MaxTimes);

  std::string DataToHexString(UM2xxData &data);

  void connect(const std::string &port);




private:
  serial::Serial * mSerial= nullptr;
  /*!
   * \brief 由数据长度换算得到帧长度
   * \param datasize 数据长度
   *
   * 帧长度 = 2 + 2 + 1 + N + 1+ 2
   * (帧头, 帧长, 类型, 数据, 校验，帧尾)
   */
  uint16_t getFrameSize(uint16_t datasize);
  uint16_t getDataSize(uint16_t frameSize);
  /*!
   * \brief 由帧数据获取CRC校验码
   * \param datasize 数据长度
   * \param data 帧数据
   * \param code 帧类型
   *
   * 校验码的获取方式是每帧数据所有字节（除去帧头和帧尾）异或.
   */
  uint8_t getFrameCRC(opcode code,uint8_t *data, uint16_t datasize);
  UM2xxFrame readFrame(int timeOut);
  UM2xxECR dataToECR( UM2xxData data);






  bool isConnected(){return mSerial!= nullptr;};

};

} // namespace um2xx

#endif // DRIVER_UM210_H
