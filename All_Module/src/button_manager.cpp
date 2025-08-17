#include "button_manager.h"

ButtonManager::ButtonManager() {
}

ButtonManager::~ButtonManager() {
}

void ButtonManager::Init(void) {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Button initialized successfully!");
}

void ButtonManager::Update(void) {
  int input_value = digitalRead(BUTTON_PIN);
  button_log = button_log << 1;

  if (input_value == HIGH) {
    button_log |= 1;
  }

  if (sample_count < BUTTON_DEBOUNCE_SAMPLE) {
    sample_count++;
  } else {
    uint8_t logic_high_counter = 0;
    for (uint8_t i = 0; i < BUTTON_DEBOUNCE_SAMPLE; i++) {
      if ((button_log >> i) & 0x01) {
        logic_high_counter++;
      }
    }

    bool new_stable = (logic_high_counter * 100 / BUTTON_DEBOUNCE_SAMPLE) > BUTTON_HIGH_THRESHOLD;

    // Phát hiện nhả nút (HIGH → LOW)
    if (new_stable == LOW && last_state == HIGH) {
      pressed_flag = 1;
    } else {
      pressed_flag = 0;
    }

    last_state = new_stable;
  }
}

bool ButtonManager::Get_Status(void) {
  return pressed_flag;
}

void ButtonManager::Reset_Status(void) {
  pressed_flag = 0;
}