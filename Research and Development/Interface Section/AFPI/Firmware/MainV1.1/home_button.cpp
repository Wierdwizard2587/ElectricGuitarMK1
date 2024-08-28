#include "home_button.h"

#include "config.h"
#include "landing_page.h"
#include "SD_card.h"
#include "display.h"

const int buttonPin = 14;

void checkHomeButton() {
  int buttonState = digitalRead(buttonPin); 
  if (buttonState == LOW) {
    resetScreenSaver();
    writeUpdatedValues();
    
    delay(500); 
    landingPage();
  }
}

bool homeButtonActivity() {
  int buttonState = digitalRead(buttonPin); 
  if (buttonState == LOW) {
    delay(500); 
    return true;
  } else {
    return false;
  }
}