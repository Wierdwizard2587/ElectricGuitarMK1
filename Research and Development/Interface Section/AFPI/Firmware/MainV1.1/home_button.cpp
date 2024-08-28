#include "home_button.h"

#include "config.h"
#include "landing_page.h"
#include "SD_card.h"
const int buttonPin = 14;

void checkHomeButton() {
  int buttonState = digitalRead(buttonPin); 
  if (buttonState == LOW) {

    writeUpdatedValues();
    
    delay(500); 
    landingPage();
  }
}