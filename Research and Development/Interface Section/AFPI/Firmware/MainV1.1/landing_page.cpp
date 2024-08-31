#include "landing_page.h"

#include "config.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"


#include "settings_page.h"
#include "RGB_page.h"
#include "aux_pages.h"
#include "FX_pages.h"
#include "EQ_page.h"

void landingPage() { 
  hoverOptionSelector();

  bool choosing = true;

  
  resetScreenSaver();
  while (choosing == true) {
    checkScreenTime();
    int EncRes;
    //current option Control Encoder Check
    param = currentHoverOption;
    EncRes = EncDialCheck(3, param, 4.0, 0.0);
    if (EncRes == 2) {
      currentHoverOption++;
      hoverOptionSelector();
    } 
    if (EncRes == 1) {
      currentHoverOption--;
      hoverOptionSelector();
    }
    
    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      choosing = false;
      resetScreenSaver();
    }
  }

  landingFunctions[currentHoverOption]();;
}

void hoverOptionSelector() {
    display.clearDisplay();
    setLandingPage();
    if (currentHoverOption == 0){
      display.drawCircle(12, 30, 9, 1);
    }
    if (currentHoverOption == 1){
      display.drawCircle(38, 30, 9, 1);
    }
    if (currentHoverOption == 2){
      display.drawCircle(64, 30, 9, 1);
    }
    if (currentHoverOption == 3){
      display.drawCircle(90, 30, 9, 1);
    }
    if (currentHoverOption == 4){
      display.drawCircle(115, 30, 9, 1);
    }
    display.display();
}

typedef void (*FunctionPointer)();
FunctionPointer landingFunctions[] = { FXMainPage, EQPage, audioPage, RGBPage, settingsPage };

void setLandingPage() {
    display.clearDisplay();
    display.setCursor(16, 10);
    display.setFont(NULL);
    display.setTextWrap(0);
    display.setCursor(28, 10);
    display.println("Expeditioner");
    display.setCursor(0, 10);
    display.drawLine(0, 20, 128, 20, 1);
    display.drawRect(0, 20, 25, 44, 1);
    display.drawRect(26, 20, 25, 44, 1);
    display.drawRect(52, 20, 25, 44, 1);
    display.drawRect(78, 20, 25, 44, 1);
    display.drawRect(104, 20, 24, 44, 1);
    display.setCursor(7, 50);
    display.print("FX");
    display.setCursor(33, 50);
    display.print("EQ");
    display.setCursor(56, 50);
    display.print("Aux");
    display.setCursor(82, 50);
    display.print("RGB");
    display.setCursor(107, 50);
    display.print("Set");
    display.fillCircle(12, 30, 5, 1);
    display.fillCircle(38, 30, 5, 1);
    display.fillCircle(64, 30, 5, 1);
    display.fillCircle(90, 30, 5, 1);
    display.fillCircle(115, 30, 5, 1);
    display.drawBitmap(105, -2, bitmap37, 24, 24, 1);
    display.display();
}