//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.0        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

//Delay Virtuale
unsigned long Tempo0 = 0;
int DelayVirtuale = 1000;


// Lettura Tensione di Uscita
#define Analog_Volt_OUT A0
int datiS;
int Conpionamento = 1;
int CampNum;
float Con;
float R1 = 30000;  //
float R2 = 7500;   //
float Volt;
//Delay Virtuale
unsigned long TempoVal = 0;
int DelayVirtuale2 = 50;





//PWM Anlog auto set
#define PWM_Analog_OUT 3
int Val_PWM = 128;
float Volt_Set = 0;



//----------------------------------
void setup() {

  Serial.begin(115200);

  pinMode(PWM_Analog_OUT, OUTPUT);
  pinMode(Analog_Volt_OUT, INPUT);

  analogWrite(PWM_Analog_OUT, Val_PWM);
  Volt_Set = 5;

  TCCR2B = TCCR2B & B11111000 | B00000001;  // for PWM frequency of 31372.55 Hz  D3 D11
  //TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
  //TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz
}




//----------------------------------
float Tensione() {
  if (millis() >= (TempoVal + DelayVirtuale2)) {
    // leggere il valore sull'ingresso analogico
    if (CampNum < Conpionamento) {
      datiS += analogRead(Analog_Volt_OUT);
      CampNum++;
    } else {
      Con = ((datiS / Conpionamento) * 5.0) / 1024;
      Volt = Con / (R2 / (R1 + R2));
      datiS = 0;
      CampNum = 0;
      ajustaPWM();
    }
    //delay(50);
    TempoVal = millis();
  }
  return Volt;
}

//----------------------------------
void ajustaPWM() {
  if (Volt_Set < Tensione()) {
    if (Val_PWM > 0)
      Val_PWM--;
    analogWrite(PWM_Analog_OUT, Val_PWM);
  } else {
    if (Val_PWM < 255)
      Val_PWM++;
    analogWrite(PWM_Analog_OUT, Val_PWM);
  }
}

//----------------------------------
void loop() {

  if (Serial.available() > 0) {
    String rx = Serial.readString();
    //Val_PWM = rx.toInt();
    Volt_Set = rx.toFloat();
  }
  //analogWrite(PWM_Analog_OUT, Val_PWM);


  if (((Volt_Set - Tensione()) >= 0.35) or ((Tensione() - Volt_Set) >= 0.35)) {
    DelayVirtuale2 = 5;
    Conpionamento = 1;
  } else {
    DelayVirtuale2 = 200;
    Conpionamento = 10;
  }
  Tensione();





  //RPM Ventola
  if (millis() >= (Tempo0 + DelayVirtuale)) {
    Tempo0 = millis();

    Serial.print(Volt_Set, 2);
    Serial.println(" Volt_SET");

    Serial.print(Tensione(), 2);
    Serial.println(" Volt");

    Serial.print(Val_PWM);
    Serial.println(" PWM");

    Serial.print(Conpionamento);
    Serial.println(" Conpionamento");
  }
}
