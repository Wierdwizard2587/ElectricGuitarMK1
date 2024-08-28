#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
void setOLEDContrast(uint8_t contrast);
void checkScreenTime();
void screenSaverActive();
void resetScreenSaver();
bool checkActivity();


#endif