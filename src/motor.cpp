#include <motor.h>


motor::motor(int relay1, int relay2, int speed){
    rl1 = relay1;
    rl2 = relay2;
    sp = speed;
}
void motor::setPower(bool dir, int power){
    digitalWrite(rl1, dir);
    digitalWrite(rl2, !dir);
    analogWrite(sp, power);
}
void motor::stop(){
    digitalWrite(sp, 0);
}
