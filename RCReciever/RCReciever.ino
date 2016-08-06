//Wireless serial receiver relay.
//Recieves serial data via software
//serial, and retransmits over uart.

#include <SoftwareSerial.h>
#include "Reciever.h"
#define BAUDRATE 9600
#define PACKET_SIZE 3

#define LEFT_MOTOR_PIN 16
#define RIGHT_MOTOR_PIN 17

byte Read();
int Available();
void ProcessPacket(byte packet[]);

Reciever _reciever(PACKET_SIZE, Read, Available, ProcessPacket);

void setup() {
  Serial2.begin(BAUDRATE);
  
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
}

void loop() {
  _reciever.Recieve();
}

int Available(){
  return Serial2.available();
}

byte Read(){
  return Serial2.read();
}

void ProcessPacket(byte packet[]){
  switch(packet[0]){
    case 0x53:
        SetMotorSpeed(LEFT_MOTOR_PIN, packet[1]);
        SetMotorSpeed(RIGHT_MOTOR_PIN, packet[2]);
        break;
  }
}

void SetMotorSpeed(int motorPin, byte input){
  analogWrite(motorPin, input * 2);
}