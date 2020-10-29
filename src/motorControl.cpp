#include "motorControl.h"

motorControl::motorControl(motor* m1, motor* m2, int power=105){
    _m1 = m1;
    _m2 = m2;
    p=power;
}
void motorControl::stop(){
    _m1->stop();
    _m2->stop();
}

void motorControl::moveMotors(Direction dir){
    switch (dir)
    {
    case FORWARD:
        _m1->setPower(true, p);
        _m2->setPower(true, p);
        break;
    case BACKWARD:
        _m1->setPower(false, p);
        _m2->setPower(false, p);
        break;
    case LEFT:
        _m1->setPower(true, p);
        _m2->setPower(false, p);
        break;
    case RIGHT:
        _m1->setPower(false, p);
        _m2->setPower(true, p);
        break;
    }
}