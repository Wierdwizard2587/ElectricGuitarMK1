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

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);


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


#include <regex>


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

const int inputChSelect = AUDIO_INPUT_LINEIN;

const int chipSelect = 10;

// audio shield volume
float masterVolume  = 0.0;
int gainOut = 13;

#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short flange_delayline[FLANGE_DELAY_LENGTH];
int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;
bool flangeActive;


#define chorusDelayLength (16*AUDIO_BLOCK_SAMPLES)  // Number of samples in each delay line
short l_delayline[chorusDelayLength]; // Allocate the delay lines for left and right channels
int   n_chorus = 2;                   // number of "voices" in the chorus including the original voice
bool chorusActive;  

bool reverbActive;
float revRoomsize = 0.0;
float revDamping = 0.0;

bool delayActive;
int delayTime = 0;

Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);
seesaw_NeoPixel pixels = seesaw_NeoPixel(4, SS_NEO_PIN, NEO_GRB + NEO_KHZ800, &Wire1);

int32_t enc_positions[4] = {0, 0, 0, 0};

const int buttonPin = 14;

//General FX Variables
int currentEffect;
float param;
int fxEncRes;

//Audio section Variables
int currentAuxPage;
bool backingActive = false;
float backingVol = 0.5;

//landing page Variables
int currentHoverOption = 0;



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
String softwareVer;

