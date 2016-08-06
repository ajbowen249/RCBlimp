#define BAUDRATE 9600
#define NULL_TX_INTERVAL 100000
#define PACKET_SIZE 3
#define DIDDLE_SIZE 10

#define THROTTLE_PIN 3
#define THROTTLE_MIN 180
#define THROTTLE_MAX 1000

#define IX_SetMotors 0x53

#include "Transmitter.h"
#include "TimerOne.h"

void Write(byte* buffer, int size);

Transmitter _transmitter(PACKET_SIZE, DIDDLE_SIZE, Write);

void setup() {
  Serial.begin(BAUDRATE);
}

void loop() {
  byte throttleBase = ThrottleBase();
  byte instructionBuffer[3] = {IX_SetMotors, throttleBase, throttleBase};

  _transmitter.Transmit(instructionBuffer);

  delay(100);
}

void Write(byte* buffer, int size) {
  Serial.write(buffer, size);
}

byte ThrottleBase(){
  int throttleInput = analogRead(THROTTLE_PIN);

  if(throttleInput < THROTTLE_MIN) return 0;
  else if(throttleInput > THROTTLE_MAX) return 127;
  else return (byte)(((double)((double)throttleInput - (double)THROTTLE_MIN)) / ((double)(THROTTLE_MAX) - (double)THROTTLE_MIN) * 127.0);
}