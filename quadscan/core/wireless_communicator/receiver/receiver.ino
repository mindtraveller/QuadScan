#include <RF24.h>
#include <RF24Network.h>

//keep the same as for transmitter
//packet size of the transfer operations
const uint8_t packetSize = sizeof(uint8_t) * 5;
//buffer for read write operations
uint8_t buffer[packetSize];
//pipe address for the communication
//const uint64_t pipe = 0xF0F0F0F0AA1;
unsigned char messageType = 77; //receives ACK

RF24 radio(9,10);
RF24Network receiver(radio);
RF24NetworkHeader header;
RF24NetworkHeader to_header(01, messageType);

void setup() {
  Serial.begin(9600);
  receiver.begin(00);
//  radio.begin();
//  radio.openReadingPipe(1, pipe);
//  radio.startListening();
}

void loop() {
  if (receiver.available()) {
    receiver.read(header, buffer, 1);
    Serial.print(buffer[0]);
  }
//  delay(10);
}

