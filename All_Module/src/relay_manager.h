#ifndef __RELAY_MANAGER_H__
#define __RELAY_MANAGER_H__

#include <Arduino.h>

#define RELAY_PIN 4  // Define the pin for the relay

class RelayManager {
private:
public:
  RelayManager();
  virtual ~RelayManager();

  void Init();
  void Turn_On();
  void Turn_Off();
};

#endif  // __RELAY_MANAGER_H__