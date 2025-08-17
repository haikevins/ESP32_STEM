#include "varistor_manager.h"

VaristorManager::VaristorManager(/* args */) {
}

VaristorManager::~VaristorManager() {
}

void VaristorManager::Init() {
  pinMode(VARISTOR_PIN, INPUT);  // Thiết lập chân varistor là đầu vào
}

void VaristorManager::Read(float &voltage) {
  // Đọc giá trị điện áp từ varistor
  int sensorValue = analogRead(VARISTOR_PIN);
  voltage = sensorValue * (3.3 / 4095.0);  // Chuyển đổi giá trị ADC sang điện áp
}