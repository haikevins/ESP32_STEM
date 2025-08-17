#ifndef __VARISTOR_MANAGER_H__
#define __VARISTOR_MANAGER_H__

#include <Arduino.h>

#define VARISTOR_PIN 35  // Chân kết nối với varistor

class VaristorManager {
private:
  /* data */
public:
  VaristorManager(/* args */);
  virtual ~VaristorManager();

  void Init();
  void Read(float &voltage);
};

#endif  // __VARISTOR_MANAGER_H__