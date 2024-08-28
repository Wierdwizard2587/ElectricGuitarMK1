#include "settings_page.h"

#include "config.h"
#include "display.h"
void settingsPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }

  while (true) {
    char title[] = {"Settings"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();
    checkHomeButton();
  }
}