float rx, v1 = 0;
float r1 = 914; //1kohm resistenza nota

void setup(){
   Serial.begin(9600);
   Serial.println("MastrMarco");
   Serial.print("DC VOLTMETRO");
}
void loop(){
  int n = analogRead(A1); 
  
  v1 = map(n, 0, 1024, 0, 5080)/1000.0; //mV
  rx = (r1*(5.08-v1)) / v1;
  
  Serial.print(v1);
  Serial.print("\t");
  Serial.println(rx);
  
  delay(200);
  
}
