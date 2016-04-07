#include <RF24.h>

//keep the same as for receiver
//packet size of the transfer operations
const uint8_t packetSize = sizeof(uint8_t) * 5;
//buffer for read write operations
uint8_t buffer[packetSize];
//pipe address for the communication
const uint64_t pipe = 0xF0F0F0F0AA;

RF24 transmitter(9,10);

void setup() {
  transmitter.begin();
  transmitter.openWritingPipe(pipe);

  //dummy values
  buffer[0] = 1;
  buffer[1] = 3;
  buffer[2] = 4;
  buffer[3] = 5;
  buffer[4] = 6;
}

void loop() {
  transmitter.write(buffer, packetSize);
  delay(1000);
}
