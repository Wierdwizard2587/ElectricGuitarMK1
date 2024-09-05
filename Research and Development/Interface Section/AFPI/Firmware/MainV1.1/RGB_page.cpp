#include "RGB_page.h"


#include "config.h"
#include "RGB_processing.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"
#include "home_button.h"

void RGBPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  while (true) {
    char title[] = {"RGB Lighting"};

    setFXTemplatePage(title, rgbActive, true);
    
    display.setCursor(1, 20);
    display.print("brtns:");
    display.setCursor(6, 35);
    display.println(rgbBrightness);

    display.setCursor(35, 20);
    display.print("Col:");
    display.setCursor(40, 35);
    display.println(rgbColour);

    display.setCursor(70, 20);
    display.print("patrn:");
    display.setCursor(75, 35);
    display.println(rgbEffect);

    display.display();

    checkRGBinterval();

    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      if (rgbActive == false){
          rgbActive = true;
      }
      else {
          RGBoff();
      }
      while (!ss.digitalRead(SS_ENC3_SWITCH)) {
      delay(50);
      }
    }


    int EncRes;
    EncRes = EncDialCheck(0, rgbBrightness, 255, 5);
    if (EncRes == 2) {
      rgbBrightness = rgbBrightness + 5;
      setLEDBrightness();
    } 
    if (EncRes == 1) {
      rgbBrightness = rgbBrightness - 5;
      setLEDBrightness();
    }

    EncRes = EncDialCheck(1, rgbColour, 8, 0);
    if (EncRes == 2) {
      rgbColour = rgbColour + 1;
    } 
    if (EncRes == 1) {
      rgbColour = rgbColour - 1;
    }

    EncRes = EncDialCheck(2, rgbEffect, 4, 0);
    if (EncRes == 2) {
      rgbEffect = rgbEffect + 1;
    } 
    if (EncRes == 1) {
      rgbEffect = rgbEffect - 1;
    }

    checkScreenTime();
    
    checkHomeButton();
  }
}