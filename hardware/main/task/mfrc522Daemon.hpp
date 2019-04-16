#pragma once
extern  MFRC522   gMFRC522Obj;
extern QueueHandle_t QueueRFID ;


static void ThMFRC522Daemon(void *arg){
    int tInnerFSM=0;
    bool cardReadFlag=false;
    bool presentFlag=false;
    uint8_t  i;
    uint32_t RFID=0x12345678;
    while(1){
        if ( gMFRC522Obj.PICC_IsNewCardPresent()) if(gMFRC522Obj.PICC_ReadCardSerial()){
            for ( i = 0; i < 4; i++)  (RFID) |= (gMFRC522Obj.uid.uidByte[i]<<8*i);
            xQueueSend(QueueRFID,(void *)&RFID,2000);
            vTaskDelay(1000);
        }
        else{
            vTaskDelay(200);
        }
        // presentFlag=gMFRC522Obj.PICC_IsNewCardPresent();
        // if (!presentFlag){vTaskDelay(1000);continue;}
        // taskENTER_CRITICAL();
        // // cardReadFlag=gMFRC522Obj.PICC_ReadCardSerial();
        // taskEXIT_CRITICAL();
        // RFID=1;
        // for ( i = 0; i < 4; i++)  (RFID) |= (gMFRC522Obj.uid.uidByte[i]<<8*i);
        // xQueueSend(QueueRFID,(void *)&RFID,2000);
        // vTaskDelay(1000);
    }
}