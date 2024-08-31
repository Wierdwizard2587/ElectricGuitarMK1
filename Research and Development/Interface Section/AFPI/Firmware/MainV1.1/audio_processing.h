#ifndef AUDIO_PROCESSING_H
#define AUDIO_PROCESSING_H

#include "config.h"

// Declare audio objects
extern AudioInputI2S            i2s1_in;
extern AudioEffectWaveshaper    waveshape1; 
extern AudioMixer4              distort_sw;
extern AudioEffectFlange        flange;
extern AudioMixer4              flange_sw;
extern AudioEffectChorus        chorus;
extern AudioMixer4              chorus_sw;
extern AudioEffectFreeverb      freeverb;
extern AudioMixer4              reverb_sw;
extern AudioEffectDelay         delay1;
extern AudioMixer4              delay_sw;
extern AudioMixer4              master_mix;
extern AudioOutputI2S           i2s2_out;
extern AudioControlSGTL5000     audioShield;

// Declare audio connections
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;

// Other global variables
extern const int inputChSelect;
extern const int chipSelect;




void initialiseAudio();
void initialiseDistortion();
void determineAudioOutput();


#endif