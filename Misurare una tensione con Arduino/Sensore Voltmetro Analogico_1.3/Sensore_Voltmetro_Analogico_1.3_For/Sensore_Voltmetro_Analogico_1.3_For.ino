//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.3        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

#define pinPartitore A0  // Pin analogico a cui è collegato il punto centrale del partitore resistivo

const int numeroCampioni = 50;  // Numero di campioni da utilizzare per la media mobile
int campioni[numeroCampioni];   // Array per memorizzare i campioni


/* 
In questo codice, ho aggiunto un array tensioniRiferimento che contiene i valori di tensione di riferimento per la calibrazione multi-punto 
e un array correzioni che contiene i fattori di correzione corrispondenti. Il codice cicla attraverso questi array 
e applica la correzione appropriata in base alla tensione letta. Assicurati di inserire i valori di tensione di riferimento 
e i fattori di correzione corrispondenti in modo corretto.
*/
// Valori di tensione di riferimento per la calibrazione multi-punto
float tensioniRiferimento[] = { 5.0, 10.0, 15.0, 25.0 };           // Inserire qui i valori di tensione di riferimento
int numeroTensioni = sizeof(tensioniRiferimento) / sizeof(float);  // Numero di valori di tensione di riferimento
// Valori di correzione per la calibrazione multi-punto
//                      <=5v  <=10v  <=15v  <=25v
float correzioni[] = { 1.005, 0.996, 0.988, 0.985 };  // Fattori di correzione empirici corrispondenti ai valori di tensione di riferimento


float R1 = 10000;  // Inserire il valore del Resistore R1 indicato nello Schema
float R2 = 1000;   // Inserire il valore del Resistore R2 indicato nello Schema
float AREF = 5.0;  // Valore di Riferimento Analogico. Per Arduino UNO ecc.. 5V e per ESP32 ecc... 3.3v


void setup() {
  Serial.begin(115200);  // Inizializza la comunicazione seriale
}

void loop() {
  // Leggi i campioni
  for (int i = 0; i < numeroCampioni; i++) {
    campioni[i] = analogRead(pinPartitore);
    delayMicroseconds(370);  // Aggiungi un piccolo ritardo tra le letture
  }

  // Calcola la media mobile
  float media = 0;
  for (int i = 0; i < numeroCampioni; i++) {
    media += campioni[i];
  }
  media /= numeroCampioni;

  // Converti in tensione
  float tensione = media * (AREF / 1023.0);  // Tensione senza correzione
  // Calcola la tensione corretta utilizzando i valori del partitore resistivo
  tensione /= (R2 / (R1 + R2));

  // Correzione basata sulla calibrazione multi-punto
  for (int i = 0; i < numeroTensioni; i++) {
    if (tensione <= tensioniRiferimento[i]) {
      tensione *= correzioni[i];
      break;  // Esci dal ciclo dopo aver applicato la correzione
    }
  }

  // Stampa il valore
  Serial.print("Tensione: ");
  Serial.print(tensione, 2);  // Stampa con 2 cifre decimali
  Serial.println(" V");

  delay(500);  // Attendere un secondo prima di leggere nuovamente il valore
}
