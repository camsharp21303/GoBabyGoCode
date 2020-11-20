#ifndef DATARELAY_H
#define DATARELAY_H

#include <Printer.h>
#include "motor.h"
#include "definitions.h"

class dataRelay{
    private:
        Printer* print;
        void blink();
        const int POWER_MULTIPLY = 1;
    public:
        motor m1 = motor(motor1Relay1, motor1Relay2, motor1Speed);
        motor m2 = motor(motor2Relay1, motor2Relay2, motor2Speed);
        bool debug = false;
        dataRelay(Printer* p);
        void formatData(int d);
};

#endif //DATARELAY_H