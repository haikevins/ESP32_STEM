#ifndef   __HCSR04_MANAGER_H__
#define   __HCSR04_MANAGER_H__

#include <Arduino.h>

#define TRIG_PIN 26
#define ECHO_PIN 27

class HCSR04Manager {
    private:
        unsigned long duration;
        float distance;
    public:
        HCSR04Manager();
        virtual ~HCSR04Manager();

        void Init();
        float Read_Distance();
};

#endif // __HCSR04_MANAGER_H__
