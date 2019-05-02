//
// Created by cn on 2019/5/2.
//

#include "UM2xx.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include "mqtt/async_client.h"
#include "mqttclient.hpp"

using namespace std;

const std::string DFLT_SERVER_ADDRESS   { "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID        { "UHDDriver" };
const string TOPIC { "hello" };
const int  QOS = 1;
const auto TIMEOUT = std::chrono::seconds(10);

const char *LWT_PAYLOAD = "Last will and testament.";


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void ReadThread() {
  um2xx::UM2xx umObj;
  umObj.connect(string("/dev/ttyS2"));
  while (true) {
    while (true) {
      auto data = umObj.CMDFindTagSingle(1000);
      if (data.size() > 10) {
        cout << umObj.DataToHexString(data) << endl;
        break;
      }
    }
    auto data = umObj.CMDFindTags(500);
    std::this_thread::sleep_for(0.5s);
  }
}
#pragma clang diagnostic pop

int main() {
  string address =  DFLT_SERVER_ADDRESS,
         clientID = DFLT_CLIENT_ID;

  cout << "Initializing for server '" << address << "'..." << endl;
  mqtt::async_client client(address, clientID);

  callback cb;
  client.set_callback(cb);

  mqtt::connect_options conopts;
  mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
  mqtt::will_options will(willmsg);
  conopts.set_will(will);
  cout << "  ...OK" << endl;


  cout << "\nConnecting..." << endl;
  mqtt::token_ptr conntok = client.connect(conopts);
  cout << "Waiting for the connection..." << endl;
  conntok->wait();
  cout << "  ...OK" << endl;

  cout << "\nSending message..." << endl;
  mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC,"Test from CNLHC");
  pubmsg->set_qos(QOS);
  client.publish(pubmsg)->wait_for(TIMEOUT);
  cout << "  ...OK" << endl;

  thread readWorker(ReadThread);
  readWorker.join();
  return 0;

}
