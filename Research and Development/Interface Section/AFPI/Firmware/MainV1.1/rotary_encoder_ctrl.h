#ifndef ROTARY_ENCODER_CTRL_H
#define ROTARY_ENCODER_CTRL_H

#include "config.h"

#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

// Pin definitions
#define SS_NEO_PIN       18
#define SS_ENC0_SWITCH   12
#define SS_ENC1_SWITCH   14
#define SS_ENC2_SWITCH   17
#define SS_ENC3_SWITCH   9

// I2C address for Seesaw
#define SEESAW_ADDR      0x49

// Object declarations
extern Adafruit_seesaw ss;
extern seesaw_NeoPixel pixels;

// Encoder positions array
extern int32_t enc_positions[4];

// Function declarations
void initializeEncoders();
int EncDialCheck(int encNo, float paramValue, float maxRange, float minRange);
void EncToggleCheck(bool& FXActive, AudioMixer4& mixer_sw);

uint32_t Wheel(byte WheelPos);
#endif