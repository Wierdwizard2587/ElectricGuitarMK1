#include <SD.h>
#include <SPI.h>

#define SD_CS_PIN 10  // CS pin for Teensy Audio Shield SD card reader

// Embedded content of data.txt as a string. Ensure this matches exactly what you want to write to the SD card.
const char *dataContent = R"(
//Audio Processing
lineMix=0.0
backingMix=0.0
backingActive=false
currentAudioOutput=0
HPVol=0.0
HPGainOut=13
SPVol=0.0
SPGainOut=13
AUXVol=0.0
AuxGainOut=13

//Equaliser
EQActive=false
bassBand=0.0
midBassBand=0.0
midRangeBand=0.0
midTrebleBand=0.0
trebleBand=0.0

//EQ bass values
bassBoostActive=false
lr_lev=0.0
bass_lev=0.5
hpf_bypass=0
cutoff=6

//Current Page Sections
currentEQPage=0
currentAuxPage=0
currentHoverOption=0
currentEffect=2

//FX Sections

//distortion values
distortActive=false

//flange values
flangeActive=true
s_freq=0.5

//chorus values
chorusActive=true
n_chorus=2

//reverb values
reverbActive=true
revRoomsize=0.0
revDamping=0.0

//delay values
delayActive=true
delayTime=200

//rgb values
rgbActive=false
rgbBrightness=0.0
rgbColour=0
rgbEffect=0

//settings values
oledContrast=255
lowPwrMode=false
)";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for Serial to initialize
  }

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Failed to initialize SD card");
    return;
  }

  // Attempt to update the file on the SD card
  if (updateSDCardFile()) {
    Serial.println("File updated successfully on SD card!");
  } else {
    Serial.println("Failed to update the file on the SD card.");
  }
}

void loop() {
  // Main loop does nothing
}

// Function to update the SD card file with the embedded data content
bool updateSDCardFile() {
  // Open the target file on the SD card, create or truncate the existing file
  File targetFile = SD.open("/data.txt", FILE_WRITE);
  if (!targetFile) {
    Serial.println("Failed to open data.txt on SD card for writing.");
    return false;
  }

  // Write the embedded data content to the target file
  targetFile.print(dataContent);

  // Close the file
  targetFile.close();

  // Check if the file was written successfully
  return true;
}
