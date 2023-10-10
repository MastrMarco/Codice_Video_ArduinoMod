//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.0        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

#define analogPin A0  // PIN Analogico dove è collegato il Resistore parte Positiva

int dataAnalog;
const byte Campionamento = 50;   // Numero di Campionamenti per fare una Media
const float VoltRef = 1.056;     // V = 1.XXX | mV = 1XXX.00 Tensione di riferimento per i pin Analogici
const float R_Shunt = 0.014151;  // Inserire il valore del Resistore R Shunt
const float ADJ_Error = 0.003;   // Valore in Volt da aggiungere per diminuire l'errore di lettura
float Con;                       //Conversione in Volt del valore Analogico


//Delay Millis per la scrittura sulla seriale
unsigned long Tempo0 = 0;
const int DelayVirtuale = 200;


//Start
void setup() {
  Serial.begin(115200);
  analogReference(INTERNAL);
  pinMode(analogPin, INPUT);

  Serial.println("MastrMarco");
  Serial.print("DC Amperometro 1.0v");
}

//Loop
void loop() {

  float VoltMedia = 0;
  float AmpMedia = 0;
  for (int i = 0; i < Campionamento; i++) {
    dataAnalog = analogRead(analogPin);
    delay(10);
    if (dataAnalog != 0 and dataAnalog < 1023) {
      Con = (dataAnalog + 0.5) * (VoltRef / (pow(2, 10) - 1));
      if (i != 0) {
        VoltMedia += Con + ADJ_Error;
      }
    } else {
      i--;
    }
  }
  delay(5);
  VoltMedia /= (Campionamento - 1);
  AmpMedia += VoltMedia / R_Shunt;




  // Delay Seriale
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    //Scrittura su seriale
    Serial.print("Tensione RMS V ");
    Serial.print(VoltMedia, 3);
    Serial.print("  Corrente RMS A ");
    Serial.println(AmpMedia, 2);
    Tempo0 = millis();
  }
}
