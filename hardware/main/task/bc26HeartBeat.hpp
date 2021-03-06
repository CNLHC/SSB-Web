#pragma once
#include <MapleFreeRTOS900.h>

extern BC26 *gBC26Obj;
static void ThBC26HeartBeat(void *arg);

static void ThBC26HeartBeat(void *arg){
    int innerFSM;
    Serial1.println("Heartbeat");
    while(1){
        switch (innerFSM)
        {
            case  0:{
                if(!gBC26Obj->isBusy() && gBC26Obj->mIsSocketConnect){
                    Serial1.println("Heartbeat Defered");
                    gBC26Obj->deferCommand(SSB_BC26_NETWORK_HEARTBEAT_PAYLOAD  );
                    innerFSM=1;
                }
                break;
            }
            case 1:{
                if(gBC26Obj->mIsResponseSet){
                    Serial1.println("Heartbeat Thread ");
                    Serial1.println(gBC26Obj->mMessage);
                    gBC26Obj->releaseLock();
                    innerFSM=0;
                    vTaskDelay(SSB_BC26_NETWORK_HEARTBEAT_INTERVAL);
                }
                break;
            }
        }
        vTaskDelay(100);
    }
}