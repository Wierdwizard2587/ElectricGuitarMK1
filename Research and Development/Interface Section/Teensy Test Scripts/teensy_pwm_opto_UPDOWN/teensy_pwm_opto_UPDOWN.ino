const int ledPin = 13; // LED pin
const int buttonUpPin = 2; // Button to increase PWM pin
const int buttonDownPin = 3; // Button to decrease PWM pin

int pwmValue = 0; // Initial PWM value
const int pwmIncrement = 10; // Increment/decrement step for PWM value

bool lastButtonUpState = HIGH;
bool lastButtonDownState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  // Read button states
  bool buttonUpState = digitalRead(buttonUpPin);
  bool buttonDownState = digitalRead(buttonDownPin);
  
  if (buttonUpState == LOW && lastButtonUpState == HIGH) {
    increasePWM();
  }
  
  if (buttonDownState == LOW && lastButtonDownState == HIGH) {
    decreasePWM();
  }
  
  lastButtonUpState = buttonUpState;
  lastButtonDownState = buttonDownState;
  
  // Update LED brightness
  analogWrite(ledPin, pwmValue);
}

void increasePWM() {
  pwmValue += pwmIncrement;
  if (pwmValue > 255) {
    pwmValue = 255;
  }
  Serial.print("PWM increased to: ");
  Serial.println(pwmValue);
  delay(200); // Debouncing delay
}

void decreasePWM() {
  pwmValue -= pwmIncrement;
  if (pwmValue < 0) {
    pwmValue = 0;
  }
  Serial.print("PWM decreased to: ");
  Serial.println(pwmValue);
  delay(200); // Debouncing delay
}