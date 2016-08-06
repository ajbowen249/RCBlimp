//Wraps up prototcol difficulties involved
//with the raw wireless serial link.

#include "Arduino.h"

#ifndef Reciever_h
#define Reciever_h

class Reciever {
  public:
    Reciever(int packetSize, byte (*read)(), int (*available)(), void (*processPacket)(byte*));
    void Recieve();
  private:
    byte (*_read)();
    int (*_available)();
    void (*_processPacket)(byte*);
    int _packetSize;

    bool CheckSum(byte buffer[], byte sum);
};

#endif
