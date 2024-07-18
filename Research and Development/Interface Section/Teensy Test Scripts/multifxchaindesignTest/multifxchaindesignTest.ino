#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1_in;           //xy=466.11112213134766,339.28570556640625

AudioEffectWaveshaper    waveshape1;     //xy=611.8571701049805,385.7142963409424
AudioMixer4              fuzz_sw;         //xy=802.0000152587891,343.99999618530273

AudioEffectChorus        chorus;        //xy=944.9364852905273,440.57143211364746
AudioMixer4              chorus_sw; //xy=1087.5714263916016,360.71428298950195

AudioEffectFreeverb      freeverb;      //xy=1242.8571739196777,447.8571319580078
AudioMixer4              reverb_sw; //xy=1403.8571853637695,368.42857360839844

AudioOutputI2S           i2s2_out;           //xy=1658.888888888889,368.88888888888886


//input to fuzz dpdt sw
AudioConnection          patchCord1(i2s1_in, 0, waveshape1, 0);
AudioConnection          patchCord2(i2s1_in, 0, fuzz_sw, 0);
AudioConnection          patchCord3(waveshape1, 0, fuzz_sw, 1);

//fuzz dpdt sw to chorus dpdt sw
AudioConnection          patchCord4(fuzz_sw, chorus);
AudioConnection          patchCord5(fuzz_sw, 0, chorus_sw, 0);
AudioConnection          patchCord6(chorus, 0, chorus_sw, 1);

//chorus dpdt sw to reverb dpdt sw
AudioConnection          patchCord7(chorus_sw, freeverb);
AudioConnection          patchCord8(chorus_sw, 0, reverb_sw, 0);
AudioConnection          patchCord9(freeverb, 0, reverb_sw, 1);

//reverb dpdt sw to output
AudioConnection          patchCord10(reverb_sw, 0, i2s2_out, 0);
AudioConnection          patchCord11(reverb_sw, 0, i2s2_out, 1);

AudioControlSGTL5000     sgtl5000_1;     //xy=1157.3333206176758,200.22224235534668
// GUItool: end automatically generated code



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
