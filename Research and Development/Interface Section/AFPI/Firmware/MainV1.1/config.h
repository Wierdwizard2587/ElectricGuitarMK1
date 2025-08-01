#ifndef CONFIG_H
#define CONFIG_H


#include <Arduino.h>
#include <Audio.h>

#include <Wire.h>
#include <SPI.h>

#include <SD.h>
#include <SerialFlash.h>


//General FX Variables
extern int currentEffect;
extern float param;
extern int fxEncRes;

//Audio section Variables
extern int currentAuxPage;
extern int currentAudioOutput;

//landing page Variables
extern int currentHoverOption;


extern float lineMix;
extern float backingMix;
extern bool backingActive;
extern float HPVol;
extern float SPVol;
extern float AUXVol;
extern bool EQActive;
extern float bassBand;
extern float midBassBand;
extern float midRangeBand;
extern float midTrebleBand;
extern float trebleBand;
extern bool bassBoostActive;
extern float lr_lev;
extern float bass_lev;
extern int hpf_bypass;
extern int cutoff;
extern bool rgbActive;
extern int rgbBrightness;
extern int rgbColour;
extern int rgbEffect;
extern int auxOutOpt;
extern int currentEQPage;



// audio shield volume
extern int HPGainOut;

extern int SPGainOut;
extern int AuxGainOut;
extern bool distortActive;
#define MAX_ORDER 2
extern float alpha[MAX_ORDER - 1]; // First entry is second-order
extern float waveshape[32769];

#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
extern short flange_delayline[];
extern int s_idx;
extern int s_depth;
extern double s_freq;
extern bool flangeActive;


#define chorusDelayLength (16*AUDIO_BLOCK_SAMPLES)  // Number of samples in each delay line
extern short l_delayline[]; // Allocate the delay lines for left and right channels
extern int   n_chorus;                   // number of "voices" in the chorus including the original voice
extern bool chorusActive;  

extern bool reverbActive;
extern float revRoomsize;
extern float revDamping;

extern bool delayActive;
extern int delayTime;


extern uint8_t oledContrast;

extern unsigned long previousMillis; 
extern const unsigned long interval;
extern bool lowPwrMode;
#endif