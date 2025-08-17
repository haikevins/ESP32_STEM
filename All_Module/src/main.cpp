#include "gy33_manager.h"
#include "relay_manager.h"
#include "dht11_manager.h"
#include "motor_manager.h"
#include "hcsr04_manager.h"
#include "rgbled_manager.h"
#include "button_manager.h"
#include "dfplayer_manager.h"
#include "varistor_manager.h"
#include "joystick_manager.h"

GY33Manager gy33Manager;
DHT11Manager dht11Manager;
RelayManager relayManager;
MotorManager motorManager;
RGBLEDManager rgbLedManager;
HCSR04Manager hcsr04Manager;
ButtonManager buttonManager;
JoystickManager joystickManager;
VaristorManager varistorManager;
DFPlayerManager dfPlayerManager;

#define THRESHOLD_TIME 1000

void setup() {
  Serial.begin(115200);
  delay(1000);  // Đợi Serial ổn định

  Serial.println("Initializing...");
  // Khởi tạo các module
  gy33Manager.Init();
  relayManager.Init();
  dht11Manager.Init();
  hcsr04Manager.Init();
  buttonManager.Init();
  rgbLedManager.Init();
  varistorManager.Init();
  joystickManager.Init();

  if (!dfPlayerManager.Init(9600)) {
    Serial.println("DFPlayer initialization failed!");
  } else {
    Serial.println("DFPlayer initialized successfully!");
    dfPlayerManager.Set_Volume(20);
  }

  if (!motorManager.Init()) {
    Serial.println("Motor initialization failed!");
  } else {
    Serial.println("Motor initialized successfully!");
  }

  Serial.println("Init complete!");
}

void loop() {
  static unsigned long last_time = 0;

  if (millis() - last_time >= THRESHOLD_TIME) {
    last_time = millis();

    // DHT11
    float temperature, humidity;
    dht11Manager.Read_Sensor(temperature, humidity);
    Serial.printf("Temperature: %.2f oC, Humidity: %.2f %%\n", temperature, humidity);

    // HC-SR04
    float distance = hcsr04Manager.Read_Distance();
    Serial.printf("Distance: %.2f cm\n", distance);

    // Varistor
    float voltage;
    varistorManager.Read(voltage);
    Serial.printf("Varistor Voltage: %.2f V\n", voltage);

    // Relay
    static bool relayState = false;
    if (!relayState) {
      relayManager.Turn_On();
      relayState = true;
    } else {
      relayManager.Turn_Off();
      relayState = false;
    }

    // GY 33
    uint8_t r, g, b;
    const char* colorName = gy33Manager.Read_Color(r, g, b);
    Serial.printf("Color: %s", colorName);
    Serial.printf(" (R: %d, G: %d, B: %d)\n", r, g, b);

    // RGB LED
    rgbLedManager.Set_Color(r, g, b);
  }

  // DF Player
  static int button_flag = 0;
  if (buttonManager.Get_Status() == 1) {
    buttonManager.Reset_Status();
    if (button_flag == 0) {
      Serial.println("Button Pressed!");
      button_flag = 1;
      dfPlayerManager.Play(1);  // Play first track
    } else {
      Serial.println("Button Released!");
      button_flag = 0;
      dfPlayerManager.Stop();  // Stop playback
    }
  }
}
