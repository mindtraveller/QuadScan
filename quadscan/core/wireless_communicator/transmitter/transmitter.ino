//#include <RF24.h>
//#include <nRF24L01.h>
//#include <RF24Network.h>

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//keep the same as for receiver
//packet size of the transfer operations
const uint8_t packetSize = sizeof(uint8_t) * 5;
//buffer for read write operations
uint8_t buffer[5];
//pipe address for the communication
const uint64_t pipe = 0xE8E8F0F0E1LL;
unsigned char messageType = 'T';
uint8_t channel = 90;

RF24 radio(9,10);
//RF24Network transmitter(radio);
//
//const uint16_t this_node = 1;
//const uint16_t other_node = 0;
//
void setup() {
//  Serial.begin(9600);
//  radio.begin();
//  radio.openWritingPipe(pipe); 
////  radio.setRetries(15, 15);
////  radio.setPALevel(RF24_PA_HIGH);
////  radio.setChannel(channel);
////  radio.setDataRate(RF24_1MBPS);
////  radio.setPayloadSize(packetSize);
////  transmitter.begin(90, this_node);
//  
//  //dummy values
//  buffer[0] = 77;
//  buffer[1] = 33;
//  buffer[2] = 44;
//  buffer[3] = 55;
//  buffer[4] = 66;
}
//
void loop() {
////  transmitter.update();
////  RF24NetworkHeader to_header(other_node);
////  transmitter.write(to_header, buffer, packetSize);
////  radio.openWritingPipe(pipe); 
//  if (radio.write(buffer, packetSize)) {
//    Serial.println("success");
//  } else {
//    Serial.println("fail");
//  }
//  delay(1000);
}

