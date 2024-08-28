#ifndef FX_PAGES_H
#define FX_PAGES_H


#include "config.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"

void flangeFX();
void chorusFX();
void reverbFX();
void delayFX();
void cycleFX(int encNo, int param, int maxRange, int minRange);
void FXMainPage();

#endif