#include "motorControl.h"

motorControl::motorControl(motor* m1, motor* m2){
    _m1 = m1;
    _m2 = m2;
}
void motorControl::stop(){
    _m1->stop();
    _m2->stop();
}

void motorControl::moveMotors(Direction dir, int p){
    int powerHalf = p/2;
    switch (dir)
    {
    case FORWARD:
        _m1->setPower(false, powerHalf);
        _m2->setPower(false, powerHalf);
        break;
    case BACKWARD:
        _m1->setPower(true, powerHalf);
        _m2->setPower(true, powerHalf);
        break;
    case LEFT:
        _m1->setPower(false, powerHalf);
        _m2->setPower(true, powerHalf);
        break;
    case RIGHT:
        _m1->setPower(true, powerHalf);
        _m2->setPower(false, powerHalf);
        break;
    }
}