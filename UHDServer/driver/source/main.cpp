//
// Created by cn on 2019/5/2.
//

#include "UM2xx.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {
  um2xx::UM2xx umObj;
  umObj.connect(string("/dev/ttyS2"));
  while(1){
    while(1){
      auto data = umObj.CMDFindTagSingle(1000);
      cout<<umObj.DataToHexString(data)<<endl;
      if(data.size()>10)
        break;
    }
    auto data = umObj.CMDFindTags(500);
    for (auto &j :data){
      cout<<"标签:"<<j.first<<"\t次数:"<<j.second<<endl;
    }
    cout<<"共获得标签"<<data.size()<<"个"<<endl;
    cout<<"done";
    std::this_thread::sleep_for(0.05s);


  }



}
//3000E28068940000500380417C8400D201
//3400300833B2DDD901400000000000C301


//30 00 00 B0 7A 13 EC 36 F4 C8 08 00 37 B5 00 BA 01