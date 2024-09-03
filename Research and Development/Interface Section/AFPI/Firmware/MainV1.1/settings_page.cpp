#include "settings_page.h"

#include "config.h"
#include "display.h"
#include "RGB_processing.h"
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
    display.print("val:");
    display.setCursor(60, 35);
    display.println("val");
    display.display();


    

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
    // //Master Gain out Control Encoder Check
    // param = backingMix;
    // EncRes = EncDialCheck(1, param, 3.0, 0.0);
    // if (EncRes == 2) {
    //   backingMix = backingMix + 0.05;
    //   master_mix.gain(0, backingMix);
    // } 
    // if (EncRes == 1) {
    //   backingMix = backingMix - 0.05;
    //   master_mix.gain(0, backingMix);
    // }
  }
}