#include <Adafruit_NeoPixel.h>

#define LED_COUNT 63
#define LED_PIN 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(9600);

  strip.begin();
  strip.show();
  strip.setBrightness(50);
}


void loop() {

  // LED
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(10);
  }


  // Seriale
  Serial.println((String) "255" + "  " + "MastrMarco" + "  " + "5" + "255" + "  " + "MastrMarco" + "  " + "5");
}
