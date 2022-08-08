#include <Wire.h>

#define VOLTAGE_METER_PIN A0
#define SOLENOID_PIN 7

int battery_voltage = 0;

void setup() {
  Wire.begin(8); // join i2c bus with address #8
  Wire.onRequest(requestEvent); // trigger function when request by master
  Serial.begin(115200);
}

void loop() {
  battery_voltage = map(analogRead(VOLTAGE_METER_PIN),0,1023,0,255);
  Serial.print(battery_voltage);
  Serial.print(":");
  Serial.println(char(battery_voltage));
  delay(20);
}

void requestEvent() {
  Wire.write(char(battery_voltage));
}