#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

#define SS_NEO_PIN       18
#define SS_ENC0_SWITCH   12
#define SS_ENC1_SWITCH   14
#define SS_ENC2_SWITCH   17
#define SS_ENC3_SWITCH   9

#define SEESAW_ADDR      0x49


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "TomThumb.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

const uint8_t bitmap37[] = {0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x7f, 0xff, 0xe0, 
                            0xff, 0xff, 0xf0, 
                            0xc0, 0x00, 0x30, 
                            0xc0, 0x00, 0x30, 
                            0xc0, 0x00, 0x30, 
                            0xc0, 0x00, 0x33, 
                            0xc0, 0x00, 0x33, 
                            0xc0, 0x00, 0x33, 
                            0xc0, 0x00, 0x33, 
                            0xc0, 0x00, 0x30, 
                            0xc0, 0x00, 0x30, 
                            0xc0, 0x00, 0x30, 
                            0xff, 0xff, 0xf0, 
                            0x7f, 0xff, 0xe0, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00};

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1_in;           //xy=466.11112213134766,339.28570556640625
AudioEffectFlange        flange;        //xy=626.6666259765625,389.99999237060547
AudioMixer4              flange_sw;         //xy=802.0000152587891,343.99999618530273
AudioEffectChorus        chorus;        //xy=944.9364852905273,440.57143211364746
AudioMixer4              chorus_sw; //xy=1087.5714111328125,360.714298248291
AudioEffectFreeverb      freeverb;      //xy=1242.8571739196777,447.8571319580078
AudioMixer4              reverb_sw; //xy=1409.412712097168,367.3174858093262
AudioEffectDelay         delay1;         //xy=1791.1111183166504,462.2222480773926
AudioMixer4              delay_sw;         //xy=2136.666603088379,401.11111068725586
AudioOutputI2S           i2s2_out;           //xy=2405.555362701416,354.4444236755371
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


AudioConnection          patchCord13(delay_sw, 0, i2s2_out, 0);
AudioConnection          patchCord14(delay_sw, 0, i2s2_out, 1);

AudioControlSGTL5000     audioShield;     //xy=1157.3333206176758,200.22224235534668
// GUItool: end automatically generated code


// GUItool: end automatically generated code

const int inputChSelect = AUDIO_INPUT_LINEIN;

// audio shield volume
int masterVolume        = 0;


#define chorusDelayLength (16*AUDIO_BLOCK_SAMPLES)  // Number of samples in each delay line

short l_delayline[chorusDelayLength]; // Allocate the delay lines for left and right channels
int   n_chorus = 2;                   // number of "voices" in the chorus including the original voice
bool  chorusActive = false;  

bool reverbActive = false;
float revRoomsize = 0.0;
float revDamping = 0.0;

bool delayActive = false;
int delayTime = 0;

Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);
seesaw_NeoPixel pixels = seesaw_NeoPixel(4, SS_NEO_PIN, NEO_GRB + NEO_KHZ800, &Wire1);

int32_t enc_positions[4] = {0, 0, 0, 0};

const int buttonPin = 14;

