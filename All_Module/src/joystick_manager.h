#ifndef __JOYSTICK_MANAGER_H__
#define __JOYSTICK_MANAGER_H__

#include <Arduino.h>

#define VRX_PIN 39  // Chân ADC cho trục X
#define VRY_PIN 34  // Chân ADC cho trục Y
#define SW_PIN 36   // Chân digital cho nút nhấn

class JoystickManager {
private:
public:
  JoystickManager();
  virtual ~JoystickManager();

  void Init();
  void Read(int &x, int &y);
};
#endif  // __JOYSTICK_MANAGER_H__
