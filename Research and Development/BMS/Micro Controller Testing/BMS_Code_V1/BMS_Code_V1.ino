#include <DS18B20.h>

#define BATTERY_PIN A3
#define RELAY_PIN_1 1
#define RELAY_PIN_2 2
#define RELAY_PIN_3 4

#define BATTERY_THRESHOLD_HIGH 106   // Equivalent to 10.6V
#define BATTERY_THRESHOLD_LOW 109    // Equivalent to 10.9V
#define TEMPERATURE_THRESHOLD_LOW 38 // Below 38 degrees Celsius
#define TEMPERATURE_THRESHOLD_HIGH 58 // Above 58 degrees Celsius

DS18B20 ds(2); // Initialize DS18B20 sensor
uint8_t address[] = {40, 250, 31, 218, 4, 0, 0, 52}; // Address of DS18B20 sensor
//uint8_t selected; // Flag to indicate if sensor is found

void setup() {
  pinMode(BATTERY_PIN, INPUT);
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);

  ds.select(address);
  ds.setAlarms(TEMPERATURE_THRESHOLD_LOW, TEMPERATURE_THRESHOLD_HIGH);

}

void loop() {
  float batteryVoltage = getBatteryVoltage();
  float temperature;

  if (ds.hasAlarm()) {
    temperature = ds.getTempC();
    if (temperature < TEMPERATURE_THRESHOLD_LOW) {
      digitalWrite(RELAY_PIN_1, HIGH);
    } else {
      digitalWrite(RELAY_PIN_1, LOW);
    }
    if (temperature > TEMPERATURE_THRESHOLD_HIGH) {
      digitalWrite(RELAY_PIN_3, HIGH);
    } else {
      digitalWrite(RELAY_PIN_3, LOW);
    }
  }

  if (batteryVoltage > BATTERY_THRESHOLD_HIGH) {
    digitalWrite(RELAY_PIN_2, HIGH);
  } else if (batteryVoltage < BATTERY_THRESHOLD_LOW) {
    digitalWrite(RELAY_PIN_2, LOW);
  }

  delay(10000); // Adjust delay as needed
}

float getBatteryVoltage() {
  int rawValue = analogRead(BATTERY_PIN);
  return map(rawValue, 0, 1023, 104, 144) / 10.0; // Map the analog value to voltage
}
