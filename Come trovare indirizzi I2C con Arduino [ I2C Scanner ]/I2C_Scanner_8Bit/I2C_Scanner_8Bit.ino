//*****************************************************************************************************************************//
//-------------------           By  MastrMarco    Versione 1.00      ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//
// ---------------------------------------
// Scansione_I2C
//
// Versione 6
// Questo programma (o codice simile)
// può essere trovato in molti posti.
// Ad esempio sul forum Arduino.cc.
// L'autore originale non è noto.
//
// Questo sketch verifica gli indirizzi standard a 7 bit
// I dispositivi con un indirizzo di bit più alto potrebbero non essere visti correttamente.
// ---------------------------------------

#include <Wire.h>


void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: attendi monitor seriale
  Serial.println("\nI2C Scansione");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scansione...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // I2C_scanner utilizza il valore di ritorno di
    // Write.endTransmisstion per vedere se
    // un dispositivo ha riconosciuto l'indirizzo.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C dispositivo trovato all'indirizzo 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Errore sconosciuto all'indirizzo 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("Nessun dispositivo I2C trovato\n");
  else
    Serial.println("Fatto\n");

  delay(5000);           // attendi 5 secondi per la scansione successiva
}
