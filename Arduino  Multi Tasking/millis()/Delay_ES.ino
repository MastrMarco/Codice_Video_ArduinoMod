const int ledPin1 = 10;
const int ledPin2 = 11;
const int ledPin3 = 12;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  // Lampeggio del primo LED ogni secondo
  digitalWrite(ledPin1, HIGH);
  delay(1000);
  digitalWrite(ledPin1, LOW);
  delay(1000);

  // Effetto fade sul secondo LED ogni 30 ms
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(ledPin2, brightness);
    delay(30);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(ledPin2, brightness);
    delay(30);
  }

  // Lampeggio del terzo LED ogni 250 ms
  digitalWrite(ledPin3, HIGH);
  delay(250);
  digitalWrite(ledPin3, LOW);
  delay(250);
}

