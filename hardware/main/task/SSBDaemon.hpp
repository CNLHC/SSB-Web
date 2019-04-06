#pragma once
#include "../ssb/SSBEncodeFrame.hpp"
extern BC26 *gBC26Obj;
extern QueueHandle_t QueueRFID ;
void ThSSBDaemon(void * arg){
    uint32_t RFID=0;
    bool tSendDeferred=false;
    int innerFSM=0;
    String Send ="";
    while(1){
        switch (innerFSM){
            case 0:{
                RFID=0;
                Send="";
                innerFSM=1;
                break;
            }
            case 1:{
                xQueueReceive(QueueRFID,&RFID,3000);
                Serial1.println("Get Queue Item");
                Serial1.println(String(RFID,HEX));
                if(RFID!=0){
                    innerFSM=2;
                    Send = SSBEncodeFrame(0,RFID);
                }
                break;
            }
            case 2:{
                if(!gBC26Obj->isBusy() && gBC26Obj->mIsNetworkAvailable && gBC26Obj->mIsSocketConnect){
                    gBC26Obj->deferCommand( ("AT+QISENDEX=1,24,"+Send).c_str());
                    innerFSM=3;
                }
                break;
            }
            case 3:{
                if(gBC26Obj->mIsResponseSet){
                    gBC26Obj->releaseLock();
                    innerFSM=0;
                }
                break;
            }
        }
        vTaskDelay(10);
    }
}