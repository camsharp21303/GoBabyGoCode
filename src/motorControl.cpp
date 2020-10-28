#include <motor.cpp>

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT};

class motorControl{
    private:
        motor* _m1;
        motor* _m2;
        int p;
    public:
        motorControl(motor* m1, motor* m2, int power=105){
            _m1 = m1;
            _m2 = m2;
            p=power;
        }
        void stop(){
            _m1->stop();
            _m2->stop();
        }

        void moveMotors(Direction dir){
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
        
};