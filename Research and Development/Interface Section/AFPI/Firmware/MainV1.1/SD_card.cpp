#include "SD_card.h"
#include "audio_processing.h"
const int chipSelect = 10;

//#include "config.h"

void initialiseSDCard() {
    if (!SD.begin(chipSelect)) {
    //Serial.println("SD card initialization failed!");
    return;
    }

    readStoredValues();
}



// Define your variables
Variable variables[] = {
    {"currentAuxPage", &currentAuxPage, updateInt},
    {"currentAudioOutput", &currentAudioOutput, updateInt},
    {"HPVol", &HPVol, updateFloat},
    {"SPVol", &SPVol, updateFloat},
    {"AUXVol", &AUXVol, updateFloat},
    {"HPGainOut", &HPGainOut, updateInt},
    {"SPGainOut", &SPGainOut, updateInt},
    {"AuxGainOut", &AuxGainOut, updateInt},
    {"lineMix", &lineMix, updateFloat},
    {"backingMix", &backingMix, updateFloat},
    {"backingActive", &backingActive, updateBool},

    {"distortActive", &distortActive, updateBool},
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
    {"rgbBrightness", &rgbBrightness, updateInt},
    {"rgbColour", &rgbColour, updateInt},
    {"rgbEffect", &rgbEffect, updateInt},
    {"oledContrast", &oledContrast, updateInt}
    
};

const int numVariables = sizeof(variables) / sizeof(variables[0]);

void readStoredValues() {
    File dataFile = SD.open("data.txt");
    if (dataFile) {
        while (dataFile.available()) {
            String line = readLine(dataFile);
            if (line.length() > 0 && !line.startsWith("//")) {
                parseAndUpdate(line);
            }
        }
        dataFile.close();
    }
}

String readLine(File &file) {
    String line = "";
    while (file.available()) {
        char c = file.read();
        if (c == '\n') {
            break;
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

    updateVariableByName(key, value);
}

void updateFloat(void* ptr, const String& value) {
    *(float*)ptr = value.toFloat();
}

void updateInt(void* ptr, const String& value) {
    *(int*)ptr = value.toInt();
}

void updateString(void* ptr, const String& value) {
    *(String*)ptr = value;
}

void updateBool(void* ptr, const String& value) {
    String trimmedValue = value;
    trimmedValue.trim();
    trimmedValue.toLowerCase();
    if (trimmedValue.equals("true")) {
        *(bool*)ptr = true;
    } else if (trimmedValue.equals("false")) {
        *(bool*)ptr = false;
    }
}

void updateVariableByName(const String& name, const String& value) {
    for (int i = 0; i < numVariables; i++) {
        if (variables[i].name == name) {
            variables[i].updateFunction(variables[i].pointer, value);
            return;
        }
    }
}

void writeUpdatedValues() {
    File file = SD.open("data.txt", FILE_READ);
    if (!file) {
        return;
    }

    String fileContent;
    while (file.available()) {
        fileContent += (char)file.read();
    }
    file.close();

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

    file = SD.open("data.txt", FILE_WRITE);
    if (!file) {
        return;
    }

    file.print(fileContent);
    file.close();

}