void setup() {

  Serial.begin(115200);
  while (!Serial) delay(10);


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  testLoadingScreen();

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  String filename = "data.txt";
  readStoredValues();


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


  if (!chorus.begin(l_delayline, chorusDelayLength, n_chorus)) {
    Serial.println("AudioEffectChorus - left channel begin failed");
    while (1);
  }

  flange.begin(flange_delayline, FLANGE_DELAY_LENGTH, s_idx, s_depth, s_freq);


  pinMode(buttonPin, INPUT_PULLUP);

  Wire1.begin();
  
  if (! ss.begin(SEESAW_ADDR) || !pixels.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
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

  
  for (int e=0; e<4; e++) {
    enc_positions[e] = ss.getEncoderPosition(e);
    ss.enableEncoderInterrupt(e);
  }

  pixels.setBrightness(255);
  pixels.show();
}
//set sketch variables their value from the txt file
void readStoredValues() {
  String variables[] = {};


  File dataFile = SD.open("data.txt");
  if (dataFile) {
    Serial.println("data.txt opened successfully.");

      // Read each line from the file
    while (dataFile.available()) {
      String line = readLine(dataFile);
      
      // Skip empty lines or lines starting with //
      if (line.length() > 0 && !line.startsWith("//")) {
        Serial.println(line);
        parseAndUpdate(line);
      }
    }

    dataFile.close();
    Serial.println("data.txt closed.");
  } else {
    Serial.println("Error opening data.txt");
  }
}

String readLine(File &file) {
  String line = "";
  while (file.available()) {
    char c = file.read();
    if (c == '\n') {
      break; // End of line
    }
    line += c;
  }
  return line;
}

void parseAndUpdate(const String& line) {
  String key;
  String value;

  int equalsIndex = line.indexOf("=");
  if (equalsIndex == -1) return;

  key = line.substring(0, equalsIndex);
  value = line.substring(equalsIndex + 1);

  Serial.println(key);
  Serial.println(value);

  updateVariableByName(key, value);

}

// Structure to hold variable information
struct Variable {
  String name;
  void* pointer;
  void (*updateFunction)(void*, const String&);
};

// Update functions for different types
void updateFloat(void* ptr, const String& value) {
  Serial.println("float var");
  *(float*)ptr = value.toFloat();
}

void updateInt(void* ptr, const String& value) {
  Serial.println("int var");
  *(int*)ptr = value.toInt();
}

void updateString(void* ptr, const String& value) {
  Serial.println("String var");
  *(String*)ptr = value;
}

void updateBool(void* ptr, const String& value) {
  Serial.println("bool var");
  Serial.print("Value read: '");
  Serial.print(value);
  Serial.println("'");

  String trimmedValue = value;
  trimmedValue.trim();
  trimmedValue.toLowerCase();
  if (trimmedValue.equals("true")) {
    Serial.println("is true!!");
    *(bool*)ptr = true;
  } 
  else if (trimmedValue.equals("false")) {
    Serial.println("is false!!");
    *(bool*)ptr = false;
  } 
  else {
    Serial.println("Unknown bool value");
  }
}

Variable variables[] = {
    {"currentAuxPage", &currentAuxPage, updateInt},
    {"auxOutOpt", &auxOutOpt, updateInt},
    {"HPVol", &HPVol, updateFloat},
    {"SPVol", &SPVol, updateFloat},
    {"AUXVol", &AUXVol, updateFloat},
    {"gainOut", &gainOut, updateInt},
    {"backingActive", &backingActive, updateBool},
    {"backingVol", &backingVol, updateFloat},
    {"currentEffect", &currentEffect, updateInt},
    {"flangeActive", &flangeActive, updateBool},
    {"s_freq", &s_freq, updateFloat},
    {"chorusActive", &chorusActive, updateBool},
    {"n_chorus", &n_chorus, updateInt},
    {"reverbActive", &reverbActive, updateBool},
    {"revRoomsize", &revRoomsize, updateFloat},
    {"revDamping", &revDamping, updateFloat},
    {"delayActive", &delayActive, updateBool},
    {"delayTime", &delayTime, updateInt},
    {"currentEQPage", &currentEQPage, updateInt},
    {"EQActive", &EQActive, updateBool},
    {"bassBand", &bassBand, updateFloat},
    {"midBassBand", &midBassBand, updateFloat},
    {"midRangeBand", &midRangeBand, updateFloat},
    {"midTrebleBand", &midTrebleBand, updateFloat},
    {"trebleBand", &trebleBand, updateFloat},
    {"bassBoostActive", &bassBoostActive, updateBool},
    {"lr_lev", &lr_lev, updateFloat},
    {"bass_lev", &bass_lev, updateFloat},
    {"hpf_bypass", &hpf_bypass, updateInt},
    {"cutoff", &cutoff, updateInt},
    {"rgbActive", &rgbActive, updateBool},
    {"rgbBrightness", &rgbBrightness, updateFloat},
    {"screenBrightness", &screenBrightness, updateFloat},
    {"softwareVer", &softwareVer, updateString}
  };

const int numVariables = sizeof(variables) / sizeof(variables[0]);

void updateVariableByName(const String& name, const String& value) {
  for (int i = 0; i < numVariables; i++) {
    if (variables[i].name == name) {
      // Call the update function associated with the variable
      variables[i].updateFunction(variables[i].pointer, value);
      return;
    }
  }
  Serial.print("Variable name '");
  Serial.print(name);
  Serial.println("' not found.");
}
//blanket update all values in txt file with their variables value in the program
void writeUpdatedValues() {

  File file = SD.open("data.txt", FILE_READ);
  if (!file) {
    Serial.println("Failed to open file for reading.");
    return;
  }

  String fileContent;
  while (file.available()) {
    fileContent += (char)file.read();
  }
  file.close();

  // Update the file content with new variable values
  for (int i = 0; i < numVariables; i++) {
    String key = variables[i].name;
    String newValue;
    void* ptr = variables[i].pointer;

    if (ptr == nullptr) continue;

    if (variables[i].updateFunction == updateFloat) {
      newValue = String(*(float*)ptr, 6);
    } else if (variables[i].updateFunction == updateInt) {
      newValue = String(*(int*)ptr);
    } else if (variables[i].updateFunction == updateString) {
      newValue = *(String*)ptr;
    } else if (variables[i].updateFunction == updateBool) {
      newValue = (*(bool*)ptr) ? "true" : "false";
    }

    int keyIndex = fileContent.indexOf(key + "=");
    if (keyIndex != -1) {
      int valueStart = keyIndex + key.length() + 1;
      int valueEnd = fileContent.indexOf('\n', valueStart);
      if (valueEnd == -1) valueEnd = fileContent.length();
      fileContent = fileContent.substring(0, valueStart) + newValue + fileContent.substring(valueEnd);
    } else {
      fileContent += "\n" + key + "=" + newValue;
    }
  }

  // Debug: Print the updated file content
  Serial.println("Updated file content:");
  Serial.println(fileContent);

  // Write the updated content back to the file
  file = SD.open("data.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing.");
    return;
  }

  file.print(fileContent);
  file.close();
  Serial.println("File updated successfully.");
}


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

