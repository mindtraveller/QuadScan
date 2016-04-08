#include <RF24.h>
#include <RF24Network.h>

//keep the same as for receiver
//packet size of the transfer operations
const uint8_t packetSize = sizeof(uint8_t) * 5;
//buffer for read write operations
uint8_t buffer[packetSize];
//pipe address for the communication
//const uint64_t pipe = 0xF0F0F0F0AA;
unsigned char messageType = 77; //receives ACK

RF24 radio(9,10);
RF24Network transmitter(radio);
RF24NetworkHeader header;
RF24NetworkHeader to_header(00, messageType);

void setup() {
  Serial.begin(9600);
  transmitter.begin(00);

  //dummy values
  buffer[0] = 1;
  buffer[1] = 3;
  buffer[2] = 4;
  buffer[3] = 5;
  buffer[4] = 6;
}

void loop() {
  transmitter.write(to_header, buffer, 1);
  delay(100);
}
