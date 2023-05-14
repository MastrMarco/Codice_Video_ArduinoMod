//*****************************************************************************************************************************//
//------------------          By  MastrMarco    Versione 1.00        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//
//---------------
int Pc;
int SerialComand = 3;

unsigned long tempo = 0;
unsigned long tempo0 = 0;
int limite = 50;

int Mod = 0;
int const Ometro = 0;
int const Voltmetro = 1;
int const MisuratoreDiCondensatore = 2;

int PinVoltmetro = A0;
int PinOmetro = A1;
int PinMisuratoreDiCondensatore = A2;
int chargePinCondensatore = 13;
int dischargePinCondensatore = 11;
int DL = 0;
float Varduino5V = 5.08f;

//----------------------------------------------------------------------
int Compatibile = 5;
int InfoArduino = 3;
float Ver = 1.00;
int ModMIS = 1;
int Progetto = 3;
float SerialDataInvio;
int BRIGHTNESS;


void setup() {
  Serial.begin(9600);
  pinMode(PinVoltmetro, INPUT);
  pinMode(PinOmetro, INPUT);
  pinMode(PinMisuratoreDiCondensatore, INPUT);
  pinMode(chargePinCondensatore, OUTPUT);
  digitalWrite(dischargePinCondensatore, LOW);
  Serial.println("/*************************/");
  Serial.println("/******By_MastrMarco******/");
  Serial.println("/******** V 1.00 *********/");
  Serial.println("/*************************/");
  Serial.println("");
  Serial.println("");
  Serial.println("");
}
void loop() {
  tempo = millis();
  if (tempo >= (tempo0 + limite)) {
    tempo0 = tempo;
    //----------------------------------------------------------------------
    //                Verifica Compatibile(0)        Tipo di Arduino(1)               Invio Dati(2)                  MOD (3)              Versione(4)       Sequenza di progetto(5)
    String data = String (Compatibile) + ";" + String (InfoArduino) + ";" + String (SerialDataInvio) + ";" + String (ModMIS) + ";" + String (Ver) + ";" + String (Progetto) + ";";
    Serial.println(data);
  }

  if (Serial.available()) {
    Pc = Serial.parseInt();
    Serial.read();
    if (Pc == 340) {
      Mod = Ometro;
      ModMIS = 1;
    }
    if (Pc == 341) {
      Mod = Voltmetro;
      ModMIS = 2;
    }
    if (Pc == 342) {
      Mod = MisuratoreDiCondensatore;
      SerialComand = 3;
      ModMIS = 3;
    }
    if (Pc == 343) {
      DL = 0;
    }
  }
  Set();
}

void Set() {
  switch (Mod) {
    case Ometro: LetturaResistore();
      break;
    case Voltmetro: LetturaTensione();
      break;
    case MisuratoreDiCondensatore: LetturaCondensatore();
      break;
  }
}
//------------------------------------------------------------[Ometro]-----------------------------------------------------------------------
float Rx, v1 = 0;
float R1_Ometro = 933;
unsigned long tempoR = 0;
unsigned long tempoRr = 0;
int limiteLR = 500;

void LetturaResistore() {
  tempoR = millis();
  int Rdato = analogRead(PinOmetro);
  v1 = map(Rdato, 0, 1024, 0, 5080) / 1000.0; //mV
  Rx = (R1_Ometro * (Varduino5V - v1)) / v1;
  if (tempoR >= (tempoRr + limiteLR)) {
    tempoRr = tempoR;
    SerialDataInvio = Rx;
  }
}

//-----------------------------------------------------------[Voltmetro]---------------------------------------------------------------------
float Con = 0.0;
float Volt = 0.0;
float R1_Voltmetro = 29900.0;
float R2_Voltmetro = 7490.0;
int datiS = 0;
unsigned long tempoT = 0;
unsigned long tempoTr = 0;
int limiteLT = 500;

void LetturaTensione() {
  tempoT = millis();
  // leggere il valore sull'ingresso analogico
  datiS = analogRead(PinVoltmetro);
  Con = (datiS * Varduino5V ) / 1008;
  Volt = Con / (R2_Voltmetro / (R1_Voltmetro + R2_Voltmetro));
  if (tempoT >= (tempoTr + limiteLT)) {
    tempoTr = tempoT;
    SerialDataInvio = Volt, 2;
  }
}

//----------------------------------------------------------[Condensatore]-------------------------------------------------------------------
#define resistorValue 10000.0F
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;
unsigned long tempoC = 0;
unsigned long tempoCr = 0;
int limiteLC = 500;


void LetturaCondensatore() {
  tempoC = millis();
  digitalWrite(chargePinCondensatore, HIGH);
  startTime = millis();

  if ( DL < 5  ) {
    while (analogRead(PinMisuratoreDiCondensatore) < 648) {
      if (Serial.available()) {
        SerialComand = Serial.parseInt();
        Serial.read();
        if ((SerialComand = 1) or (SerialComand = 2) ) {
          if (SerialComand == 340) {
            Mod = Ometro;
          }
          if (SerialComand == 341) {
            Mod = Voltmetro;
          }
          break;
        }
      }
      String data = String (Compatibile) + ";" + String (InfoArduino) + ";" + String (SerialDataInvio) + ";" + String (ModMIS) + ";" + String (Ver) + ";" + String (Progetto) + ";";
      Serial.println(data);
      ModMIS = 10;
    }
  }
  elapsedTime = millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;

  if (microFarads > 1) {
    DL = (long)microFarads;
    SerialDataInvio = (long)microFarads;
    ModMIS = 3;
  }
  else {
    if (Mod == MisuratoreDiCondensatore and  DL < 5) {
      if (tempoC >= (tempoCr + limiteLC)) {
        tempoCr = tempoC;
        nanoFarads = microFarads * 1000.0;
        SerialDataInvio = (long)nanoFarads, 0;
        ModMIS = 4;
      }
    }
    if (analogRead(PinMisuratoreDiCondensatore) > 1000) {
      ModMIS = 11;
      DL = 0;
    }
  }
  digitalWrite(chargePinCondensatore, LOW);
  pinMode(dischargePinCondensatore, OUTPUT);
  digitalWrite(dischargePinCondensatore, LOW);
  while (analogRead(PinMisuratoreDiCondensatore) > 0) {
  }
  pinMode(dischargePinCondensatore, INPUT);
}
