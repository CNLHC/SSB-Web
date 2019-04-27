#pragma once
#include <MapleFreeRTOS900.h>
#include <stdlib.h>
#include "../bc26util.hpp"
#include "../ssb/SSBConfig.h"

extern BC26 *gBC26Obj ;

static void ThBC26NetworkDaemon(void *arg);
static void ThBC26NetworkDaemon(void *arg){
    char responseBuf[40];
    int innerFSM = 0;
    while(1){
        switch (innerFSM)
        {
            case 0:{
                if(!gBC26Obj->isBusy()){
                    gBC26Obj->deferCommand("AT+CGATT?\r\n");
                    innerFSM=1;
                }
                break;
            }
            case 1:{
                if(gBC26Obj->mIsResponseSet){
                    memcpy(responseBuf,gBC26Obj->mMessage,sizeof(responseBuf[0])*strlen(gBC26Obj->mMessage));
                    gBC26Obj->releaseLock();
                    innerFSM=2;
                }
                break;
            }
            case 2:{
                if(responseBuf[8]=='1'){
                    Serial1.println("Network available");
                    gBC26Obj->mIsNetworkAvailable=true;
                    vTaskDelay(SSB_BC26_NETWORK_CHECK_INTERVAL_WHEN_CONNECT);  //check every 5s
                }
                else{
                    Serial1.println("Network unavailable");
                    gBC26Obj->mIsNetworkAvailable=false;
                    vTaskDelay(SSB_BC26_NETWORK_CHECK_INTERVAL_WHEN_DISCONNECT );  //check every 5s
                }

                innerFSM=0;
            }
        };
        vTaskDelay(SSB_BC26_NETWORK_FSM_REFRESH_INTERVAL);
    }
        
}


