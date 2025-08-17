#include "hcsr04_manager.h"

HCSR04Manager::HCSR04Manager() {
}

HCSR04Manager::~HCSR04Manager() {
}

void HCSR04Manager::Init() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float HCSR04Manager::Read_Distance() {
  // Phát xung trigger 10µs
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Đo thời gian echo
  duration = pulseIn(ECHO_PIN, HIGH);
  // Tính khoảng cách (đơn vị cm)
  distance = duration * 0.0343 / 2;  // Tính khoảng cách theo công thức: distance = (duration * speed of sound) / 2

  return distance;
}
