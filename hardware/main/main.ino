#include <MapleFreeRTOS900.h>
#include <MFRC522.h>
#include <SPI.h>
#include "./bc26util.hpp"
#include "./hardwareInit.hpp"

#include "./task/SSBDaemon.hpp"
#include "./task/mfrc522Daemon.hpp"
#include "./task/blinkLED.hpp"
#include "./task/bc26Init.hpp"

#define SS_PIN PA4  // CS Pin
#define RST_PIN PA3 // Reset Pin
//信号量定义
SemaphoreHandle_t BC26ReaderTimeOut;
//单例类全局变量
MFRC522 gMFRC522Obj(SS_PIN, RST_PIN);   // Create MFRC522 instance.
BC26 *gBC26Obj = new BC26();
//全局队列定义
QueueHandle_t QueueRFID = NULL;



void setup()
{
  hardwareinit();

  portBASE_TYPE s1, s2, hBC26Init,hMFRC,hSSB;
  blinkLEDSem = xSemaphoreCreateCounting(1, 0);
  s1 = xTaskCreate(ThLEDSemGiver, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  s2 = xTaskCreate(ThLEDSemReceiver, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  hBC26Init = xTaskCreate(ThBC26Init, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  hMFRC =  xTaskCreate( ThMFRC522Daemon, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  hSSB =  xTaskCreate( ThSSBDaemon, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  QueueRFID = xQueueCreate(10, sizeof(uint32_t));

  if (blinkLEDSem== NULL || s1 != pdPASS || s2 != pdPASS)
  {
    Serial1.println(F("Creation problem"));
    while (1);
  }
  vTaskStartScheduler();
  Serial1.println("Insufficient RAM");
  while (1);
}