//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.0        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//

//Display OLED i2c
#include <Adafruit_SH1106.h>
#define OLED_RESET 2
Adafruit_SH1106 display(OLED_RESET);
String Set = "Null";


#define Pin_Btn 5  //Pin digitale di Arduino dove è collegato il bottone

#define Pressione_Corta 50        // Tempo minimo (ms) tra una pressione e l'altra [Delay virtuale]
#define Pressione_Lunga 400       // Tempo minimo (ms) per la pressione Lunga
#define Intervallo_Pressione 260  // Tempo aggiuntivo (ms) all'rilascio del bottone che permette di avere pressioni multiple
unsigned long tempoM = 0;         //Delay virtuale

bool BtnSato;          // Stato del livello attuale del bottone
bool PreBtnStato = 0;  // Stato del livello precedente ad una nuova variazione del bottone
byte Click_N = 0;      // Numero di clic effettuati

unsigned long PressioneDurata = 0;    // Tempo (ms) in cui il tasto è stato premuto e poi rilasciato
unsigned long PressioneInizio = 0;    // Tempo (ms) in cui il tasto è stato premuto
unsigned long PressioneRilascio = 0;  // Tempo (ms) in cui il tasto è stato rilasciato


//
void setup() {
  Serial.begin(115200);
  pinMode(Pin_Btn, INPUT);  // Imposta il Pin digitali come ingresso

  //Display
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(3, 0);
  display.println("MastrMarco");
  display.display();
  delay(1250);
}


//
void loop() {


  // Delay virtuale
  if (millis() >= (tempoM + Pressione_Corta)) {
    tempoM = millis();

    // legge lo sato del Pin
    BtnSato = digitalRead(Pin_Btn);

    //Verifica se e stata effettuata una pressione
    if (BtnSato == HIGH && PreBtnStato == false) {

      Click_N++;
      PressioneInizio = millis();
      PreBtnStato = true;

      //Verifica se e stata effettuata un rilascio del bottone
    } else if (BtnSato == LOW and PreBtnStato == true) {
      PressioneRilascio = millis();
      PressioneDurata = (PressioneRilascio - PressioneInizio);
      PreBtnStato = false;
    }
  }

  // Funzione Clic singolo o miltiplo
  if ((PressioneDurata < Pressione_Lunga) and (millis() > (PressioneRilascio + Intervallo_Pressione)) and (PreBtnStato == false)) {
    if (Click_N == 1) {  //
      Serial.println("Pressione Singola");
      Set = "Pressione Singola";
      Click_N = 0;
      PressioneDurata = 0;
    } else if (Click_N == 2) {  //
      Serial.println((String) "Pressione Doppia " + Click_N);
      Set = ((String) "Pressione Doppia " + Click_N);
      Click_N = 0;
      PressioneDurata = 0;
    } else if (Click_N > 2) {  //
      Serial.println((String) "Pressione Multipla " + Click_N);
      Set = ((String) "Pressione Multipla " + Click_N);
      Click_N = 0;
      PressioneDurata = 0;
    }

    // Funzione Clic Lungo o Nullo
  } else if ((PressioneDurata >= Pressione_Lunga) and (PreBtnStato == false)) {
    if ((Click_N == 1) and (PressioneDurata < +2000)) {  //
      Serial.println("Pressione Lunga");
      Set = "Pressione Lunga";
      Click_N = 0;
      PressioneDurata = 0;
    } else if ((Click_N > 1) or (PressioneDurata > 2000)) {  //
      Serial.println("Pressione Nulla");
      Set = "Pressione Nulla";
      Click_N = 0;
      PressioneDurata = 0;
    }
  }


  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(Set);
  display.display();
}
