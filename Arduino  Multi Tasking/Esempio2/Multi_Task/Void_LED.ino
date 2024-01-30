
void LEDControllerTask(void *parms) {

  Strip.begin();
  Strip.show();
  Strip.setBrightness(50);

  while (true) {


    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
      for (int i = 0; i < Strip.numPixels(); i++) {
        int pixelHue = firstPixelHue + (i * 65536L / Strip.numPixels());
        Strip.setPixelColor(i, Strip.gamma32(Strip.ColorHSV(pixelHue)));
      }
      Strip.show();
      // delay(10);
     vTaskDelay(10 / portTICK_PERIOD_MS);

    }

  }
}