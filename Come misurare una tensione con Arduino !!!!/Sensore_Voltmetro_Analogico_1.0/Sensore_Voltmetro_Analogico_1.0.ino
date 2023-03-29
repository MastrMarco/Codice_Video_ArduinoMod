//*****************************************************************************************************************************//
//-------------------          By  MastrMarco    Versione 1.0        ISCRIVITI AL CANALE YOUTUBE       ------------------------//
//
//                                  https://www.youtube.com/channel/UCpQb1Iz6M229ylkyXpdJPlw
//*****************************************************************************************************************************//
//------------------------------------- 1°Code
/*
#include <Wire.h>
int datiS;
int Volt;

void setup(){

Serial.begin(9600);
Serial.println("MastrMarco");
Serial.print("DC VOLTMETRO");
Serial.print("V");
}
void loop(){
float temp;
datiS=analogRead(0);
temp=datiS/4.092;
datiS=(int)temp;
Volt=((datiS%100)/10);
Serial.println(Volt);
delay(1000);
}

//------------------------------------- 2°Code

#include <Wire.h>
int datiS;
float Volt;

void setup(){
Serial.begin(9600);
Serial.println("MastrMarco");
Serial.print("DC VOLTMETRO");
Serial.print("V");
}

void loop(){
float temp;
datiS=analogRead(0);
temp=datiS/4.425;
Volt=(temp/10);
Serial.println(Volt);
delay(1000);
}
*/
//------------------------------------- 3°Code
int analogInput = A0;
float Con = 0.0;
float Volt = 0.0;
float R1 = 29900.0; //  
float R2 = 7480.0; // 
int datiS = 0;
void setup(){
   pinMode(analogInput, INPUT);
   Serial.begin(9600);
   Serial.println("MastrMarco");
   Serial.print("DC VOLTMETRO");
}
void loop(){
   // leggere il valore sull'ingresso analogico 
   datiS = analogRead(analogInput);
   Con = (datiS * 4.60 ) / 1010.0;
   Volt = Con / (R2/(R1+R2)); 
   
Serial.print("INPUT V= ");
Serial.println(Volt,2);
delay(500);
}
