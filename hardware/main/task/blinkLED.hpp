
#pragma once
#include <MapleFreeRTOS900.h>

SemaphoreHandle_t blinkLEDSem;
const uint8_t statusLED = LED_BUILTIN;

static void ThLEDSemReceiver(void* arg);
static void ThLEDSemGiver(void* arg);
static void ThLEDSemReceiver(void* arg) {
  while (1) {
    xSemaphoreTake(blinkLEDSem, portMAX_DELAY);
    digitalWrite(statusLED, LOW);
  }
}
static void ThLEDSemGiver(void* arg) {
  pinMode(statusLED, OUTPUT);
  while (1) {
    digitalWrite(statusLED, HIGH);
    vTaskDelay((1000L* configTICK_RATE_HZ) / 1000L);
    xSemaphoreGive(blinkLEDSem);
    vTaskDelay((1000L* configTICK_RATE_HZ) / 1000L);
  }
}
