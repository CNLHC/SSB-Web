#pragma once
extern  MFRC522   gMFRC522Obj;
extern QueueHandle_t QueueRFID ;

static void ThMFRC522Daemon(void *arg){
    uint32_t mocking=0x12345678;
    while(1){
        xQueueSend(QueueRFID,(void *) &mocking,2000);
        vTaskDelay(2000);
    }
}