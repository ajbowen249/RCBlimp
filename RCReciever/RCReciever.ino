//Wireless serial receiver relay.
//Recieves serial data via software
//serial, and retransmits over uart.

#include <SoftwareSerial.h>
#include "Reciever.h"
#define BAUDRATE 9600
#define PACKET_SIZE 3

byte Read();
int Available();
void ProcessPacket(byte packet[]);

Reciever _reciever(PACKET_SIZE, Read, Available, ProcessPacket);

void setup() {
  Serial.begin(BAUDRATE);
  while(!Serial){}
  
  Serial2.begin(BAUDRATE);
  
  Serial.println("Ready!");
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
  Serial.print("instruction code: ");
  Serial.print(packet[0]);
  Serial.print(" arg 1: ");
  Serial.print(packet[1]);
  Serial.print(" arg 2: ");
  Serial.println(packet[2]);
}