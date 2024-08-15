
#ifndef FXControl_h
#define FXControl_h

#include "Arduino.h"


class FXControl
{
	public:
		void returnHome();
		bool toggleEffect(bool fxState);
		bool cycleEffect();

};

#endif