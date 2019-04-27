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
SemaphoreHandle_t blinkLEDSem;



void setup()
{
  hardwareinit();
  QueueRFID = xQueueCreate(32, sizeof(uint32_t));
  blinkLEDSem = xSemaphoreCreateCounting(1, 0);

  portBASE_TYPE s1, s2;
  // portBASE_TYPE  hBC26Init,hMFRC,hSSB;
  portBASE_TYPE  hMFRC,hSSB;
  portBASE_TYPE  hSerialReader,hNetworkDaemon,hSocketDaemon,hHeartBeat,hSocketRead;
  s1 = xTaskCreate(ThLEDSemGiver, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  s2 = xTaskCreate(ThLEDSemReceiver, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  hMFRC =  xTaskCreate( ThMFRC522Daemon, NULL,768, NULL, 5, NULL);
  // hBC26Init = xTaskCreate(ThBC26Init, NULL,256, NULL, 5, NULL);
  hSSB =  xTaskCreate( ThSSBDaemon, NULL, configMINIMAL_STACK_SIZE, NULL, 5, NULL);

  hSerialReader = xTaskCreate(ThBC26Reader, NULL, configMINIMAL_STACK_SIZE, NULL, 5, NULL);
  hNetworkDaemon = xTaskCreate( ThBC26NetworkDaemon, NULL, configMINIMAL_STACK_SIZE, NULL, 5, NULL);
  hSocketDaemon= xTaskCreate(ThBC26SocketDaemon, NULL, configMINIMAL_STACK_SIZE, NULL, 5, NULL);
  hSocketRead= xTaskCreate(ThBC26SocketReader, NULL, configMINIMAL_STACK_SIZE, NULL, 5, NULL);
  hHeartBeat =  xTaskCreate(ThBC26HeartBeat, NULL, configMINIMAL_STACK_SIZE, NULL, 5, NULL);

  if (blinkLEDSem== NULL || s1 != pdPASS || s2 != pdPASS)
  // if (blinkLEDSem== NULL || s1 != pdPASS || s2 != pdPASS||hMFRC!=pdPASS||hBC26Init!=pdPASS||hSSB!=pdPASS)
  {
    Serial1.println("FCreation problem");
    while (1);
  }
  vTaskStartScheduler();
  Serial1.println("QInsufficient RAM");
  while (1);
}