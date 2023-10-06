//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.2        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

#define analogPin A0  //PIN Analogico dove è collegato il punto centrale del partitore resistivo
int dataAnalog;
int Campionamento = 50;       // Numero di Campionamenti per fare una Media
const float VoltRef = 1.047;  // V = 1.XXX | mV = 1XXX.00 Tensione di riferimento per i pin Analogici
float Con;


float R1 = 173000;       // Inserire il valore del Resistore R1 indicato nello Schema
float R2 = 4500;         // Inserire il valore del Resistore R2 indicato nello Schema
float ADJ_Error = 0.12;  //Valore in Volt da aggiungere per diminuire l'errore di lettura



float Volt;  // Valore Convertito in Tensione



//Delay Millis per la scrittura sulla seriale
unsigned long Tempo0 = 0;
const int DelayVirtuale = 200;



//Start
void setup() {
  Serial.begin(115200);
  analogReference(INTERNAL);
  pinMode(analogPin, INPUT);

  Serial.println("MastrMarco");
  Serial.print("DC VOLTMETRO 1.2v");
}

//Loop
void loop() {

  float VoltMedia = 0;
  for (int i = 0; i < Campionamento; i++) {
    dataAnalog = analogRead(analogPin);
    if (dataAnalog != 0 and dataAnalog < 1023) {
      Con = (dataAnalog + 0.5) * (VoltRef / (pow(2, 10) - 1));
      Volt = Con / (R2 / (R1 + R2));
      if (i != 0) {
        VoltMedia += Volt + ADJ_Error;
      }
    } else {
      i--;
    }
  }
  VoltMedia /= (Campionamento - 1);






  // Delay Seriale
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    //Scrittura su seriale
    Serial.print("Volt no RMS ");
    Serial.print(Volt, 3);
    Serial.print("  Volt RMS ");
    Serial.println(VoltMedia);
    Tempo0 = millis();
  }
}