typedef void (*FunctionPointer)();
FunctionPointer landingFunctions[] = { FXMainPage, EQPage, audioPage, RGBPage, settingsPage };

void landingPage() { 
  hoverOptionSelector();

  bool choosing = true;

  while (choosing == true) {
    int EncRes;
    //current option Control Encoder Check
    param = currentHoverOption;
    EncRes = EncDialCheck(3, param, 4.0, 0.0);
    if (EncRes == 2) {
      currentHoverOption++;
      hoverOptionSelector();
    } 
    if (EncRes == 1) {
      currentHoverOption--;
      hoverOptionSelector();
    }
    
    if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      choosing = false;
    }
  }

  landingFunctions[currentHoverOption]();;
}

void hoverOptionSelector() {
    display.clearDisplay();
    setLandingPage();
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
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }

  while (true) {
    char title[] = {"Settings"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();
    checkHomeButton();
  }
}


void RGBPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  while (true) {
    char title[] = {"RGB Lighting"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();
    checkHomeButton();
  }
}

void masterAuxPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  currentAuxPage = 0;
  while (true) {
    char title[] = {"Aux #1 Master Vol"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);
    display.setCursor(1, 20);
    display.print("MasVol:");
    display.setCursor(10, 35);
    display.println(masterVolume);
    display.setCursor(55, 20);
    display.print("Gain:");
    display.setCursor(60, 35);
    display.println(gainOut);
    display.display();

    checkHomeButton();

    //Master volume Control Encoder Check
    int EncRes;
    param = masterVolume;
    EncRes = EncDialCheck(0, param, 1.0, 0.0);
    if (EncRes == 2) {
      masterVolume = masterVolume + 0.05;
      audioShield.volume(masterVolume);
    } 
    if (EncRes == 1) {
      masterVolume = masterVolume - 0.05;
      audioShield.volume(masterVolume);
    }
    //Master Gain out Control Encoder Check
    param = gainOut;
    EncRes = EncDialCheck(1, param, 31, 13);
    if (EncRes == 2) {
      gainOut = gainOut + 1;
      audioShield.lineOutLevel(gainOut);
    } 
    if (EncRes == 1) {
      gainOut = gainOut - 1;
      audioShield.lineOutLevel(gainOut);
    }



    cycleAux(3, currentAuxPage, 1.0, 0.0);//Check FX selected change 
    
  }
}


void backTrackAuxPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  currentAuxPage = 1;
  while (true) {
    char title[] = {"Aux #2 Back Track"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);
    display.setCursor(1, 20);
    display.print("Line I/O:");
    display.setCursor(10, 35);
    display.println(backingActive);
    display.setCursor(55, 20);
    display.print("BackVol:");
    display.setCursor(60, 35);
    display.println(gainOut);
    display.display();

    checkHomeButton();

    //Master volume Control Encoder Check
    int EncRes;
    param = masterVolume;
    EncRes = EncDialCheck(0, param, 1.0, 0.0);
    if (EncRes == 2) {
      masterVolume = masterVolume + 0.05;
      audioShield.volume(masterVolume);
    } 
    if (EncRes == 1) {
      masterVolume = masterVolume - 0.05;
      audioShield.volume(masterVolume);
    }
    //Master Gain out Control Encoder Check
    param = gainOut;
    EncRes = EncDialCheck(1, param, 31, 13);
    if (EncRes == 2) {
      gainOut = gainOut + 1;
      audioShield.lineOutLevel(gainOut);
    } 
    if (EncRes == 1) {
      gainOut = gainOut - 1;
      audioShield.lineOutLevel(gainOut);
    }



    cycleAux(3, currentAuxPage, 1.0, 0.0);//Check Aux selected change 
    
  }
}
typedef void (*FunctionPointer)();
FunctionPointer auxFunctions[] = { masterAuxPage, backTrackAuxPage  };

