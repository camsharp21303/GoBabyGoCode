#include "Printer.h"

Printer::Printer(HardwareSerial* hwSer, SoftwareSerial* swSer){
    _ser = hwSer;
    _hc = swSer;
}
void Printer::out(int m){
    _ser->println(m);
    _hc->println(m);
}
void Printer::out(String m){
    _ser->println(m);
    _hc->println(m);
}

void Printer::begin(int baud){
    _ser->begin(baud);
    _hc->begin(baud);
}