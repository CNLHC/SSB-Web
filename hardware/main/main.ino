#include <MapleFreeRTOS900.h>
#include "./hardwareInit.hpp"
#include "./bc26util.hpp"
#include "./task/blinkLED.hpp"
#include "./task/bc26Reader.hpp"
//信号量定义
SemaphoreHandle_t BC26ReaderTimeOut;
//单例全局变量
BC26 *gBC26Obj = new BC26();

void setup()
{
  hardwareinit();
  Serial1.println("hello");
  gBC26Obj->deferCommand("AT+CGACT?\r\n");
  // gBC26Obj->deferCommand("ATE0\r\n");

  portBASE_TYPE s1, s2, hSerialReader;
  blinkLEDSem = xSemaphoreCreateCounting(1, 0);
  s1 = xTaskCreate(ThLEDSemGiver, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  s2 = xTaskCreate(ThLEDSemReceiver, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  hSerialReader = xTaskCreate(ThBC26Reader, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  if (blinkLEDSem== NULL || s1 != pdPASS || s2 != pdPASS)
  {
    Serial1.println(F("Creation problem"));
    while (1)
      ;
  }
  vTaskStartScheduler();
  Serial1.println("Insufficient RAM");
  while (1);
}