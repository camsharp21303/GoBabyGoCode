#include <motorControl.cpp>
#include <Printer.cpp>

#define motor1Relay1 8
#define motor1Relay2 9
#define motor1Speed 3

#define motor2Relay1 11
#define motor2Relay2 12
#define motor2Speed 10

#define debugLED 13

class dataRelay{
    
    private:
        Printer* print;
        void blink(){
            for(int i = 0; i < 3; i++){
                digitalWrite(debugLED, LOW);
                delay(50);
                digitalWrite(debugLED, HIGH);
                delay(500);
        }
}
    public:
        motor m1 = motor(motor1Relay1, motor1Relay2, motor1Speed);
        motor m2 = motor(motor2Relay1, motor2Relay2, motor2Speed);
        bool debug = false;
        dataRelay(Printer* p){
            print = p;
        }
        void formatData(int d){
            switch (d)
            {
            case 0:
                m1.stop();
                break;
            case 1:
                m2.stop();
                break;
            case 3:
                if(debug){
                    debug = false;
                    blink();
                    print->out("Debugging is off");
                }
                else{
                    debug  = true;
                    blink();
                    print->out("Debugging is on");
                }
                break;
            default:
                if(d >= 11 && d <= 71){
                    m1.setPower(true, (d-10)*4);
                }
                else if(d >= 72 && d <= 132){
                    m1.setPower(false, (d-71)*4);
                }
                else if(d >= 133 && d <= 193){
                    m2.setPower(true, (d-132)*4);
                }
                else if(d >= 194 && d <= 254){
                    m2.setPower(false, (d-193)*4);
                }
                break;
            }
        }
};