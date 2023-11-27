//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.2.1      ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

#define analogPin A0  //PIN Analogico dove è collegato il punto centrale del partitore resistivo

int dataAnalog;                 //Valore Porta Analogica
const byte Campionamento = 50;  // Numero di Campionamenti per fare una Media
const float VoltRef = 4.856;    // V = 1.XXX | mV = 1XXX.00 Tensione di riferimento per i pin Analogici
int CampNum;                    // Variabile per evitare l'utilizzo di un ciclo for{}
float Con;                      //Conversione in Volt del valore Analogico


const float R1 = 173000;       // Inserire il valore del Resistore R1 indicato nello Schema
const float R2 = 4500;         // Inserire il valore del Resistore R2 indicato nello Schema
const float ADJ_Error = 0.12;  //Valore in Volt da aggiungere per diminuire l'errore di lettura


float Volt;           // Valore Convertito in Tensione
float VoltMedia = 0;  // Valore convertito in tensione Media
float VoltOUT = 0;    // Valore Tensione Media


//Delay Virtuale per la funzione di conversione dei dati in Tensione
unsigned long TempoVal = 0;
const byte DelayVirtuale2 = 15;  // Valore Max Delay 255ms


//Delay Millis per la scrittura sulla seriale
unsigned long Tempo0 = 0;
const int DelayVirtuale = 200;




void setup() {
  Serial.begin(115200);
  pinMode(analogPin, INPUT);

  Serial.println("MastrMarco");
  Serial.print("DC VOLTMETRO 1.2.1v");
}




void loop() {

  if (millis() >= (TempoVal + DelayVirtuale2)) {
    if (CampNum < Campionamento) {
      dataAnalog = analogRead(analogPin);
      if (dataAnalog != 0 and dataAnalog < 1023) {
        Con = (dataAnalog + 0.5) * (VoltRef / (pow(2, 10) - 1));
        Volt = Con / (R2 / (R1 + R2));
        CampNum++;
        if (CampNum != 0) {
          VoltMedia += Volt + ADJ_Error;
        }
      } else {
        if (CampNum > 0)
          CampNum--;
      }
    } else if (CampNum == Campionamento) {
      VoltMedia /= (Campionamento);
      VoltOUT = VoltMedia;
      VoltMedia = 0;
      CampNum = 0;
    }
    if ((CampNum == 0) and (dataAnalog == 0)) {
      VoltOUT = 0;
      VoltMedia = 0;
    }
    TempoVal = millis();
  }





  // Delay Seriale
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    Serial.print("Volt no RMS ");
    Serial.print(Volt, 3);
    Serial.print("  Volt RMS ");
    Serial.println(VoltOUT);
    Tempo0 = millis();
  }
}
