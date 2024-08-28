#ifndef LANDING_PAGE_H
#define LANDING_PAGE_H


#include "config.h"
#include "rotary_encoder_ctrl.h"
#include "display.h"
#include "settings_page.h"

typedef void (*FunctionPointer)();
extern FunctionPointer landingFunctions[];

void landingPage();
void hoverOptionSelector();
void setLandingPage();
#endif