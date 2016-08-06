#define BAUDRATE 9600
#define NULL_TX_INTERVAL 100000
#define PACKET_SIZE 7
#define DIDDLE_SIZE 10

#include "Transmitter.h"
#include "TimerOne.h"

void Write(byte* buffer, int size);

Transmitter _transmitter(PACKET_SIZE, DIDDLE_SIZE, Write);

void setup() {
  Serial.begin(BAUDRATE);  
}

void loop() {
  byte buffer[] = {'h', 'e', 'l', 'l', 'o', '\n', '\r'};
  _transmitter.Transmit(buffer);
  delay(100);

  byte buffer2[] = {'w', 'o', 'r', 'l', 'd', '\n', '\r'};
  _transmitter.Transmit(buffer2);
  delay(100);
}

void Write(byte* buffer, int size) {
  Serial.write(buffer, size);
}
