#include <Arduino_FreeRTOS.h>
void LED_0_ControllerTask(void *parms);
void LED_1_ControllerTask(void *parms);

void setup() {
  xTaskCreate(LED_0_ControllerTask, "LED 0 Task", 128, NULL, 1, NULL);
  xTaskCreate(LED_1_ControllerTask, "LED 1 Task", 128, NULL, 1, NULL);
}

void loop() {}