void audioPage() {
    while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    // Debounce delay
    delay(50);
  }
  auxFunctions[currentAuxPage]();;
}

void cycleAux(int encNo, int param, int maxRange, int minRange) {
    int EncRes;
    EncRes = EncDialCheck(encNo, param, maxRange, minRange);
    if (EncRes == 2) {
        auxFunctions[param + 1]();;
    } 
    if (EncRes == 1) {
        auxFunctions[param - 1]();;
    }  
}

void EQPage() {
  while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
  }
  while (true) {
    char title[] = {"EQ"};
    bool notFX = false;
    setFXTemplatePage(title, notFX, false);

    display.display();
    checkHomeButton();
  }
}

void flangeFX() {
    currentEffect = 0;
    while (true) {
        char title[] = {"FX #1 Flange"};
        setFXTemplatePage(title, flangeActive, true);
        display.setCursor(10, 20);
        display.print("Freq:");
        display.setCursor(24, 35);
        display.println(s_freq);
        display.display();

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
        cycleFX(3, currentEffect, 3.0, 0.0);
    }
}

void chorusFX() {
    currentEffect = 1;
    while (true) {
        char title[] = {"FX #2 Chorus"};
        setFXTemplatePage(title, chorusActive, true);
        
        display.setCursor(10, 20);
        display.print("Voices:");
        display.setCursor(24, 35);
        display.println(n_chorus);

        display.display();
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
        cycleFX(3, currentEffect, 3.0, 0.0); //Check FX selected change 
    }
}

void reverbFX() {
    currentEffect = 2;
    while (true) {
        char title[] = {"FX #3 Reverb"};
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
        cycleFX(3, currentEffect, 3.0, 0.0);//Check FX selected change 
    }
}


void delayFX() {
    currentEffect = 3;
    while (true) {
        char title[] = {"FX #4 Delay"};
        setFXTemplatePage(title, delayActive, true);
        display.setCursor(10, 20);
        display.print("Time Ms:");
        display.setCursor(24, 35);
        display.println(delayTime);
        display.display();
        
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
         
        cycleFX(3, currentEffect, 3.0, 0.0);//Check FX selected change
    }
}

typedef void (*FunctionPointer)();
FunctionPointer FXfunctions[] = { flangeFX, chorusFX, reverbFX, delayFX  };

void checkHomeButton() {
  int buttonState = digitalRead(buttonPin); 
  if (buttonState == LOW) {

    writeUpdatedValues();
    
    delay(500); 
    landingPage();
  }
}

int EncDialCheck(int encNo, float paramValue, float maxRange, float minRange) {
    int32_t enc_pos = ss.getEncoderPosition(encNo);
    if (enc_positions[0] != enc_pos) {
        int change = enc_pos - enc_positions[encNo];
        enc_positions[encNo] = enc_pos;

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
      if (FXActive == false){
          FXActive = true;
          mixer_sw.gain(0, 0);
          mixer_sw.gain(1, 1);
      }
      else {
          FXActive = false;
          mixer_sw.gain(0, 1);
          mixer_sw.gain(1, 0);
      }         
    }

    while (!ss.digitalRead(SS_ENC3_SWITCH)) {
    delay(50);
    }
}

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

void setFXTemplatePage(char title[], bool& FXActive, bool fxCheck) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont(NULL);
  display.setCursor(0, 10);
  display.setCursor(0, 5);
  display.setTextWrap(0);
  display.setCursor(28, 5);
  display.println(title);
  display.drawLine(0, 18, 128, 18, 1);
  display.drawRect(109, 50, 17, 12, 1);
  display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
  display.drawRect(2, 50, 17, 12, 1);
  display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
  display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
  display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
  display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
  if (fxCheck) {
    if (FXActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
  }
}