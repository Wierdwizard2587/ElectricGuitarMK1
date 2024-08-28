#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

// Display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Declare the display object
extern Adafruit_SSD1306 display;

// Declare the bitmaps
extern const unsigned char PROGMEM logo_bmp[];
extern const uint8_t bitmap37[];

// Function declarations
void initializeDisplay();
void testLoadingScreen();
void setFXTemplatePage(char title[], bool& FXActive, bool fxCheck);

#endif