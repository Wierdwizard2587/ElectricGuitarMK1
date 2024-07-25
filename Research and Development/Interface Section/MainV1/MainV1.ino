#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

#define SS_NEO_PIN       18
#define SS_ENC0_SWITCH   12
#define SS_ENC1_SWITCH   14
#define SS_ENC2_SWITCH   17
#define SS_ENC3_SWITCH   9

#define SEESAW_ADDR      0x49

#include <Arduino.h>

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

#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short flange_delayline[FLANGE_DELAY_LENGTH];
int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;
bool flangeActive = false;


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
float param;
int fxEncRes;




int currentHoverOption = 0;
void setup() {


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  testLoadingScreen();

  Serial.begin(115200);
  while (!Serial) delay(10);


  AudioMemory(250);

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


  if (!chorus.begin(l_delayline, chorusDelayLength, n_chorus)) {
    Serial.println("AudioEffectChorus - left channel begin failed");
    while (1);
  }

  flange.begin(flange_delayline, FLANGE_DELAY_LENGTH, s_idx, s_depth, s_freq);


  pinMode(buttonPin, INPUT_PULLUP);

  Wire1.begin();

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
  landingPage();
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

void flangeFX() {
    currentEffect = 0;
    while (true) {
        flangeSetPage();

        checkHomeButton();

        //flange Freq Control Encoder Check
        param = s_freq;
        fxEncRes = EncDialCheck(0, param, 5.0, 0.0);
        if (fxEncRes == 2) {
          s_freq = s_freq + 0.1;
        } 
        if (fxEncRes == 1) {
          s_freq = s_freq - 0.1;
        }
        flange.voices(s_idx,s_depth,s_freq);


        //Check flange FX active Toggle
        EncToggleCheck(flangeActive, flange_sw);

        //Check FX selected change 
        cycleFX(3, currentEffect, 3.0, 0.0);
    }
}


void chorusFX() {
    currentEffect = 1;
    while (true) {
        chorusSetPage();

        checkHomeButton();

        //chorus Voice amount Control Encoder Check
        param = n_chorus;
        fxEncRes = EncDialCheck(0, param, 16, 2);
        if (fxEncRes == 2) {
          n_chorus++;
        } 
        if (fxEncRes == 1) {
          n_chorus--;
        }
        chorus.voices(n_chorus);

        EncToggleCheck(chorusActive, chorus_sw); //Check Chorus FX active Toggle
        
        cycleFX(3, currentEffect, 3.0, 0.0); //Check FX selected change 
    }
}


void reverbFX() {
    currentEffect = 2;
    while (true) {
        ReverbSetPage();

        checkHomeButton();

        //Reverb Room Size Control Encoder Check
        param = revRoomsize;
        fxEncRes = EncDialCheck(0, param, 1.0, 0.0);
        if (fxEncRes == 2) {
          revRoomsize = revRoomsize + 0.05;
        } 
        if (fxEncRes == 1) {
          revRoomsize = revRoomsize - 0.05;
        }
        freeverb.roomsize(revRoomsize);

        //Reverb Damping Control Encoder Check
        param = revDamping;
        fxEncRes = EncDialCheck(1, param, 1.0, 0.0);
        if (fxEncRes == 2) {
          revDamping = revDamping + 0.05;
        } 
        if (fxEncRes == 1) {
          revDamping = revDamping - 0.05;
        }
        freeverb.damping(revDamping);

        //Check reverb FX active Toggle
        EncToggleCheck(reverbActive, reverb_sw);

        //Check FX selected change 
        cycleFX(3, currentEffect, 3.0, 0.0);
    }
}

void delayFX() {
    currentEffect = 3;
    while (true) {
        delaySetPage();
        
        checkHomeButton();

        //Delay time Control Encoder Check
        param = delayTime;
        fxEncRes = EncDialCheck(0, param, 1000, 0);
        if (fxEncRes == 2) {
          delayTime = delayTime + 50;
        } 
        if (fxEncRes == 1) {
          delayTime = delayTime - 50;
        }
        delay1.delay(0, delayTime);

        //Check delay FX active Toggle
        EncToggleCheck(delayActive, delay_sw);
        delay_sw.gain(0, 1);
        //Check FX selected change 
        cycleFX(3, currentEffect, 3.0, 0.0);
    }
}

typedef void (*FunctionPointer)();
FunctionPointer FXfunctions[] = { flangeFX, chorusFX, reverbFX, delayFX  };

void checkHomeButton() {
  int buttonState = digitalRead(buttonPin); 

  if (buttonState == LOW) {
    Serial.println("Home Button pressed!");
    delay(500); 
    landingPage();
  }
}

int EncDialCheck(int encNo, float paramValue, float maxRange, float minRange) {
    int32_t enc_pos = ss.getEncoderPosition(encNo);
    if (enc_positions[0] != enc_pos) {
        int change = enc_pos - enc_positions[encNo];

        // Update the encoder position
        enc_positions[encNo] = enc_pos;

        // Adjust n_chorus based on the change, ensuring it remains within the valid range
        if (change > 0 && paramValue < maxRange) {
            return 2;
        } else if (change < 0 && paramValue > minRange) {
            return 1;
        }
    }
    return 0;
}

void EncToggleCheck(bool& FXActive, AudioMixer4& mixer_sw) {
    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      Serial.println("ENC3 pressed!");
      Serial.println("effect is now on");
      if (FXActive == false){
          Serial.print("effect now ON");
          FXActive = true;
          mixer_sw.gain(0, 0);
          mixer_sw.gain(1, 1);
      }
      else {
          Serial.print("effect now OFF");
          FXActive = false;
          mixer_sw.gain(0, 1);
          mixer_sw.gain(1, 0);
      }         
    }

    while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
    }
}




void cycleFX(int encNo, int param, int maxRange, int minRange) {
    int EncRes;
    EncRes = EncDialCheck(encNo, param, maxRange, minRange);
    Serial.print(EncRes);
    if (EncRes == 2) {
        FXfunctions[param + 1]();;
    } 
    if (EncRes == 1) {
        FXfunctions[param - 1]();;
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

void flangeSetPage() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.setCursor(0, 5);
    display.setTextWrap(0);
    display.setCursor(28, 5);
    display.println("FX 1# Flange");
    display.drawLine(0, 18, 128, 18, 1);
    display.setCursor(10, 20);
    display.print("Freq:");
    display.setCursor(24, 35);
    display.println(s_freq);
    display.drawRect(109, 50, 17, 12, 1);
    display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
    display.drawRect(2, 50, 17, 12, 1);
    display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
    display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
    display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
    display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
    if (flangeActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
    
    display.display();
}

void chorusSetPage() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.setCursor(0, 5);
    display.setTextWrap(0);
    display.setCursor(28, 5);
    display.println("FX 2# Chorus");
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
    if (chorusActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
    
    display.display();
}

void ReverbSetPage() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.setCursor(0, 5);
    display.setTextWrap(0);
    display.setCursor(28, 5);
    display.println("FX 3# Reverb");
    display.drawLine(0, 18, 128, 18, 1);
    display.setCursor(1, 20);
    display.print("RoomSize:");
    display.setCursor(15, 35);
    display.println(revRoomsize);
    display.setCursor(55, 20);
    display.print("Damping:");
    display.setCursor(65, 35);
    display.println(revDamping);
    display.drawRect(109, 50, 17, 12, 1);
    display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
    display.drawRect(2, 50, 17, 12, 1);
    display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
    display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
    display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
    display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
    if (reverbActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
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
    if (delayActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
    display.display();
}


