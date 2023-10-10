//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.0        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

#define analogPin A0  //PIN Analogico dove è collegato il Resistore parte Positiva

int dataAnalog;                  //Valore Porta Analogica
const byte Campionamento = 50;   // Numero di Campionamenti per fare una Media
const float VoltRef = 1.056;     // V = 1.XXX | mV = 1XXX.00 Tensione di riferimento per i pin Analogici
const float R_Shunt = 0.014151;  // Inserire il valore del Resistore R Shunt
const float ADJ_Error = 0.003;   // Valore in Volt da aggiungere per diminuire l'errore di lettura

int CampNum;  // Variabile per evitare l'utilizzo di un ciclo for{}
float Con;    //Conversione in Volt del valore Analogico


float VoltMedia = 0;  // Valore convertito in tensione Media
float AmpMedia = 0;   // Valore Corrente Media
float VoltOUT = 0;    // Valore Tensione Media


//Delay Virtuale per la funzione di conversione dei dati in Tensione/Corrente
unsigned long TempoVal = 0;
const byte DelayVirtuale2 = 15;  // Valore Max Delay 255ms


//Delay Millis per la scrittura sulla seriale
unsigned long Tempo0 = 0;
const int DelayVirtuale = 200;



void setup() {
  Serial.begin(115200);
  analogReference(INTERNAL);
  pinMode(analogPin, INPUT);

  Serial.println("MastrMarco");
  Serial.print("DC Amperometro 1.0v");
}


void loop() {

  if (millis() >= (TempoVal + DelayVirtuale2)) {
    if (CampNum < Campionamento) {
      dataAnalog = analogRead(analogPin);
      if (dataAnalog != 0 and dataAnalog < 1023) {
        Con = (dataAnalog + 0.5) * (VoltRef / (pow(2, 10) - 1));
        CampNum++;
        if (CampNum != 0) {
          VoltMedia += Con + ADJ_Error;
        }
      } else {
        if (CampNum > 0)
          CampNum--;
      }
    } else if (CampNum == Campionamento) {
      VoltMedia /= (Campionamento);
      VoltOUT = VoltMedia;
      AmpMedia += VoltMedia / R_Shunt;
      VoltMedia = 0;
      CampNum = 0;
    }
    TempoVal = millis();
  }





  // Delay Seriale
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    Serial.print("Tensione RMS V ");
    Serial.print(VoltOUT, 3);
    Serial.print("  Corrente RMS A ");
    Serial.println(AmpMedia, 3);
    Tempo0 = millis();
  }
}
