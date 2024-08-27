#include "audio_processing.h"

#include "config.h"

// Instantiate audio objects
AudioInputI2S            i2s1_in;
AudioEffectFlange        flange;
AudioMixer4              flange_sw;
AudioEffectChorus        chorus;
AudioMixer4              chorus_sw;
AudioEffectFreeverb      freeverb;
AudioMixer4              reverb_sw;
AudioEffectDelay         delay1;
AudioMixer4              delay_sw;
AudioMixer4              master_mix;
AudioOutputI2S           i2s2_out;
AudioControlSGTL5000     audioShield;

// Instantiate audio connections
AudioConnection          patchCord1(i2s1_in, 0, flange_sw, 0);
AudioConnection          patchCord2(i2s1_in, 0, flange, 0);
AudioConnection          patchCord3(flange, 0, flange_sw, 1);
AudioConnection          patchCord4(flange_sw, chorus);
AudioConnection          patchCord5(flange_sw, 0, chorus_sw, 0);
AudioConnection          patchCord6(chorus, 0, chorus_sw, 1);
AudioConnection          patchCord7(chorus_sw, freeverb);
AudioConnection          patchCord8(chorus_sw, 0, reverb_sw, 0);
AudioConnection          patchCord9(freeverb, 0, reverb_sw, 1);
AudioConnection          patchCord10(reverb_sw, delay1);
AudioConnection          patchCord11(reverb_sw, 0, delay_sw, 0);
AudioConnection          patchCord12(delay1, 0, delay_sw, 1);
AudioConnection          patchCord13(i2s1_in, 1, master_mix, 0);
AudioConnection          patchCord14(delay_sw, 0, master_mix, 1);
AudioConnection          patchCord15(master_mix, 0, i2s2_out, 0);
AudioConnection          patchCord16(master_mix, 0, i2s2_out, 1);

// Global variables
const int inputChSelect = AUDIO_INPUT_LINEIN;

void initialiseAudio() {
    AudioMemory(250);

    audioShield.enable();
    audioShield.inputSelect(inputChSelect); 
    audioShield.volume(masterVolume);
    audioShield.lineOutLevel(gainOut);

    flange_sw.gain(0, 1);
    flange_sw.gain(1, 0);
    flange_sw.gain(2, 0);
    flange_sw.gain(3, 0);

    chorus_sw.gain(0, 1);
    chorus_sw.gain(1, 0);
    chorus_sw.gain(2, 0);
    chorus_sw.gain(3, 0);

    reverb_sw.gain(0, 1);
    reverb_sw.gain(1, 0);
    reverb_sw.gain(2, 0);
    reverb_sw.gain(3, 0);

    delay_sw.gain(0, 1);
    delay_sw.gain(1, 0);
    delay_sw.gain(2, 0);
    delay_sw.gain(3, 0);

    master_mix.gain(0, 1);
    master_mix.gain(1, 1);

    if (!chorus.begin(l_delayline, chorusDelayLength, n_chorus)) {
      //Serial.println("AudioEffectChorus - left channel begin failed");
      while (1);
    }

    flange.begin(flange_delayline, FLANGE_DELAY_LENGTH, s_idx, s_depth, s_freq);
}