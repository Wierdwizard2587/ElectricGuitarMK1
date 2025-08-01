#include "config.h"

#include "SD_card.h"
#include "audio_processing.h"
#include "display.h"
#include "rotary_encoder_ctrl.h"
#include "home_button.h"
#include "RGB_processing.h"
#include "low_pwr_mode.h"

#include "landing_page.h"
#include "settings_page.h"
#include "RGB_page.h"
#include "aux_pages.h"
#include "FX_pages.h"
#include "EQ_page.h"

void setup() {
  //Serial.begin(115200);
  //while (!Serial) delay(10);
  initializeDisplay();
  initialiseSDCard();
  initialiseAudio();
  //initialiseDistortion();
  pinMode(buttonPin, INPUT_PULLUP);
  Wire1.begin();
  initializeEncoders();
  initialiseRGB();
  lowPwrModeHandle();
}

void loop() {
  landingPage();
}