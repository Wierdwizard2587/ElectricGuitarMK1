#include "RGB_processing.h"

#include <FastLED.h>

#include "config.h"

CRGB leds[NUM_LEDS];

const unsigned long LED_UPDATE_INTERVAL = 20; 
unsigned long lastUpdate = 0;

void initialiseRGB() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(rgbBrightness);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}


void checkRGBinterval() {
  if (rgbActive == true) {
      unsigned long currentTime = millis();
      if (currentTime - lastUpdate >= LED_UPDATE_INTERVAL) {
        lastUpdate = currentTime;
        updateLEDs();
      }
  }
}

void updateLEDs() {
  static uint8_t hue = 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + i * 10, 255, 255); 
  }

  hue += 1;

  FastLED.show();
}

void RGBoff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
  rgbActive = false;
}