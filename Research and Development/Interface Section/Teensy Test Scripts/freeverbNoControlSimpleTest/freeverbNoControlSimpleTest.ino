#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1_in;           //xy=466.11112213134766,339.28570556640625

AudioEffectFreeverb      freeverb;      //xy=743.857177734375,336.8571472167969

AudioOutputI2S           i2s2_out;           //xy=923.888916015625,332.8888854980469



AudioConnection          patchCord1(i2s1_in, 0, freeverb, 0);
AudioConnection          patchCord2(freeverb, 0, i2s2_out, 0);
AudioConnection          patchCord3(freeverb, 0, i2s2_out, 1);

AudioControlSGTL5000     audioShield;     //xy=862.3333740234375,235.2222442626953
// GUItool: end automatically generated code

const int inputChSelect = AUDIO_INPUT_LINEIN;

// audio shield volume
int masterVolume = 0;

float roomsizeamt = 1;

float dampingamt = 1;
void setup() {
  // put your setup code here, to run once:

  
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  Serial.print("init audio shield...");
  audioShield.enable();
  audioShield.inputSelect(inputChSelect);  // select mic or line-in for audio shield input source
  audioShield.volume(0.5);
  Serial.println("done.");

  freeverb.roomsize(roomsizeamt);
  freeverb.damping(dampingamt);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("freeverb effect running.");
}
