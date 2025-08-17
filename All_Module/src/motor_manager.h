#ifndef __MOTOR_MANAGER_H_
#define __MOTOR_MANAGER_H_

#include <Arduino.h>
#include <Wire.h>

#define FAULT_PIN    18
#define B1_PIN       23
#define B2_PIN       19

#define PWM_RES      8       // 8-bit (0-255)
#define PWM_CH_B1    0
#define PWM_CH_B2    1
#define PWM_FREQ     20000   // 20 kHz để động cơ êm hơn

class MotorManager {
    private:
        bool initialized = false;
    public:
        MotorManager();
        virtual ~MotorManager();

        bool Init();
        void Turn_Left(uint8_t speed = 255);
        void Turn_Right(uint8_t speed = 255);
        void Stop();
};
        
#endif  // __MOTOR_MANAGER_H_