#define LED_0 7

void LED_0_ControllerTask(void *parms) {
  
  pinMode(LED_0, OUTPUT);

  while (true) {
    delay(1000);
    digitalWrite(LED_0, HIGH);
    delay(1000);
    digitalWrite(LED_0, LOW);
  }
}