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
        setLEDs();
        //updateLEDs();
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

void setLEDBrightness() {
  if (lowPwrMode == true) {
    if (rgbBrightness > 50) {
      FastLED.setBrightness(50);
    } else {
      FastLED.setBrightness(rgbBrightness);
    }
  } else {
    FastLED.setBrightness(rgbBrightness);
  }
  
}
/* Light Colour Options */

//Red
void lightCol1(int i){     
  leds[i] = CRGB(255, 0, 0);
}

//Green
void lightCol2(int i) {
  leds[i] = CRGB(0, 255, 0);
}

//Blue
void lightCol3(int i) {
  leds[i] = CRGB(0, 0, 255);
}

//Pink
void lightCol4(int i) {
  leds[i] = CRGB::Pink;
}

//Purple
void lightCol5(int i) {
  leds[i] = CRGB::Purple;
}

//Orange
void lightCol6(int i) {
  leds[i] = CRGB::Orange;
}

//Yellow
void lightCol7(int i) {
  leds[i] = CRGB::Yellow;
}

//lightBlue
void lightCol8(int i) {
  leds[i] = CRGB::LightSteelBlue;
}

//Rainbow
void lightCol9(int i) {
  static uint8_t hue = 0;
  leds[i] = CHSV(hue, 255, 255);
  hue += 5;
}

typedef void (*ColFunctionPointer)(int);
ColFunctionPointer lightCol[] = { lightCol1, lightCol2, lightCol3, lightCol4, lightCol5, lightCol6, lightCol7, lightCol8, lightCol9  };

/* Lighting Modes */

//Solid Colour
void lightMode1() {
  for (int i = 0; i < NUM_LEDS; i++) {
    lightCol[rgbColour](i);;
  }
}

//Flow hue
void lightMode2() {
  static uint8_t hue = 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + i * 10, 255, 255); 
  }

  hue += 1;
}


void lightMode3() {

}


void lightMode4() {

}


void lightMode5(){ 

}

typedef void (*ModeFunctionPointer)();
ModeFunctionPointer lightMode[] = { lightMode1, lightMode2, lightMode3, lightMode4, lightMode5  };


void setLEDs() {
  lightMode[rgbEffect]();;

  FastLED.show();
}