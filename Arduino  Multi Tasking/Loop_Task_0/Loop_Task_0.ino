#define LED_0 7
#define LED_1 8

void setup() {
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
}

void loop() {
  Loop_LED_0();
  Loop_LED_1();
}
