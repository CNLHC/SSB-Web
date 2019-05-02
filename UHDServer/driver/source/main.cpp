//
// Created by cn on 2019/5/2.
//

#include "UM2xx.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
  um2xx::UM2xx umObj;
  umObj.connect(string("/dev/ttyS33"));
  auto data = umObj.CMDSimpleGet(um2xx::OP_GET_FIRMWARE_VERSION);
  for (auto & j: data)
    cout<<(unsigned int)j<< endl;
  cout<<"done";
}