#include "EQ_page.h"

#include "config.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"
#include "home_button.h"
#include "RGB_processing.h"
void EQPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  while (true) {
    char title[] = {"EQ"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();

    checkRGBinterval();
    
    checkScreenTime();

    
    checkHomeButton();
  }
}