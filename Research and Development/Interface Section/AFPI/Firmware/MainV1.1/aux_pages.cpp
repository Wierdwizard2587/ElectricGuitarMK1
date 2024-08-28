#include "aux_pages.h"


#include "config.h"
#include "audio_processing.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"
#include "home_button.h"

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