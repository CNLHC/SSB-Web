#pragma once
#include <MapleFreeRTOS900.h>
#include <stdlib.h>
#include "../bc26util.hpp"
#include "../ssb/SSBConfig.h"

extern BC26 *gBC26Obj;
static void  ThBC26SocketDaemon(void * args);
static void  ThBC26SocketDaemon(void * args){
    int innerFSM = 0;
    char tResBuf[50];
    
    while(1){
        switch (innerFSM)
        {
            case 0:{
                Serial1.println("In Socket Daemon 0");
                if(gBC26Obj->mIsNetworkAvailable)
                    innerFSM = 1;
                vTaskDelay(1000);
                break;
            }
            case 1:{
                Serial1.println("In Socket Daemon 1");
                if(!gBC26Obj->isBusy()){
                    gBC26Obj->deferCommand("AT+QISTATE=0,1");
                    innerFSM=2;
                }
                break;
            }
            case 2:{
                if(gBC26Obj->mIsResponseSet){
                    int len=strlen(gBC26Obj->mMessage);
                    memcpy(tResBuf,gBC26Obj->mMessage,sizeof(tResBuf[0])*len);
                    tResBuf[len] = '\0';
                    gBC26Obj->releaseLock();
                    if(strstr(tResBuf,"QISTATE")==NULL)
                        innerFSM=3;
                    else{
                        char * p = strstr(tResBuf,"3001,");
                        Serial1.println(tResBuf);
                        Serial1.println("Socket Status");
                        Serial1.print(p[5]);
                        Serial1.print('\n');

                        if(p==NULL)
                            innerFSM=3;
                        else{
                            if(p[5]=='1'){//connecting
                                innerFSM=0;
                                vTaskDelay(SSB_BC26_SOCKET_CONNECTING_POLLING_INTERVAL);
                                gBC26Obj->mIsSocketConnect=false;
                            }
                            else if (p[5]=='2'){ 
                                innerFSM=7;
                                gBC26Obj->mIsSocketConnect=true;
                            }
                            else if (p[5]=='3'){ //Need close and reopen
                                innerFSM=5;
                                gBC26Obj->mIsSocketConnect=false;
                            }
                            else{ //Unknown
                                innerFSM=0;
                                gBC26Obj->mIsSocketConnect=false;
                            }
                        }
                    }
                }
                break;
            }
            case 3:{
                if(!gBC26Obj->isBusy()){
                    gBC26Obj->deferCommand("AT+QIOPEN=1,1,\"TCP\",\"39.105.151.150\",2334,3001,0,0\r\n");
                    innerFSM=4;
                }
                break;
            }

            case 4:{
                if(gBC26Obj->mIsResponseSet){
                    Serial1.println("Scoket Daemon 4");
                    Serial1.println(gBC26Obj->mMessage);
                    if(strstr(gBC26Obj->mMessage,"QIOPEN")!=NULL 
                        ||strstr(gBC26Obj->mMessage,"ERROR")!=NULL){
                        gBC26Obj->releaseLock();
                        innerFSM = 0;
                    }
                    vTaskDelay(SSB_BC26_SOCKET_QIOPEN_POLLING_INTERVAL);
                }
                break;
            }

            case 5:{
                Serial1.println("Scoket Daemon 5(Transient)");
                if(!gBC26Obj->isBusy()){
                    gBC26Obj->deferCommand("AT+QICLOSE=1\r\n");
                    innerFSM=6;
                }
                break;
            }

            case 6:{
                if(gBC26Obj->mIsResponseSet){
                    gBC26Obj->releaseLock();
                    innerFSM=0;
                }
                break;
            }

            case 7:{
                if(!gBC26Obj->isBusy()){
                    gBC26Obj->deferCommand("AT+QISWTMD=1,0\r\n");
                    innerFSM=8;
                }
                break;
            }
            case 8:{
                if(gBC26Obj->mIsResponseSet){
                    gBC26Obj->releaseLock();
                    innerFSM=0;
                    vTaskDelay(SSB_BC26_SOCKET_RECHECK_CONNECTIVITY_INTERVAL);
                }
                break;
            }
        }
        vTaskDelay(SSB_BC26_SOCKET_FSM_REFRESH_INTERVAL);
    }
}