//LED
#include <Adafruit_NeoPixel.h>
#define DATA_PIN 8
#define NUMPIXELS 36
Adafruit_NeoPixel Strip = Adafruit_NeoPixel(NUMPIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);




#include <Arduino_FreeRTOS.h>
void TaskSeriale(void *parms);
void LEDControllerTask(void *parms);



void setup() {
  
  xTaskCreate(TaskSeriale, "Seriale", 128, NULL, 1, NULL);
  xTaskCreate(LEDControllerTask, "LED Task", 128, NULL, 1, NULL);
  //vTaskStartScheduler();

}

void loop() {}