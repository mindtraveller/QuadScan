#include <RF24.h>
#include <nRF24L01.h>
#include <RF24Network.h>

//keep the same as for transmitter
//packet size of the transfer operations
const uint8_t packetSize = sizeof(uint8_t) * 5;
//buffer for read write operations
uint8_t buffer[5];
//pipe address for the communication
const uint64_t pipe = 0xE8E8F0F0E1LL;
unsigned char messageType = 'T';
uint8_t channel = 90;

RF24 radio(9,10);
RF24Network receiver(radio);

const uint16_t this_node = 0;
const uint16_t other_node = 1;

void setup() {
  Serial.begin(9600);
  radio.begin();
//  receiver.begin(90, this_node);
  radio.openReadingPipe(1, pipe);
//  radio.setPALevel(RF24_PA_HIGH);
//  radio.setChannel(channel);
//  radio.setDataRate(RF24_1MBPS);
//  radio.setPayloadSize(packetSize);
}

void loop() {
//  receiver.update();
//  while (receiver.available()) {
//    Serial.println("after available");
//    RF24NetworkHeader header;
//    receiver.read(header, buffer, packetSize);
//    Serial.print(buffer[0]);
//  }
  while(!radio.available());
  if (radio.available()) {
  radio.read(buffer, packetSize);
  Serial.print(buffer[0]);
  }
  delay(100);
}


