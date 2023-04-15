#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//--------------------------Comunicazione:NRF24L01+----------------------
RF24 radio(9, 10);
const byte addresses[][6] = {"00001", "00002"};

//------------------------------------------------------------------------
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
  invio = 10;

//-------------------------Comandi_Trasmisione----------------------------
  delay(100);

  radio.startListening();
  while (radio.available()) {
    radio.read(&ricevo, sizeof(ricevo));
  }
  Serial.println(ricevo);

  delay(100);

  radio.stopListening();
  radio.write(&invio, sizeof(invio));
  
  ricevo = 0;

}
