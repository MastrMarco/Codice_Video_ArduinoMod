//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.1        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

#define analogInput A0  //PIN Analogico dove è collegato il punto centrale del partitore resistivo
int datiS;
int Campionamento = 30;  // Numero di Campionamenti per fare una Media
int CampNum;
float Con;
float R1 = 30000;  // Inserire il valore del Resistore R1 indicato nello Schema
float R2 = 7500;   // Inserire il valore del Resistore R2 indicato nello Schema
float Volt;        // Valore Convertito in Tensione, è scritto sulla Seriale


//Delay Millis per la scrittura sulla seriale
unsigned long Tempo0 = 0;
int DelayVirtuale = 1000;

//Delay Millis per la conversione da numeri analogici a Tensione / Voltaggio
unsigned long TempoVal = 0;
int DelayVirtuale2 = 50;



//Start
void setup() {
  Serial.begin(115200);

  pinMode(analogInput, INPUT);

  Serial.println("MastrMarco");
  Serial.print("DC VOLTMETRO 1.1v");
}



//Loop
void loop() {

  // Delay Conversione
  if (millis() >= (TempoVal + DelayVirtuale2)) {
    if (CampNum < Campionamento) {
      // leggere il valore sull'ingresso analogico
      datiS += analogRead(analogInput);
      CampNum++;
    } else {
      // Conversione Dati analogici
      Con = ((datiS / (Campionamento + 1)) * 5.0) / 1024;
      Volt = Con / (R2 / (R1 + R2));
      datiS = 0;
      CampNum = 0;
    }
    //delay(50);
    TempoVal = millis();
  }

  // Delay Seriale
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    //Scrittura su seriale
    Serial.print("INPUT V= ");
    Serial.println(Volt);
    //delay(500);
    Tempo0 = millis();
  }
}
