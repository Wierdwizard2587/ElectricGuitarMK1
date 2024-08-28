#ifndef AUX_PAGES_H
#define AUX_PAGES_H


#include "config.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"

void masterAuxPage();
void backTrackAuxPage();

typedef void (*FunctionPointer)();
extern FunctionPointer auxFunctions[];

void audioPage();
void cycleAux(int encNo, int param, int maxRange, int minRange);

#endif