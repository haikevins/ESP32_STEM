#include "rgbled_manager.h"

RGBLEDManager::RGBLEDManager()
  : strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800) {
}

RGBLEDManager::~RGBLEDManager() {
  // Destructor logic nếu cần
}

void RGBLEDManager::Init() {
  strip.begin();
  strip.show();  // Tắt hết LED ban đầu
}

void RGBLEDManager::Set_Color(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
