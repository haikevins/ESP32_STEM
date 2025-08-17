#include "relay_manager.h"

RelayManager::RelayManager() {
}

RelayManager::~RelayManager() {
}

void RelayManager::Init() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Ensure relay is off initially
}

void RelayManager::Turn_On() {
  digitalWrite(RELAY_PIN, HIGH);  // Turn on the relay
}

void RelayManager::Turn_Off() {
  digitalWrite(RELAY_PIN, LOW);  // Turn off the relay
}