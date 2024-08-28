#include "config.h"

#include "landing_page.h"


//General FX Variables
int currentEffect;
float param;
int fxEncRes;

//Audio section Variables
int currentAuxPage;
int currentAudioOutput;

//landing page Variables
int currentHoverOption = 0;


float lineMix;
float backingMix;
float HPVol;
float SPVol;
float AUXVol;
bool EQActive = false;
float bassBand;
float midBassBand;
float midRangeBand;
float midTrebleBand;
float trebleBand;
bool bassBoostActive = false;
float lr_lev;
float bass_lev;
int hpf_bypass;
int cutoff;
bool rgbActive = false;
float rgbBrightness;
int auxOutOpt;
int currentEQPage;
float screenBrightness;


// audio shield volume
float masterVolume  = 0.0;
int gainOut = 13;


//#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short flange_delayline[FLANGE_DELAY_LENGTH];
int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;
bool flangeActive;


//#define chorusDelayLength (16*AUDIO_BLOCK_SAMPLES)  // Number of samples in each delay line
short l_delayline[chorusDelayLength]; // Allocate the delay lines for left and right channels
int   n_chorus = 2;                   // number of "voices" in the chorus including the original voice
bool chorusActive;  

bool reverbActive;
float revRoomsize = 0.0;
float revDamping = 0.0;

bool delayActive;
int delayTime = 0;

uint8_t oledContrast = 255;

unsigned long previousMillis = 0; // Stores the last time the timer was checked
const unsigned long interval = 10000; // 10-second interval in milliseconds
bool lowPwrMode = false;