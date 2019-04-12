#pragma once
#include <MapleFreeRTOS900.h>
#include <stdlib.h>
#include "../bc26util.hpp"

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
                if(responseBuf[8]=='1')
                    gBC26Obj->mIsNetworkAvailable=true;
                else
                    gBC26Obj->mIsNetworkAvailable=false;

                vTaskDelay(15000);  //check every 5s
                innerFSM=0;
            }
        };
        vTaskDelay(5);
    }
        
}


