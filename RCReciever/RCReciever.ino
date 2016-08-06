//Wireless serial receiver relay.
//Recieves serial data via software
//serial, and retransmits over uart.

#include <SoftwareSerial.h>
#define BAUDRATE 9600
#define PACKET_SIZE 3

byte rxBuffer[PACKET_SIZE];

void setup() {
  Serial.begin(BAUDRATE);
  while(!Serial){}
  
  Serial2.begin(BAUDRATE);
  
  Serial.println("Ready!");
}

void loop() {
  if(Serial2.available()) {
    char inChar = Serial2.read();
    if(inChar != 0x55) return;

    while(!Serial2.available()) {}
    inChar = Serial2.read();
    if(inChar != 0xAA) return;
    
    while(!Serial2.available()) {}
    byte sum = Serial2.read();

    while(Serial2.available() < PACKET_SIZE){}

    for(int i = 0; i < PACKET_SIZE; i++){
      rxBuffer[i] = Serial2.read();
    }

    if(CheckSum(rxBuffer, sum)){
      Serial.print("instruction code: ");
      Serial.print(rxBuffer[0]);
      Serial.print(" arg 1: ");
      Serial.print(rxBuffer[1]);
      Serial.print(" arg 2: ");
      Serial.println(rxBuffer[2]);
    }
  }
}

bool CheckSum(byte buffer[], byte sum) {
  byte realSum = 0;

  for(int i = 0; i < PACKET_SIZE; i++) {
    realSum += buffer[i];
  }

  return realSum == sum;
}