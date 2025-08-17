#ifndef __GY33_MANAGER_H__
#define __GY33_MANAGER_H__

#include <Arduino.h>
#include <Adafruit_TCS34725.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define NUM_COLORS 11

class GY33Manager {
private:
  float calR = 1.0, calG = 1.0, calB = 1.0;

  struct RGB {
    uint8_t r, g, b;
  } color_cal[NUM_COLORS];

  Adafruit_TCS34725 tcs;

  const char *color_names[NUM_COLORS] = {
    "White", "Black", "Green", "Light Green", "Yellow",
    "Dark Green", "Pink", "Orange", "Red", "Purple", "Unknown"
  };

public:
  GY33Manager();
  ~GY33Manager();

  void Init();
  void Calibrate_Factor();
  void Calibrate_Colors();
  const char *Detect_Color(uint8_t &rMeas, uint8_t &gMeas, uint8_t &bMeas);
  const char *Read_Color(uint8_t &rOut, uint8_t &gOut, uint8_t &bOut);
};

#endif  // __GY33_MANAGER_H__
