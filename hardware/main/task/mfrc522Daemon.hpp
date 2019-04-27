#pragma once
extern  MFRC522   gMFRC522Obj;
extern QueueHandle_t QueueRFID ;


static void ThMFRC522Daemon(void *arg){
    int tInnerFSM=0;
    bool cardReadFlag=false;
    bool presentFlag=false;
    uint8_t  i;
    uint32_t RFID=0;
    while(1){
        if (gMFRC522Obj.PICC_IsNewCardPresent()) {
            if(gMFRC522Obj.PICC_ReadCardSerial()){
                for ( i = 0; i < 4; i++)  (RFID) |= (gMFRC522Obj.uid.uidByte[i]<<8*i);
                Serial1.println("New Card Readed");
                Serial1.println(String(RFID,HEX));
                
                xQueueSend(QueueRFID,&RFID,2000);
                gMFRC522Obj.PICC_HaltA(); // Stop reading
                vTaskDelay(1000);
                RFID=0;
            }
        }
        else{
            vTaskDelay(50);
        }
    }
}