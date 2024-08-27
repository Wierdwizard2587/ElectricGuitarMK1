#include "config.h"
#include "SD_card.h"
#include "audio_processing.h"
#include "display.h"
#include "rotary_encoder_ctrl.h"
#include "home_button.h"
#include "landing_page.h"
//============================new setup code above================================


void setup() {
  //Serial.begin(115200);
  //while (!Serial) delay(10);
  initializeDisplay();
  initialiseSDCard();
  pinMode(buttonPin, INPUT_PULLUP);
  Wire1.begin();
  initializeEncoders();
}

void loop() {
  landingPage();
}

typedef void (*FunctionPointer)();
FunctionPointer landingFunctions[] = { FXMainPage, EQPage, audioPage, RGBPage, settingsPage };

void landingPage() { 
  hoverOptionSelector();

  bool choosing = true;

  while (choosing == true) {
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


void RGBPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  while (true) {
    char title[] = {"RGB Lighting"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();
    checkHomeButton();
  }
}

void masterAuxPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  currentAuxPage = 0;
  while (true) {
    char title[] = {"Aux #1 Master Vol"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);
    display.setCursor(1, 20);
    display.print("MasVol:");
    display.setCursor(10, 35);
    display.println(masterVolume);
    display.setCursor(55, 20);
    display.print("Gain:");
    display.setCursor(60, 35);
    display.println(gainOut);
    display.setCursor(80, 20);
    display.print("Out:");
    display.setCursor(90, 35);
    display.println(currentAudioOutput);
    display.display();

    checkHomeButton();

    //Master volume Control Encoder Check
    int EncRes;
    param = masterVolume;
    EncRes = EncDialCheck(0, param, 1.0, 0.0);
    if (EncRes == 2) {
      masterVolume = masterVolume + 0.05;
      audioShield.volume(masterVolume);
    } 
    if (EncRes == 1) {
      masterVolume = masterVolume - 0.05;
      audioShield.volume(masterVolume);
    }
    //Master Gain out Control Encoder Check
    param = gainOut;
    EncRes = EncDialCheck(1, param, 31, 13);
    if (EncRes == 2) {
      gainOut = gainOut + 1;
      audioShield.lineOutLevel(gainOut);
    } 
    if (EncRes == 1) {
      gainOut = gainOut - 1;
      audioShield.lineOutLevel(gainOut);
    }
    //audioShield.dacVolume(0.0, 0.0);
    //audio output selection, 0 = speaker, 1 = headphones, 2 = aux out
    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      if (currentAudioOutput == 2){ //switch to speaker, next change will be hp
          currentAudioOutput = 0;

          audioShield.lineOutLevel(13, 31);
          audioShield.dacVolume(1.0, 0.05);

      } else if (currentAudioOutput == 0){ // switch to hp, next change will be aux out
          currentAudioOutput = 1;
          audioShield.unmuteHeadphone();
          audioShield.muteLineout();

          audioShield.dacVolume(1.0, 1.0);

      } else if (currentAudioOutput == 1){ // switch to aux out, next change will be speaker
          currentAudioOutput = 2;
          audioShield.muteHeadphone();
          audioShield.unmuteLineout();
          //audioShield.lineOutLevel(31, 13);
          audioShield.dacVolume(0.05, 1.0);
      }
    }

    while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
    }


    cycleAux(3, currentAuxPage, 1.0, 0.0);//Check FX selected change 
    
  }
}


void backTrackAuxPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  currentAuxPage = 1;
  while (true) {
    char title[] = {"Aux #2 Back Track"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);
    display.setCursor(1, 20);
    display.print("Line Mx:");
    display.setCursor(10, 35);
    display.println(lineMix);
    display.setCursor(55, 20);
    display.print("Back Mx:");
    display.setCursor(60, 35);
    display.println(backingMix);
    display.display();

    checkHomeButton();

    //Master volume Control Encoder Check
    int EncRes;
    param = lineMix;
    EncRes = EncDialCheck(0, param, 3.0, 0.0);
    if (EncRes == 2) {
      lineMix = lineMix + 0.05;
      master_mix.gain(1, lineMix);
    } 
    if (EncRes == 1) {
      lineMix = lineMix - 0.05;
      master_mix.gain(1, lineMix);
    }
    //Master Gain out Control Encoder Check
    param = backingMix;
    EncRes = EncDialCheck(1, param, 3.0, 0.0);
    if (EncRes == 2) {
      backingMix = backingMix + 0.05;
      master_mix.gain(0, backingMix);
    } 
    if (EncRes == 1) {
      backingMix = backingMix - 0.05;
      master_mix.gain(0, backingMix);
    }

    cycleAux(3, currentAuxPage, 1.0, 0.0);//Check Aux selected change 
    
  }
}
typedef void (*FunctionPointer)();
FunctionPointer auxFunctions[] = { masterAuxPage, backTrackAuxPage  };

void audioPage() {
    while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }
  auxFunctions[currentAuxPage]();;
}

void cycleAux(int encNo, int param, int maxRange, int minRange) {
    int EncRes;
    EncRes = EncDialCheck(encNo, param, maxRange, minRange);
    if (EncRes == 2) {
        auxFunctions[param + 1]();;
    } 
    if (EncRes == 1) {
        auxFunctions[param - 1]();;
    }  
}

void EQPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  while (true) {
    char title[] = {"EQ"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();
    checkHomeButton();
  }
}

void flangeFX() {
    currentEffect = 0;
    while (true) {
        char title[] = {"FX #1 Flange"};
        setFXTemplatePage(title, flangeActive, true);
        display.setCursor(10, 20);
        display.print("Freq:");
        display.setCursor(24, 35);
        display.println(s_freq);
        display.display();

        checkHomeButton();
        //flange Freq Control Encoder Check
        param = s_freq;
        fxEncRes = EncDialCheck(0, param, 5.0, 0.0);
        if (fxEncRes == 2) {
          s_freq = s_freq + 0.1;
          flange.voices(s_idx,s_depth,s_freq);
        } 
        if (fxEncRes == 1) {
          s_freq = s_freq - 0.1;
          flange.voices(s_idx,s_depth,s_freq);
        } 
        //Check flange FX active Toggle
        EncToggleCheck(flangeActive, flange_sw);
        //Check FX selected change 
        cycleFX(3, currentEffect, 3.0, 0.0);
    }
}

void chorusFX() {
    currentEffect = 1;
    while (true) {
        char title[] = {"FX #2 Chorus"};
        setFXTemplatePage(title, chorusActive, true);
        
        display.setCursor(10, 20);
        display.print("Voices:");
        display.setCursor(24, 35);
        display.println(n_chorus);

        display.display();
        checkHomeButton();
        //chorus Voice amount Control Encoder Check
        param = n_chorus;
        fxEncRes = EncDialCheck(0, param, 16, 2);
        if (fxEncRes == 2) {
          n_chorus++;
          chorus.voices(n_chorus);
        } 
        if (fxEncRes == 1) {
          n_chorus--;
          chorus.voices(n_chorus);
        }
        
        EncToggleCheck(chorusActive, chorus_sw); //Check Chorus FX active Toggle
        cycleFX(3, currentEffect, 3.0, 0.0); //Check FX selected change 
    }
}

void reverbFX() {
    currentEffect = 2;
    while (true) {
        char title[] = {"FX #3 Reverb"};
        setFXTemplatePage(title, reverbActive, true);
        display.setCursor(1, 20);
        display.print("RoomSize:");
        display.setCursor(15, 35);
        display.println(revRoomsize);
        display.setCursor(55, 20);
        display.print("Damping:");
        display.setCursor(65, 35);
        display.println(revDamping);

        display.display();
        checkHomeButton();

        //Reverb Room Size Control Encoder Check
        param = revRoomsize;
        fxEncRes = EncDialCheck(0, param, 1.0, 0.0);
        if (fxEncRes == 2) {
          revRoomsize = revRoomsize + 0.05;
          freeverb.roomsize(revRoomsize);
          //storeVarsToUpdate("revRoomsize", String(revRoomsize));
        } 
        if (fxEncRes == 1) {
          revRoomsize = revRoomsize - 0.05;
          freeverb.roomsize(revRoomsize);
          //storeVarsToUpdate("revRoomsize", String(revRoomsize));
        }
        

        //Reverb Damping Control Encoder Check
        param = revDamping;
        fxEncRes = EncDialCheck(1, param, 1.0, 0.0);
        if (fxEncRes == 2) {
          revDamping = revDamping + 0.05;
          freeverb.damping(revDamping);
        } 
        if (fxEncRes == 1) {
          revDamping = revDamping - 0.05;
          freeverb.damping(revDamping);
        }
        
        EncToggleCheck(reverbActive, reverb_sw);//Check reverb FX active Toggle
        cycleFX(3, currentEffect, 3.0, 0.0);//Check FX selected change 
    }
}


