#pragma once
#include <MapleFreeRTOS900.h>
#include "./bc26Reader.hpp"
#include "./bc26NetworkDaemon.hpp"
#include "./bc26SocketDaemon.hpp"
#include "./bc26SocketReader.hpp"
#include "./bc26HeartBeat.hpp"

extern BC26 *gBC26Obj;

static void ThBC26Init(void *arg){
    // if(hHeartBeat ==pdPASS)
    //     Serial1.println("ThBC26HeartBeat Created");

    gBC26Obj->mIsNetworkAvailable=true;

    int innerFSM=0;


    while(1){
    switch(innerFSM){
            case 0:{
                if(!gBC26Obj->isBusy()){
                    Serial1.println("BC26 Init process");
                    gBC26Obj->deferCommand("AT\r\n");
                    innerFSM=1;
                }
                break;
            }
            case 1:{
                if(gBC26Obj->mIsResponseSet){
                    gBC26Obj->releaseLock();
                    innerFSM=2;
                }
                break;
            }
            case 2:{
                vTaskDelay((10000L* configTICK_RATE_HZ) / 1000L);
                break;
            }
        }
        vTaskDelay(100);
    }
}