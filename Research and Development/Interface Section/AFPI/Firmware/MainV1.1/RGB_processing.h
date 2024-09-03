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
#endif