const int ledPin1 = 10;
const int ledPin2 = 11;
const int ledPin3 = 12;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

const long interval1 = 1000; // intervallo di 1 secondo
const long interval2 = 30; // intervallo di 30 millisecondi
const long interval3 = 250;  // intervallo di 250 millisecondi

int brightness = 0;
int fadeAmount = 5;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Lampeggio del primo LED ogni secondo
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    digitalWrite(ledPin1, !digitalRead(ledPin1));
  }

  // Effetto fade sul secondo LED ogni secondo
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    analogWrite(ledPin2, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }

  // Lampeggio del terzo LED ogni 500 ms
  if (currentMillis - previousMillis3 >= interval3) {
    previousMillis3 = currentMillis;
    digitalWrite(ledPin3, !digitalRead(ledPin3));
  }
}
