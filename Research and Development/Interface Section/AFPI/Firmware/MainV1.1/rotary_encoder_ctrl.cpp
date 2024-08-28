#include "rotary_encoder_ctrl.h"

#include "config.h"
#include "display.h"

// Object definitions
Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);
seesaw_NeoPixel pixels = seesaw_NeoPixel(4, SS_NEO_PIN, NEO_GRB + NEO_KHZ800, &Wire1);

// Encoder positions array
int32_t enc_positions[4] = {0, 0, 0, 0};

void initializeEncoders() {
    // Initialize the seesaw and NeoPixel
    if (!ss.begin(SEESAW_ADDR) || !pixels.begin(SEESAW_ADDR)) {
        while (1) delay(10); // Halt if initialization fails
    }

    // Verify the firmware version
    uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
    if (version != 5752) {
        while (1) delay(10); // Halt if the wrong firmware is loaded
    }

    // Configure encoder switch pins with pull-up resistors
    ss.pinMode(SS_ENC0_SWITCH, INPUT_PULLUP);
    ss.pinMode(SS_ENC1_SWITCH, INPUT_PULLUP);
    ss.pinMode(SS_ENC2_SWITCH, INPUT_PULLUP);
    ss.pinMode(SS_ENC3_SWITCH, INPUT_PULLUP);
    
    // Enable GPIO interrupts for the encoder switch pins
    ss.setGPIOInterrupts(1UL << SS_ENC0_SWITCH | 1UL << SS_ENC1_SWITCH | 
                         1UL << SS_ENC2_SWITCH | 1UL << SS_ENC3_SWITCH, 1);

    // Initialize encoder positions and enable encoder interrupts
    for (int e = 0; e < 4; e++) {
        enc_positions[e] = ss.getEncoderPosition(e);
        ss.enableEncoderInterrupt(e);
    }

    // Configure and initialize NeoPixel
    pixels.setBrightness(255);
    pixels.show();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

int EncDialCheck(int encNo, float paramValue, float maxRange, float minRange) {
    int32_t enc_pos = ss.getEncoderPosition(encNo);
    if (enc_positions[encNo] != enc_pos) {
        int change = enc_pos - enc_positions[encNo];
        enc_positions[encNo] = enc_pos;

        

        if (change < 0 && paramValue < maxRange) {
            resetScreenSaver();
            return 2;
        } else if (change > 0 && paramValue > minRange) {
            resetScreenSaver();
            return 1;
        }
    }
    return 0;
}

void EncToggleCheck(bool& FXActive, AudioMixer4& mixer_sw) {
    if (!ss.digitalRead(SS_ENC3_SWITCH)) {

      resetScreenSaver();

      if (FXActive == false){
          FXActive = true;
          mixer_sw.gain(0, 0);
          mixer_sw.gain(1, 1);
      }
      else {
          FXActive = false;
          mixer_sw.gain(0, 1);
          mixer_sw.gain(1, 0);
      }         
    }

    while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
    }
}