int currentEffect;
int currentHoverOption = 0;
void setup() {
  // put your setup code here, to run once:
    // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(120);

  // Comment these out if not using the audio adaptor board.
  Serial.print("init audio shield...");
  audioShield.enable();
  audioShield.inputSelect(inputChSelect);  // select mic or line-in for audio shield input source
  audioShield.volume(0.7);
  Serial.println("done.");

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



  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


    // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
   // Draw many lines

  testLoadingScreen();

  if (!chorus.begin(l_delayline, chorusDelayLength, n_chorus)) {
    Serial.println("AudioEffectChorus - left channel begin failed");
    while (1);
  }
  delay(2000);
  delay(2000);


  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(115200);
  while (!Serial) delay(10);

  // Initialize I2C communication
  Wire1.begin();  // No need to specify SDA and SCL pins for Teensy 4.0

  Serial.println("Looking for seesaw!");
  
  if (! ss.begin(SEESAW_ADDR) || !pixels.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version  != 5752){
    Serial.print("Wrong firmware loaded? ");
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found Product 5752");

  ss.pinMode(SS_ENC0_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC1_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC2_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC3_SWITCH, INPUT_PULLUP);
  ss.setGPIOInterrupts(1UL << SS_ENC0_SWITCH | 1UL << SS_ENC1_SWITCH | 
                       1UL << SS_ENC2_SWITCH | 1UL << SS_ENC3_SWITCH, 1);

  
  // get starting positions
  for (int e=0; e<4; e++) {
    enc_positions[e] = ss.getEncoderPosition(e);
    ss.enableEncoderInterrupt(e);
  }
  
  Serial.println("Turning on interrupts");

  pixels.setBrightness(255);
  pixels.show(); // Initialize all pixels to 'off'


  //skeleton setups
  
}

int i = 0;
void loop() {


  while (i<3) {
    loading();

    i = i + 1;
    delay(1000);
  }

  landingPage();

  delay(10);
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loading() {
  Serial.print("Starting up. Display loading Screen... ");
}

void landingPage() {

  Serial.println();
  Serial.println("**************Landing Page**************");  
  Serial.print("Options:");
  Serial.println();
  Serial.print("0# FX");
  Serial.println();
  Serial.print("1# EQ");
  Serial.println();
  Serial.print("2# Audio");
  Serial.println();
  Serial.print("3# RGB");
  Serial.println();
  Serial.print("4# Settings");
  

  setLandingPage();

  bool choosing = true;

  while (choosing == true) {


    int32_t enc_3_pos = ss.getEncoderPosition(3);
    if (enc_positions[3] != enc_3_pos) {
      Serial.print("Encoder #");
      Serial.print(3);
      Serial.print(" -> ");
      Serial.println(enc_3_pos); // Display new position

      // Determine the direction of movement
      if (enc_3_pos > enc_positions[3]) {
        // Encoder moved clockwise
        if (currentHoverOption < 4) { // Adjusted boundary to 4 for 5 options (0 to 4)
          currentHoverOption++;
        } else {
          Serial.println("cannot go that way forwards. must stay between 0 and 4");
        }
      } else if (enc_3_pos < enc_positions[3]) {
        // Encoder moved counterclockwise
        if (currentHoverOption > 0) {
          currentHoverOption--;
        } else {
          Serial.println("cannot go that way backwards. must stay between 0 and 4");
        }
      }

      Serial.print("Currently selected Option: ");
      Serial.println(currentHoverOption);

      hoverOptionSelector();
      // Update the last known encoder position
      enc_positions[3] = enc_3_pos;

      pixels.setPixelColor(3, Wheel((enc_3_pos * 4) & 0xFF));
      pixels.show();
    }

    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      Serial.println("ENC3 pressed!");
      Serial.println("The following option is chosen:");
      Serial.println(currentHoverOption);
      choosing = false;
    }


  }
  if (currentHoverOption == 0){
    FXMainPage();
  }
  if (currentHoverOption == 1){
    EQPage();
  }
  if (currentHoverOption == 2){
    audioPage();
  }
  if (currentHoverOption == 3){
    RGBPage();
  }
  if (currentHoverOption == 4){
    settingsPage();
  }
}

void hoverOptionSelector() {
    display.clearDisplay();
    setLandingPage();
    Serial.println("hoveroptionselector");
    Serial.println(currentHoverOption);
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
  Serial.println("**************Settings Page**************");
  Serial.println("Settings details...");
  Serial.println("Press ENC3 to return to the landing menu");

  // Wait for the button to be released if it was pressed
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }


  while (true) {
    int buttonState = digitalRead(buttonPin); 
    if (buttonState == LOW) {
      Serial.println("Button pressed!");
      // Add any additional action you want to perform when the button is pressed
      delay(500); 
      break;
    }
  }
  landingPage();
  
}


