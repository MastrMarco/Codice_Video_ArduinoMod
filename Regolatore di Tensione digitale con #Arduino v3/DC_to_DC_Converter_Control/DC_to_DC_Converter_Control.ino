//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.0        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//
/*
*Code By MastrMarco
*Libreria by: https://github.com/GitMoDu/FastX9CXXX
*/

#include <FastX9CXXX.h>
#define X9_CS_PIN 10
#define X9_UD_PIN 8
#define X9_INC_PIN 9
FastX9C103 Potentiometer(X9_CS_PIN, X9_UD_PIN, X9_INC_PIN);


// Lettura Tensione di Uscita
#define Analog_Volt_OUT A0
int datiS;
int Campionamenti = 5;  // Numero di Campionamenti
int CampNum;
float Con;
float R1 = 30000;  // => 30k
float R2 = 7500;   // => 7.5K
float Volt;
//Delay Virtuale
unsigned long TempoVal = 0;
int DelayVirtuale2 = 50;


//Valori impostabili
int Val_Resistore = 50;  // 0 - 100
float Volt_Set = 0;  // 0 - 100


//Delay Virutale
unsigned long Tempo0 = 0;
int DelayVirtuale = 1000;



void setup() {

  Serial.begin(115200);

  pinMode(Analog_Volt_OUT, INPUT);

  Potentiometer.Reset();

  Volt_Set = 5;
}


//----------------------------------
float Tensione() {
  if (millis() >= (TempoVal + DelayVirtuale2)) {
    // leggere il valore sull'ingresso analogico
    if (CampNum < Campionamenti) {
      datiS += analogRead(Analog_Volt_OUT);
      CampNum++;
    } else {
      Con = ((datiS / (Campionamenti + 1)) * 5.0) / 1024;
      Volt = Con / (R2 / (R1 + R2));
      datiS = 0;
      CampNum = 0;
      ajustaResistore();
    }
    TempoVal = millis();
  }
  return Volt;
}


//----------------------------------
void ajustaResistore() {
  if (Volt_Set > Tensione()) {
    if (Val_Resistore > 0) {
      Val_Resistore--;
      Potentiometer.JumpToStep(Val_Resistore);
    }
  } else {
    if (Val_Resistore < 100) {
      Val_Resistore++;
      Potentiometer.JumpToStep(Val_Resistore);
    }
  }
}


void loop() {

  if (Serial.available() > 0) {
    String rx = Serial.readString();
    Volt_Set = rx.toFloat();
  }

  if (((Volt_Set - Tensione()) >= 0.35) or ((Tensione() - Volt_Set) >= 0.35)) {
    DelayVirtuale2 = 5;
    Campionamenti = 1;
  } else {
    DelayVirtuale2 = 500;
    Campionamenti = 5;
  }
  Tensione();



  //Serial Monitor
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    Tempo0 = millis();

    Serial.print(Volt_Set, 2);
    Serial.println(" Volt_SET");

    Serial.print(Tensione(), 2);
    Serial.println(" Volt");

    Serial.print(Potentiometer.GetEstimatedResistance(), DEC);
    Serial.println(F(" Ohm"));

    Serial.print(Campionamenti);
    Serial.println(" Campionamenti");
  }
}
