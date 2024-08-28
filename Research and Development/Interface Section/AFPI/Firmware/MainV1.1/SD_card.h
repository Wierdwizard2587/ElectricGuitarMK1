#ifndef SD_Card_H
#define SD_CARD_H

#include "config.h"
#include <regex>

struct Variable {
    String name;
    void* pointer;
    void (*updateFunction)(void*, const String&);
};

extern Variable variables[];
extern const int numVariables;
extern const int chipSelect;

void readStoredValues();
String readLine(File &file);
void parseAndUpdate(const String& line);
void updateFloat(void* ptr, const String& value);
void updateInt(void* ptr, const String& value);
void updateString(void* ptr, const String& value);
void updateBool(void* ptr, const String& value);
void updateVariableByName(const String& name, const String& value);
void writeUpdatedValues();

void initialiseSDCard();

#endif