void RGBPage() {
  Serial.println("**************RGB Lighting Page**************");
  Serial.println("Lighting options and details...");
  Serial.println("press ENC3 to return to landing menu");

  // Wait for the button to be released if it was pressed
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }

  while (true) {
    int buttonState = digitalRead(buttonPin); 
    if (buttonState == LOW) {
      Serial.println("Button pressed!");
      // Add any additional action you want to perform when the button is pressed
      delay(500); 
      break;
    }
  }
  landingPage();
}

void audioPage() {
  Serial.println("**************Audio Controls Page**************");
  Serial.println("Audio options and details...");
  Serial.println("press ENC3 to return to landing menu");

  // Wait for the button to be released if it was pressed
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }

  while (true) {
    int buttonState = digitalRead(buttonPin); 
    if (buttonState == LOW) {
      Serial.println("Button pressed!");
      // Add any additional action you want to perform when the button is pressed
      delay(500); 
      break;
    }
  }
  landingPage();  
}

void EQPage() {
  Serial.println("**************EQ Controls Page**************");
  Serial.println("EQ options and details...");
  Serial.println("press ENC3 to return to landing menu");

  // Wait for the button to be released if it was pressed
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }

  while (true) {
    int buttonState = digitalRead(buttonPin); 
    if (buttonState == LOW) {
      Serial.println("Button pressed!");
      // Add any additional action you want to perform when the button is pressed
      delay(500); 
      break;
    }
  }
  landingPage();
}

void FXMainPage() {
  Serial.println("**************FX Controls Page**************");
  Serial.println("FX options and details...");
  Serial.println("press ENC3 to return to landing menu");

  // Wait for the button to be released if it was pressed
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }
  chorusFX();
  while (true) {
    int buttonState = digitalRead(buttonPin); 
    if (buttonState == LOW) {
      Serial.println("Button pressed!");
      // Add any additional action you want to perform when the button is pressed
      delay(500); 
      break;
    }
  }
  landingPage();
}

void chorusFX() {
    Serial.println("**************Effect #2 : Chorus**************");
    if (chorusActive == false){
        Serial.print("OFF");
    }
    else {
      Serial.print("ON");
    }
    Serial.println("Voices amount: ");
    Serial.print(n_chorus);
    currentEffect = 1;
    while (true) {
        chorusSetPage();
        int buttonState = digitalRead(buttonPin); 

        if (buttonState == LOW) {
          Serial.println("Home Button pressed!");
          delay(500); 
          landingPage();
          }

        int32_t enc_0_pos = ss.getEncoderPosition(0);
        if (enc_positions[0] != enc_0_pos) {
            int change = enc_0_pos - enc_positions[0];

            // Update the encoder position
            enc_positions[0] = enc_0_pos;

            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && n_chorus < 16) {
                n_chorus++;
            } else if (change < 0 && n_chorus > 2) {
                n_chorus--;
            }

            // Update the effect
            chorus.voices(n_chorus);

            // Display the new value
            Serial.print("Voices amount: ");
            Serial.println(n_chorus);

            // Update the NeoPixel color
            pixels.setPixelColor(0, Wheel((enc_0_pos * 4) & 0xFF));
            pixels.show();
        }

        if (!ss.digitalRead(SS_ENC3_SWITCH)) {
          Serial.println("ENC3 pressed!");
          Serial.println("effect is now on");
          if (chorusActive == false){
              Serial.print("effect now ON");
              chorusActive = true;
              chorus_sw.gain(0, 0);
              chorus_sw.gain(1, 1);
          }
          else {
              Serial.print("effect now OFF");
              chorusActive = false;
              chorus_sw.gain(0, 1);
              chorus_sw.gain(1, 0);
          }         
        }
        while (!ss.digitalRead(SS_ENC3_SWITCH)) {
        // Debounce delay
        delay(50);
        }

        int32_t enc_3_pos = ss.getEncoderPosition(3);
        if (enc_positions[3] != enc_3_pos) {
            int change = enc_3_pos - enc_positions[3];

            // Update the encoder position
            enc_positions[3] = enc_3_pos;
            Serial.print(change);
            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && currentEffect < 3) {
                reverbFX();
            } else if (change < 0 && currentEffect > 0) {
                Serial.print("go  to fx 1, not made yet");
            }
            // Update the NeoPixel color
            pixels.setPixelColor(0, Wheel((enc_0_pos * 4) & 0xFF));
            pixels.show();
        }
    }
}

