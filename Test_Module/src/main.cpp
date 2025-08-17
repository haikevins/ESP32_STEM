#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  pinMode(35, INPUT); // Set GPIO 35 as input
}

void loop() {
  int value = analogRead(35); // Read the value from GPIO 35
  Serial.println(value);
  delay(1000); // Wait for a second before the next read
}
