#include "low_pwr_mode.h"



#include "config.h"

#include "display.h"
#include "RGB_processing.h"

void lowPwrModeHandle() {


  //Display settings

  //1. OLED Contrast
  setOLEDContrast(oledContrast);

  //2. Screen saver timer
  resetScreenSaver();
  setSaverInterval();

  //3. refresh Rate


  //LED settings

  //1. LED Brightness
  setLEDBrightness();

  //2. LED update interval timer


  //Processor/Teensy speed settings

  //1. Processor Speed

  //2. peripheral input checking interval timer


  //Audio settings

  //1. speaker volume


}