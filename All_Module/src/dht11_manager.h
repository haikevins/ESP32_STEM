#ifndef __DHT11_MANAGER_H__
#define __DHT11_MANAGER_H__

#include <Arduino.h>

#define DHTTYPE DHT11  // Loại cảm biến
#define DHTPIN 32      // Chân DATA
#define CTRL_PIN 33    // Chân điều khiển nguồn

class DHT11Manager {
private:
  /* data */
public:
  DHT11Manager(/* args */);
  virtual ~DHT11Manager();

  void Init();
  void Read_Sensor(float &temperature, float &humidity);
};

#endif  // __DHT11_MANAGER_H__