void delayFX() {
    currentEffect = 3;
    while (true) {
        char title[] = {"FX #4 Delay"};
        setFXTemplatePage(title, delayActive, true);
        display.setCursor(10, 20);
        display.print("Time Ms:");
        display.setCursor(24, 35);
        display.println(delayTime);
        display.display();
        
        checkHomeButton();
        //Delay time Control Encoder Check
        param = delayTime;
        fxEncRes = EncDialCheck(0, param, 1000, 0);
        if (fxEncRes == 2) {
          delayTime = delayTime + 50;
          delay1.delay(0, delayTime);
          //runFileUpdate("delayTime", String(delayTime));
        } 
        if (fxEncRes == 1) {
          delayTime = delayTime - 50;
          delay1.delay(0, delayTime);
          //runFileUpdate("delayTime", String(delayTime));
        }
        

        EncToggleCheck(delayActive, delay_sw); //Check delay FX active Toggle
        delay_sw.gain(0, 1);
         
        cycleFX(3, currentEffect, 3.0, 0.0);//Check FX selected change
    }
}

typedef void (*FunctionPointer)();
FunctionPointer FXfunctions[] = { flangeFX, chorusFX, reverbFX, delayFX  };

void checkHomeButton() {
  int buttonState = digitalRead(buttonPin); 
  if (buttonState == LOW) {

    writeUpdatedValues();
    
    delay(500); 
    landingPage();
  }
}

int EncDialCheck(int encNo, float paramValue, float maxRange, float minRange) {
    int32_t enc_pos = ss.getEncoderPosition(encNo);
    if (enc_positions[0] != enc_pos) {
        int change = enc_pos - enc_positions[encNo];
        enc_positions[encNo] = enc_pos;

        if (change > 0 && paramValue < maxRange) {
            return 2;
        } else if (change < 0 && paramValue > minRange) {
            return 1;
        }
    }
    return 0;
}

void EncToggleCheck(bool& FXActive, AudioMixer4& mixer_sw) {
    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
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

void cycleFX(int encNo, int param, int maxRange, int minRange) {
    int EncRes;
    EncRes = EncDialCheck(encNo, param, maxRange, minRange);
    if (EncRes == 2) {
        FXfunctions[param + 1]();;
    } 
    if (EncRes == 1) {
        FXfunctions[param - 1]();;
    }  
}

void FXMainPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }
  FXfunctions[currentEffect]();;

}


void setLandingPage() {
    display.clearDisplay();
    display.setCursor(16, 10);
    display.setFont(NULL);
    display.setTextWrap(0);
    display.setCursor(28, 10);
    display.println("Expiditioner");
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

const uint8_t bitmap21[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0xff, 0xff, 0xf0, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void setFXTemplatePage(char title[], bool& FXActive, bool fxCheck) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont(NULL);
  display.setCursor(0, 10);
  display.setCursor(0, 5);
  display.setTextWrap(0);
  display.setCursor(28, 5);
  display.println(title);
  display.drawLine(0, 18, 128, 18, 1);
  display.drawRect(109, 50, 17, 12, 1);
  display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
  display.drawRect(2, 50, 17, 12, 1);
  display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
  display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
  display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
  display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
  if (fxCheck) {
    if (FXActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
  }
}