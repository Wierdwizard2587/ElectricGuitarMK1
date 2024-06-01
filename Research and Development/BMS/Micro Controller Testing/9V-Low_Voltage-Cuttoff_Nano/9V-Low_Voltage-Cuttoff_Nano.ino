const int analogPin = A5;  // Analog input pin that the voltage divider is connected to
const int digitalPin = 2;  // Digital output pin that the optocoupler is connected to
const float referenceVoltage = 5.0;  // Reference voltage of the Arduino (typically 5V)
const float voltageDividerFactor = 2.0;  // Factor for the voltage divider (R1 = R2, so factor is 2)

void setup() {
  pinMode(digitalPin, OUTPUT);  // Set the digital pin as output
}

void loop() {
  int analogValue = analogRead(analogPin);  // Read the analog value (0-1023)
  float voltage = (analogValue / 1023.0) * referenceVoltage * voltageDividerFactor;  // Calculate the actual voltage

  if (voltage > 9.0) {
    digitalWrite(digitalPin, HIGH);  // Set the digital pin high if the voltage is above 9V
  } else {
    digitalWrite(digitalPin, LOW);  // Set the digital pin low if the voltage is below 9V
  }

  delay(100);  // Delay for a short period of time before the next reading
}