void reverbFX() {
    Serial.println("**************Effect #3 : Reverb**************");
    if (reverbActive == false){
        Serial.print("OFF");
    }
    else {
      Serial.print("ON");
    }
    Serial.println("roomSize amount: ");
    Serial.print(revRoomsize);
    Serial.println("Damping amount: ");
    Serial.print(revDamping);

    while (true) {

        int buttonState = digitalRead(buttonPin); 

        if (buttonState == LOW) {
          Serial.println("Home Button pressed!");
          delay(500); 
          landingPage();
          }

        int32_t enc_0_pos = ss.getEncoderPosition(0);
        if (enc_positions[0] != enc_0_pos) {
            int change = enc_0_pos - enc_positions[0];

            // Update the encoder position
            enc_positions[0] = enc_0_pos;

            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && revRoomsize < 1.0) {
                revRoomsize = revRoomsize + 0.05;
            } else if (change < 0 && revRoomsize > 0.0) {
                revRoomsize = revRoomsize - 0.05;
            }

            // Update the effect
            freeverb.roomsize(revRoomsize);

            // Display the new value
            Serial.print("Room size amount: ");
            Serial.println(revRoomsize);

            // Update the NeoPixel color
            pixels.setPixelColor(0, Wheel((enc_0_pos * 4) & 0xFF));
            pixels.show();
        }

        int32_t enc_1_pos = ss.getEncoderPosition(1);
        if (enc_positions[1] != enc_1_pos) {
            int change = enc_1_pos - enc_positions[1];

            // Update the encoder position
            enc_positions[1] = enc_1_pos;

            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && revDamping < 1.0) {
                revDamping = revDamping + 0.05;
            } else if (change < 0 && revDamping > 0.0) {
                revDamping = revDamping - 0.05;  
            }
            freeverb.damping(revDamping);

            // Display the new value
            Serial.print("damping: ");
            Serial.println(revDamping);

            // Update the NeoPixel color
            pixels.setPixelColor(1, Wheel((enc_1_pos * 4) & 0xFF));
            pixels.show();
        }

        if (!ss.digitalRead(SS_ENC3_SWITCH)) {
          Serial.println("ENC3 pressed!");
          Serial.println("effect is now on");
          if (reverbActive == false){
              Serial.print("effect now ON");
              reverbActive = true;
              reverb_sw.gain(0, 0);
              reverb_sw.gain(1, 1);
          }
          else {
              Serial.print("effect now OFF");
              reverbActive = false;
              reverb_sw.gain(0, 1);
              reverb_sw.gain(1, 0);
          }         
        }
        while (!ss.digitalRead(SS_ENC3_SWITCH)) {
        // Debounce delay
        delay(50);
        }

        int32_t enc_3_pos = ss.getEncoderPosition(3);
        if (enc_positions[3] != enc_3_pos) {
            int change = enc_3_pos - enc_positions[3];

            // Update the encoder position
            enc_positions[3] = enc_3_pos;
            Serial.print(change);
            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && currentEffect < 4) {
                delayFX();
            } else if (change < 0 && currentEffect > 0) {
                chorusFX();
            }
            // Update the NeoPixel color
            pixels.setPixelColor(0, Wheel((enc_0_pos * 4) & 0xFF));
            pixels.show();
        }
    }
}

