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


Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);
seesaw_NeoPixel pixels = seesaw_NeoPixel(4, SS_NEO_PIN, NEO_GRB + NEO_KHZ800, &Wire1);

int32_t enc_positions[4] = {0, 0, 0, 0};

const int buttonPin = 14;


void setup() {
  // put your setup code here, to run once:

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
  int currentHoverOption = 0;
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