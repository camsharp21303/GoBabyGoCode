#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#include "motor.h"

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT};

class motorControl{
    private:
        motor* _m1;
        motor* _m2;
        int p;
    public:
        motorControl(motor* m1, motor* m2, int power=105);
        void stop();
        void moveMotors(Direction dir);      
};


#endif
