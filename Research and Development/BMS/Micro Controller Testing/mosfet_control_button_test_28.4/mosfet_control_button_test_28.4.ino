const int buttonPin = 2;    // Push button connected to pin 2
const int mosfetPin = 0;   // MOSFET gate connected to pin 13
const int ledPin = 1;
bool ledState = false;      // variable for storing the LED state

void setup() {
  pinMode(ledPin, OUTPUT);  // Built-in LED pin as output
  pinMode(mosfetPin, OUTPUT);    // MOSFET gate pin as output
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor for button pin
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Read the state of the push button
  
  if (buttonState == LOW) {  // If push button is pressed (LOW due to pull-up resistor)
    // Toggle LED state
    ledState = !ledState;
    // Set both LEDs accordingly
    digitalWrite(ledPin, ledState ? HIGH : LOW);  // Built-in LED
    digitalWrite(mosfetPin, ledState ? HIGH : LOW);    // MOSFET gate LED
    // Wait for button release to avoid multiple toggles
    while (digitalRead(buttonPin) == LOW) {}
    // Add a small delay to debounce
    delay(50);
  }
}
