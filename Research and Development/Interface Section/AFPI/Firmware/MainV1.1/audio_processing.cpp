#include "audio_processing.h"

#include "config.h"
#include <Arduino.h>
#include <Audio.h>

// Instantiate audio objects
AudioInputI2S            i2s1_in;

//AudioRecordQueue         queue1;  
AudioEffectWaveshaper    waveshape1; 
//AudioAmplifier           amp1; 
AudioMixer4              distort_sw;
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


// Instantiate audio connections
AudioConnection          patchCord1(i2s1_in, 0, distort_sw, 0);
AudioConnection          patchCord2(i2s1_in, 0, waveshape1, 0);
AudioConnection          patchCord3(waveshape1, 0, distort_sw, 1);

AudioConnection          patchCord4(distort_sw, 0, flange_sw, 0);
AudioConnection          patchCord5(distort_sw, 0, flange, 0);
AudioConnection          patchCord6(flange, 0, flange_sw, 1);

AudioConnection          patchCord7(flange_sw, chorus);
AudioConnection          patchCord8(flange_sw, 0, chorus_sw, 0);
AudioConnection          patchCord9(chorus, 0, chorus_sw, 1);

AudioConnection          patchCord10(chorus_sw, freeverb);
AudioConnection          patchCord11(chorus_sw, 0, reverb_sw, 0);
AudioConnection          patchCord12(freeverb, 0, reverb_sw, 1);

AudioConnection          patchCord13(reverb_sw, delay1);
AudioConnection          patchCord14(reverb_sw, 0, delay_sw, 0);
AudioConnection          patchCord15(delay1, 0, delay_sw, 1);

AudioConnection          patchCord16(i2s1_in, 1, master_mix, 0);
AudioConnection          patchCord17(delay_sw, 0, master_mix, 1);
AudioConnection          patchCord18(master_mix, 0, i2s2_out, 0);
AudioConnection          patchCord19(master_mix, 0, i2s2_out, 1);


AudioControlSGTL5000     audioShield;






// Global variables
const int inputChSelect = AUDIO_INPUT_LINEIN;

void initialiseAudio() {
    AudioMemory(250);

    audioShield.enable();
    audioShield.inputSelect(inputChSelect); 

    determineAudioOutput();

    distort_sw.gain(0, 1);
    distort_sw.gain(1, 0);
    distort_sw.gain(2, 0);
    distort_sw.gain(3, 0);

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

void determineAudioOutput() {
    if (currentAudioOutput == 0){
    audioShield.muteHeadphone();
    audioShield.unmuteLineout();
    audioShield.dacVolume(SPVol, 0.05);
    audioShield.lineOutLevel(SPGainOut, 31);
  }
  if (currentAudioOutput == 1){
    audioShield.unmuteHeadphone();
    audioShield.muteLineout();
    audioShield.dacVolume(1.0, 1.0);

    audioShield.volume(HPVol);
    audioShield.lineOutLevel(HPGainOut);
  }
  if (currentAudioOutput == 2){
    audioShield.muteHeadphone();
    audioShield.unmuteLineout();
    audioShield.dacVolume(0.05, AUXVol);
    audioShield.lineOutLevel(31, AuxGainOut);
  }
}
void initialiseDistortion() {
    float *x = (float*)malloc(sizeof(float)*32769),
        *cheby_poly_lut_0 = (float*)malloc(sizeof(float)*32769),
        *cheby_poly_lut_1 = (float*)malloc(sizeof(float)*32769);
  
    for(int i = 0; i < 32769; i++){
      x[i] = 2.0*(i/32768.0)-1.0; // map from index to value
      cheby_poly_lut_0[i] = 1.0; // 0th chebyshev, DC
      cheby_poly_lut_1[i] = x[i]; // 1st chebyshev, pass-through

      waveshape[i] = cheby_poly_lut_1[i]; // init with the 1st chebyshev polynomial
    }

    for(int k = 2; k <= MAX_ORDER; k++){ // k is the cheby_order
      for(int i = 0; i < 32769; i++){
        // generate the next chebyshev polynomial then add it to waveshape
        float next_cheby_poly = 2.0*x[i]*cheby_poly_lut_1[i]-cheby_poly_lut_0[i];
        waveshape[i] += alpha[k-2]*next_cheby_poly;

        cheby_poly_lut_0[i] = cheby_poly_lut_1[i];
        cheby_poly_lut_1[i] = next_cheby_poly;
      }
    }

    // remove the offset at zero
    float zero_offset = waveshape[16384];
    for(int i = 0; i < 32769; i++) waveshape[i] -= zero_offset;

    // normalize the waveshaper to -1dB Vpk
    float max_abs_val = 0;
    for(int i = 0; i < 32769; i++){
      float abs_val = abs(waveshape[i]);
      if(abs_val > max_abs_val) max_abs_val = abs_val;
    }
    for(int i = 0; i < 32769; i++) waveshape[i] *= pow(10.0, -1.0/20.0)/max_abs_val;

    free(x);
    free(cheby_poly_lut_0);
    free(cheby_poly_lut_1);
    
    waveshape1.shape(waveshape, 32769);

    // sgtl5000_1.lineInLevel(3); // Optimal for 2V_p-p signal
    // sgtl5000_1.lineOutLevel(25); // Under 25 causes soft clipping

}