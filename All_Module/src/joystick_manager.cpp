#include "joystick_manager.h"

JoystickManager::JoystickManager() {
}

JoystickManager::~JoystickManager() {
}

void JoystickManager::Init() {
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);  // Use pull-up resistor for button
}

void JoystickManager::Read(int &x, int &y) {
  x = analogRead(VRX_PIN);  // Read X-axis value
  y = analogRead(VRY_PIN);  // Read Y-axis value
}