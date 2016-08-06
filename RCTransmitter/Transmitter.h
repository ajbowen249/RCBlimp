//Wraps up prototcol difficulties involved
//with the raw wireless serial link.

#include "Arduino.h"
#include "SoftwareSerial.h"

#ifndef Transmitter_h
#define Transmitter_h

class Transmitter {
  public:
    Transmitter(int packetSize, int diddleSize, void (*write)(byte*, int));
    void Transmit(byte buffer[]);
  private:
    void (*_write)(byte*, int);
    int _packetSize;
    int _diddleSize;
    byte C_LineDiddler = (byte)0x00;
};

#endif
