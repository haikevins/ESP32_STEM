#ifndef __RGBLED_MANAGER_H__
#define __RGBLED_MANAGER_H__

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 15   // Chân DIN của LED RGB
#define NUM_LEDS 15  // Số lượng LED nối tiếp

class RGBLEDManager {
private:
  Adafruit_NeoPixel strip;
public:
  RGBLEDManager();
  virtual ~RGBLEDManager();

  void Init();
  void Set_Color(uint8_t r, uint8_t g, uint8_t b);
};

#endif
