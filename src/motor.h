#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

class motor{
    private:
        int rl1;
        int rl2;
        int sp;
    public:
        motor(int relay1, int relay2, int speed);
        void setPower(bool dir, int power);
        void stop();
};
#endif // MOTOR_H