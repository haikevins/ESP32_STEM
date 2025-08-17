#include "motor_manager.h"

MotorManager::MotorManager() {
}

MotorManager::~MotorManager() {
}

bool MotorManager::Init() {
    pinMode(FAULT_PIN, INPUT_PULLUP);

    ledcSetup(PWM_CH_B1, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_CH_B2, PWM_FREQ, PWM_RES);

    ledcAttachPin(B1_PIN, PWM_CH_B1);
    ledcAttachPin(B2_PIN, PWM_CH_B2);

    if (digitalRead(FAULT_PIN) == LOW) {
        Serial.println("DRV8833 Error! Check the connection or motor.");
        ledcWrite(PWM_CH_B1, 0);
        ledcWrite(PWM_CH_B2, 0);
        delay(1000);
        initialized = false;
        return false;
    }

    initialized = true;
    return true;
}

void MotorManager::Turn_Left(uint8_t speed) {
    if (!initialized) return;
    speed = constrain(speed, 0, 255);
    ledcWrite(PWM_CH_B1, 0);
    ledcWrite(PWM_CH_B2, speed);
}

void MotorManager::Turn_Right(uint8_t speed) {
    if (!initialized) return;
    speed = constrain(speed, 0, 255);
    ledcWrite(PWM_CH_B1, speed);
    ledcWrite(PWM_CH_B2, 0);
}

void MotorManager::Stop() {
    if (!initialized) return;
    ledcWrite(PWM_CH_B1, 0);
    ledcWrite(PWM_CH_B2, 0);
}
