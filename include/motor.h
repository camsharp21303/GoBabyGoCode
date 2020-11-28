#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

class motor{
    private:
        int rl1;
        int rl2;
        int sp;
        int TRIM;
    public:
        motor(int relay1, int relay2, int speed);
        void setPower(bool dir, int power);
        void setTRIM(int t);
        void stop();
};
#endif // MOTOR_H