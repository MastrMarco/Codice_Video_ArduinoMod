
void TaskSeriale(void *parms) {

  Serial.begin(9600);

  while (true) {


   Serial.println((String) "255" + "  " + "MastrMarco" + "  " + "5" + "255" + "  " + "MastrMarco" + "  " + "5");
    
    vTaskDelay(30 / portTICK_PERIOD_MS);


  }
}
