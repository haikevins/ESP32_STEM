#include "gy33_manager.h"
#include <Wire.h>

GY33Manager::GY33Manager()
  : tcs(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X) {
}

GY33Manager::~GY33Manager() {
}

void GY33Manager::Init() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!tcs.begin()) {
    Serial.println("Sensor not found! Please check I2C connection.");
    return;
  }
  Serial.println("GY-33/TCS34725 sensor detected!");

  Calibrate_Factor();
  Calibrate_Colors();
}

// Hiệu chuẩn hệ số calR, calG, calB
void GY33Manager::Calibrate_Factor() {
  uint16_t r, g, b, c;
  Serial.println("Place a White sample to calibrate calR, calG, calB factors...");
  delay(5000);  // Thời gian đặt mẫu trắng
  tcs.getRawData(&r, &g, &b, &c);

  calR = (r > 0) ? 255.0 / r : 1.0;
  calG = (g > 0) ? 255.0 / g : 1.0;
  calB = (b > 0) ? 255.0 / b : 1.0;

  Serial.printf("Calibration factors: R= %.2f, G= %.2f, B= %.2f\n", calR, calG, calB);
}

// Hiệu chuẩn tất cả các màu
void GY33Manager::Calibrate_Colors() {
  uint16_t r, g, b, c;
  for (int i = 0; i < NUM_COLORS; i++) {
    if (i < NUM_COLORS - 1) {
      Serial.print("Place a sample for color: ");
      Serial.println(color_names[i]);
    } else {
      Serial.println("Leave no color");
    }

    delay(5000);  // Thời gian đặt mẫu
    tcs.getRawData(&r, &g, &b, &c);

    color_cal[i].r = constrain(round(r * calR), 0, 255);
    color_cal[i].g = constrain(round(g * calG), 0, 255);
    color_cal[i].b = constrain(round(b * calB), 0, 255);

    Serial.print("Saved color ");
    Serial.print(color_names[i]);
    Serial.print(": ");
    Serial.print(color_cal[i].r);
    Serial.print(" ");
    Serial.print(color_cal[i].g);
    Serial.print(" ");
    Serial.println(color_cal[i].b);
  }
  Serial.println("Finished calibrating all colors!");
}

// Tìm màu gần nhất
const char *GY33Manager::Detect_Color(uint8_t &rMeas, uint8_t &gMeas, uint8_t &bMeas) {
  int closestIndex = 0;
  float minDist = 1e6;

  for (int i = 0; i < NUM_COLORS; i++) {
    float dr = rMeas - color_cal[i].r;
    float dg = gMeas - color_cal[i].g;
    float db = bMeas - color_cal[i].b;
    float dist = dr * dr + dg * dg + db * db;

    if (dist < minDist) {
      minDist = dist;
      closestIndex = i;
    }
  }
  return color_names[closestIndex];
}

// Đọc màu thực tế
const char *GY33Manager::Read_Color(uint8_t &rOut, uint8_t &gOut, uint8_t &bOut) {
  uint16_t rRaw, gRaw, bRaw, c;
  tcs.getRawData(&rRaw, &gRaw, &bRaw, &c);

  rOut = constrain(round(rRaw * calR), 0, 255);
  gOut = constrain(round(gRaw * calG), 0, 255);
  bOut = constrain(round(bRaw * calB), 0, 255);

  return Detect_Color(rOut, gOut, bOut);
}
