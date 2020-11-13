#include "dataRelay.h"

void dataRelay::blink(){
    for(int i = 0; i < 3; i++){
        digitalWrite(debugLED, LOW);
        delay(50);
        digitalWrite(debugLED, HIGH);
        delay(500);
    }
}

dataRelay::dataRelay(Printer* p){
    print = p;
}
void dataRelay::formatData(int d){
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
            print->out("Debugging is off\n");
        }
        else{
            debug  = true;
            blink();
            print->out("Debugging is on\n");
        }
        break;
    default:
        if(debug){
            print->out(d+"\n");
        }
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