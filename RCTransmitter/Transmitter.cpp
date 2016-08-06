#include "Transmitter.h"
Transmitter::Transmitter(int packetSize, int diddleSize, void (*write)(byte*, int)) {
  _write = write;
  _packetSize = packetSize;
  _diddleSize = diddleSize;
}

void Transmitter::Transmit(byte buffer[]) {
  byte bufferWithDiddlerAndPreamble[_packetSize + 3 + _diddleSize];

  for(int i = 0; i < _diddleSize; i++) {
    bufferWithDiddlerAndPreamble[i] = C_LineDiddler;
  }

  bufferWithDiddlerAndPreamble[_diddleSize + 0] = 0x55;
  bufferWithDiddlerAndPreamble[_diddleSize + 1] = 0xAA;

  byte sum = 0;

  for(int i = 0; i < _packetSize; i++) {
    bufferWithDiddlerAndPreamble[i + _diddleSize + 3] = buffer[i];
    sum += buffer[i];
  }
    
  bufferWithDiddlerAndPreamble[_diddleSize + 2] = sum;

  _write(bufferWithDiddlerAndPreamble, _diddleSize + _packetSize + 3);
}