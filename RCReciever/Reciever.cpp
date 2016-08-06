#include "Reciever.h"

Reciever::Reciever(int packetSize, byte (*read)(), int (*available)(), void (*processPacket)(byte*)){
    _packetSize = packetSize;
    _read = read;
    _available = available;
    _processPacket = processPacket;
}

void Reciever::Recieve() {
  if(_available()) {
    char inChar = _read();
    if(inChar != 0x55) return;

    while(!_available()) {}
    inChar = _read();
    if(inChar != 0xAA) return;
    
    while(!_available()) {}
    byte sum = _read();

    while(_available() < _packetSize){}

    byte rxBuffer[_packetSize];
    for(int i = 0; i < _packetSize; i++){
      rxBuffer[i] = _read();
    }

    if(CheckSum(rxBuffer, sum)){
      _processPacket(rxBuffer);
    }
  }
}

bool Reciever::CheckSum(byte buffer[], byte sum) {
  byte realSum = 0;

  for(int i = 0; i < _packetSize; i++) {
    realSum += buffer[i];
  }

  return realSum == sum;
}