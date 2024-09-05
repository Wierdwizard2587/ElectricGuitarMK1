#include "settings_page.h"

#include "config.h"
#include "display.h"
#include "RGB_processing.h"
#include "low_pwr_mode.h"
void settingsPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }

  while (true) {
    char title[] = {"Settings"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);
    display.setCursor(1, 20);
    display.print("Brtnes:");
    display.setCursor(10, 35);
    display.println(oledContrast);
    display.setCursor(55, 20);
    display.print("loPwrmde:");
    display.setCursor(60, 35);
    if (lowPwrMode == true) {
      display.println("ON");
    } else {
      display.println("OFF");
    }
    
    display.display();

    checkRGBinterval();
    

    checkScreenTime();
    
    checkHomeButton();

    //OLED Brightness Control Encoder Check
    int EncRes;
    param = oledContrast;
    EncRes = EncDialCheck(0, param, 255, 0);
    if (EncRes == 2) {
      oledContrast = oledContrast + 5;
      setOLEDContrast(oledContrast);
    } 
    if (EncRes == 1) {
      oledContrast = oledContrast - 5;
      setOLEDContrast(oledContrast);
    }

    if (!ss.digitalRead(SS_ENC1_SWITCH)) {
      if (lowPwrMode == false){
          lowPwrMode = true;
          lowPwrModeHandle();
      }
      else {
          lowPwrMode = false;
          lowPwrModeHandle();
      }
      while (!ss.digitalRead(SS_ENC1_SWITCH)) {
      delay(50);
      }
    }

  }
}