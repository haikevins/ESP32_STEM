#include "dht11_manager.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

DHT dht(DHTPIN, DHTTYPE);

DHT11Manager::DHT11Manager(/* args */) {
}

DHT11Manager::~DHT11Manager() {
}

void DHT11Manager::Init() {
  pinMode(CTRL_PIN, OUTPUT);
  digitalWrite(CTRL_PIN, HIGH);  // Cấp nguồn cho DHT11
  delay(2000);                   // Chờ cảm biến ổn định

  dht.begin();
}

void DHT11Manager::Read_Sensor(float &temperature, float &humidity) {
  // Đọc nhiệt độ và độ ẩm từ cảm biến DHT11
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}
