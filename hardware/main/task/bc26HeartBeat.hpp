#pragma once
#include <MapleFreeRTOS900.h>

extern BC26 *gBC26Obj;

static void ThBC26HeartBeat(void *arg){
    int innerFSM;
    while(1){
        switch (innerFSM)
        {
            case  0:{
                if(!gBC26Obj->isBusy() && gBC26Obj->mIsSocketConnect){
                    gBC26Obj->deferCommand("AT+QISENDEX=1,24,453144343845314530303030303035453030303030314334\r\n");
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
                    vTaskDelay(10000);
                }
                break;
            }
        }
        vTaskDelay(10);
    }
}