#include <Arduino.h>
#include <SoftwareSerial.h>

class Printer {
    private:
        HardwareSerial* _ser;
        SoftwareSerial* _hc;
    public:
        Printer(HardwareSerial* hwSer, SoftwareSerial* swSer){
            _ser = hwSer;
            _hc = swSer;
        }
        void out(int m){
            _ser->println(m);
            _hc->println(m);
        }
        void out(String m){
            _ser->println(m);
            _hc->println(m);
        }
};