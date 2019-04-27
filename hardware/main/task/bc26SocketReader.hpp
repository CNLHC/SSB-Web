#pragma once
#include <MapleFreeRTOS900.h>
#include "../ssb/SSBConfig.h"

extern BC26 *gBC26Obj;

static void ThBC26SocketReader(void *arg){
    int innerFSM;
    while(1){
        switch (innerFSM)
        {
            case  0:{
                if(!gBC26Obj->isBusy() && gBC26Obj->mIsSocketConnect){
                    gBC26Obj->deferCommand("AT+QIRD=1,10");
                    innerFSM=1;
                }
                break;
            }
            case 1:{
                if(gBC26Obj->mIsResponseSet){
                    Serial1.println("Read some bytes");
                    Serial1.println(gBC26Obj->mMessage);
                    gBC26Obj->releaseLock();
                    innerFSM=0;
                    vTaskDelay(SSB_BC26_SOCKET_READ_POLLING_INTERVAL);
                }
                break;
            }
        }
        vTaskDelay(100);
    }
}