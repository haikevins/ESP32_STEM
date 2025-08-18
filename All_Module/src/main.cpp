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
  Serial.begin(9600);
  delay(2000);  // Đợi Serial ổn định

  Serial.println("Initializing...");
  // Khởi tạo các module
  // gy33Manager.Init();
  relayManager.Init();
  dht11Manager.Init();
  hcsr04Manager.Init();
  buttonManager.Init();
  // rgbLedManager.Init();
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

    // GY 33
    uint8_t r, g, b;
    const char* colorName = gy33Manager.Read_Color(r, g, b);
    Serial.printf("Color: %s", colorName);
    Serial.printf(" (R: %d, G: %d, B: %d)\n", r, g, b);   

    // HCSR04
    float distance = hcsr04Manager.Read_Distance();
    Serial.printf("Distance: %.2f cm\n", distance);

    if (distance < 10.0) {
      relayManager.Turn_On();
    } else {
      relayManager.Turn_Off();
    }

    // DHT11
    float temperature, humidity;
    dht11Manager.Read_Sensor(temperature, humidity);
    Serial.printf("Temperature: %.2f oC, Humidity: %.2f %%\n", temperature, humidity);

    // Varistor
    float voltage;
    varistorManager.Read(voltage);
    Serial.printf("Varistor Voltage: %.2f V\n", voltage);
    if (voltage == 0.0) {
      dfPlayerManager.Set_Volume(0);
    } else if (voltage < 1.1) {
      dfPlayerManager.Set_Volume(10);
    } else if (voltage < 2.2) {
      dfPlayerManager.Set_Volume(20);
    } else if (voltage <= 3.3) {
      dfPlayerManager.Set_Volume(30);
    }

    // Joystick
    int x, y;
    joystickManager.Read(x, y);
    Serial.printf("Joystick Position: X: %d, Y: %d\n", x, y);

    // Motor Driver
    if ( x < 1940 && x > 1900) {
      if (y > 4000) {
        motorManager.Turn_Left();
      } else if (y < 100) {
        motorManager.Turn_Right();
      } else {
        motorManager.Stop();
      }
    }
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

  buttonManager.Update();
}
