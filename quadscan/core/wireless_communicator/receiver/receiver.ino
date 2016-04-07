#include <RF24.h>

//keep the same as for transmitter
//packet size of the transfer operations
const uint8_t packetSize = sizeof(uint8_t) * 5;
//buffer for read write operations
uint8_t buffer[packetSize];
//pipe address for the communication
const uint64_t pipe = 0xF0F0F0F0AA;

RF24 receiver(9,10);

void setup() {
  Serial.begin(9600);
  receiver.begin();
  receiver.openReadingPipe(1, pipe);
  receiver.startListening();
}

void loop() {
  if (receiver.available()) {
    receiver.read(buffer, packetSize);
    Serial.write(buffer, packetSize);
  }
  delay(10);
}

