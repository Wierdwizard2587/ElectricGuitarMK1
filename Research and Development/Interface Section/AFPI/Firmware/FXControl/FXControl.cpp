

#include "Arduino.h"
#include "FXControl.h"

FXControl::FXControl(int homePin)
{
	int homeButtonPin = buttonPin;

}

void FXControl::returnHome()
{
    int buttonState = digitalRead(homeButtonPin); 

    if (buttonState == LOW) {
      Serial.println("Home Button pressed!");
      delay(500); 
      landingPage();
    }
}

bool FXControl::toggleEffect(bool fxState)
{
	  if (!ss.digitalRead(SS_ENC3_SWITCH)) {
	  Serial.println("ENC3 pressed!");
	  Serial.println("effect is now on");

		  if (fxState == false){
		      Serial.print("effect now ON");
		      fxState = true;
		  }

		  else {
		      Serial.print("effect now OFF");
		      fxState = false;
		  }         
		}
		while (!ss.digitalRead(SS_ENC3_SWITCH)) {
		// Debounce delay
		delay(50);
		}

		return fxState;


}


bool FXControl::cycleEffect()
{
	
}

