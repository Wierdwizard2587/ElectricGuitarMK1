#ifndef RGB_PROCESSING_H
#define RGB_PROCESSING_H

#include <FastLED.h>
#include "config.h"

#define LED_PIN     2     // Pin connected to the data line of the LEDs
#define NUM_LEDS    6    // Number of LEDs in your strip
//#define BRIGHTNESS  50    // Set brightness (0-255)

extern CRGB leds[NUM_LEDS];

extern const unsigned long LED_UPDATE_INTERVAL;
extern unsigned long lastUpdate;

void initialiseRGB();
void checkRGBinterval();
void updateLEDs();
void RGBoff();

void setLEDBrightness();

void setLEDs();

void lightMode1();
void lightMode2();
void lightMode3();
void lightMode4();
void lightMode5();

void lightCol1(int i);
void lightCol2(int i);
void lightCol3(int i);
void lightCol4(int i);
void lightCol5(int i);
void lightCol6(int i);
void lightCol7(int i);
void lightCol8(int i);
void lightCol9(int i);
#endif