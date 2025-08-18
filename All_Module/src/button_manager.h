#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__

#include <Arduino.h>

#define BUTTON_PIN 36

#define BUTTON_DEBOUNCE_SAMPLE 16
#define BUTTON_HIGH_THRESHOLD 70

class ButtonManager {
private:
  uint64_t button_log = 0;
  bool pressed_flag = 0;
  uint8_t sample_count = 0;
  bool last_state = HIGH;  //pull_up

public:
  ButtonManager();
  virtual ~ButtonManager();

  void Init(void);
  void Update(void);
  void Reset_Status(void);
  bool Get_Status(void);
};

#endif /* __BUTTON_MANAGER_H__ */