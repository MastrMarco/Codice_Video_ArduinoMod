#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//--------------------------Comunicazione:NRF24L01+----------------------
RF24 radio(9, 10);
const byte addresses[][6] = {"00001", "00002"};

unsigned long tempo = 0;
unsigned long tempo0 = 0;
int limite = 1000;
int Delay = 0;

//-------------------------------Dati------------------------------------
int ricevo = 0;
int invio = 0;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  tempo = millis();
  invio = 2;

  if (tempo >= (tempo0 + limite)) {
    tempo0 = tempo;
    
    Delay =!Delay;

    if (ricevo == 2) {
      Serial.println("Ricevuto");
    }
  }

  switch (Delay) {
    case 0:
      Tx();
      break;
    case 1:
      Rx();
      break;
  }
}

void Tx() {
  radio.startListening();
  while (radio.available()) {
    radio.read(&ricevo, sizeof(ricevo));
  }
}

void Rx() {
  radio.stopListening();
  radio.write(&invio, sizeof(invio));
  ricevo = 0;
}
