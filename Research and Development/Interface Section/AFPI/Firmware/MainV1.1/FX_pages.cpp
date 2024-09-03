#include "FX_pages.h"

#include "config.h"
#include "audio_processing.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"
#include "home_button.h"
#include "RGB_processing.h"

void distortFX() {
    currentEffect = 0;
    while (true) {
        char title[] = {"FX #1 Distort"};
        setFXTemplatePage(title, distortActive, true);
        display.setCursor(1, 20);
        display.print("val:");
        display.setCursor(15, 35);
        display.println("val");
        display.setCursor(55, 20);
        display.print("val:");
        display.setCursor(65, 35);
        display.println("val");

        display.display();

        checkRGBinterval();

        checkScreenTime();

        checkHomeButton();

        //Reverb Room Size Control Encoder Check
        // param = revRoomsize;
        // fxEncRes = EncDialCheck(0, param, 1.0, 0.0);
        // if (fxEncRes == 2) {
        //   revRoomsize = revRoomsize + 0.05;
        //   freeverb.roomsize(revRoomsize);
        //   //storeVarsToUpdate("revRoomsize", String(revRoomsize));
        // } 
        // if (fxEncRes == 1) {
        //   revRoomsize = revRoomsize - 0.05;
        //   freeverb.roomsize(revRoomsize);
        //   //storeVarsToUpdate("revRoomsize", String(revRoomsize));
        // }
        

        //Reverb Damping Control Encoder Check
        // param = revDamping;
        // fxEncRes = EncDialCheck(1, param, 1.0, 0.0);
        // if (fxEncRes == 2) {
        //   revDamping = revDamping + 0.05;
        //   freeverb.damping(revDamping);
        // } 
        // if (fxEncRes == 1) {
        //   revDamping = revDamping - 0.05;
        //   freeverb.damping(revDamping);
        // }
        
        EncToggleCheck(distortActive, distort_sw);//Check distortion FX active Toggle
        cycleFX(3, currentEffect, 4.0, 0.0);//Check FX selected change 
    }
}


void flangeFX() {
    currentEffect = 1;
    while (true) {
        char title[] = {"FX #2 Flange"};
        setFXTemplatePage(title, flangeActive, true);
        display.setCursor(10, 20);
        display.print("Freq:");
        display.setCursor(24, 35);
        display.println(s_freq);
        display.display();

        checkRGBinterval();

        checkScreenTime();

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
        cycleFX(3, currentEffect, 4.0, 0.0);
    }
}

void chorusFX() {
    currentEffect = 2;
    while (true) {
        char title[] = {"FX #3 Chorus"};
        setFXTemplatePage(title, chorusActive, true);
        
        display.setCursor(10, 20);
        display.print("Voices:");
        display.setCursor(24, 35);
        display.println(n_chorus);

        display.display();

        checkRGBinterval();

        checkScreenTime();

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
        cycleFX(3, currentEffect, 4.0, 0.0); //Check FX selected change 
    }
}

void reverbFX() {
    currentEffect = 3;
    while (true) {
        char title[] = {"FX #4 Reverb"};
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

        checkRGBinterval();

        checkScreenTime();

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
        cycleFX(3, currentEffect, 4.0, 0.0);//Check FX selected change 
    }
}


void delayFX() {
    currentEffect = 4;
    while (true) {
        char title[] = {"FX #5 Delay"};
        setFXTemplatePage(title, delayActive, true);
        display.setCursor(10, 20);
        display.print("Time Ms:");
        display.setCursor(24, 35);
        display.println(delayTime);
        display.display();
        
        checkRGBinterval();

        checkScreenTime();
        
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
         
        cycleFX(3, currentEffect, 4.0, 0.0);//Check FX selected change
    }
}

typedef void (*FunctionPointer)();
FunctionPointer FXfunctions[] = { distortFX, flangeFX, chorusFX, reverbFX, delayFX  };





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