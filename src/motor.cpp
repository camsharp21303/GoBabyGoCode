#include <Arduino.h>


class motor{
    private:
        int rl1;
        int rl2;
        int sp;
    public:
        motor(int relay1, int relay2, int speed){
            rl1 = relay1;
            rl2 = relay2;
            sp = speed;
        }
        void setPower(bool dir, int power){
            digitalWrite(rl1, dir);
            digitalWrite(rl2, !dir);
            analogWrite(sp, power);
        }
        void stop(){
            digitalWrite(sp, 0);
        }
};