void delayFX() {
    Serial.println("**************Effect #4 : Delay**************");
    if (delayActive == false){
        Serial.print("OFF");
    }
    else {
      Serial.print("ON");
    }
    Serial.println("delay amount: ");
    Serial.print(delayTime);
    currentEffect = 3;

    // Update the effect
    while (true) {
        delaySetPage();
        int buttonState = digitalRead(buttonPin); 

        if (buttonState == LOW) {
          Serial.println("Home Button pressed!");
          delay(500); 
          landingPage();
          }

        int32_t enc_0_pos = ss.getEncoderPosition(0);
        if (enc_positions[0] != enc_0_pos) {
            int change = enc_0_pos - enc_positions[0];

            // Update the encoder position
            enc_positions[0] = enc_0_pos;

            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && delayTime < 1000) {
                delayTime = delayTime + 50;
            } else if (change < 0 && delayTime > 0) {
                delayTime = delayTime - 50;
            }
            // Update the effect
            delay1.delay(0, delayTime);

            // Display the new value
            Serial.print("delay amount: ");
            Serial.println(delayTime);

            // Update the NeoPixel color
            pixels.setPixelColor(0, Wheel((enc_0_pos * 4) & 0xFF));
            pixels.show();
        }

        if (!ss.digitalRead(SS_ENC3_SWITCH)) {
          Serial.println("ENC3 pressed!");
          Serial.println("effect is now on");
          if (delayActive == false){
              Serial.print("effect now ON");
              delayActive = true;
              delay_sw.gain(0, 1);
              delay_sw.gain(1, 1);
          }
          else {
              Serial.print("effect now OFF");
              delayActive = false;
              delay_sw.gain(0, 1);
              delay_sw.gain(1, 0);
          }         
        }
        while (!ss.digitalRead(SS_ENC3_SWITCH)) {
        // Debounce delay
        delay(50);
        }

        int32_t enc_3_pos = ss.getEncoderPosition(3);
        if (enc_positions[3] != enc_3_pos) {
            int change = enc_3_pos - enc_positions[3];

            // Update the encoder position
            enc_positions[3] = enc_3_pos;
            Serial.print(change);
            // Adjust n_chorus based on the change, ensuring it remains within the valid range
            if (change > 0 && currentEffect < 4) {
                Serial.print("go  to fx 1, not made yet");
            } else if (change < 0 && currentEffect > 0) {
                reverbFX();
            }
            // Update the NeoPixel color
            pixels.setPixelColor(0, Wheel((enc_0_pos * 4) & 0xFF));
            pixels.show();
        }
    }
}

void testLoadingScreen() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.println("Expeditioner ");
    display.println("Alex Stewart");
    display.println("");
    display.println("Loading...");
    display.display();
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

void chorusSetPage() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.setCursor(0, 5);
    display.setTextWrap(0);
    display.setCursor(28, 5);
    display.println("FX 1# Chorus");
    display.drawLine(0, 18, 128, 18, 1);
    display.setCursor(10, 20);
    display.print("Voices:");
    display.setCursor(24, 35);
    display.println(n_chorus);
    display.drawRect(109, 50, 17, 12, 1);
    display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
    display.drawRect(2, 50, 17, 12, 1);
    display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
    display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
    display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
    display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
    display.display();
}

void delaySetPage() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.setCursor(0, 5);
    display.setTextWrap(0);
    display.setCursor(28, 5);
    display.println("FX 4# Delay");
    display.drawLine(0, 18, 128, 18, 1);
    display.setCursor(10, 20);
    display.print("Time Ms:");
    display.setCursor(24, 35);
    display.println(delayTime);
    display.drawRect(109, 50, 17, 12, 1);
    display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
    display.drawRect(2, 50, 17, 12, 1);
    display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
    display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
    display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
    display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
    display.display();
}

