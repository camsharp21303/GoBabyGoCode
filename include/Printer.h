#ifndef PRINTER_H
#define PRINTER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Printer {
    private:
        HardwareSerial* _ser;
        SoftwareSerial* _hc;
    public:
        Printer(HardwareSerial* hwSer, SoftwareSerial* swSer);
        void begin(int baud=9600);
        void out(int m);
        void out(String m);
        void out (char m);
};

#endif