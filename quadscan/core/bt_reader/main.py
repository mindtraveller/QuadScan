import serial
import struct

packet_length = 7
serial_port = '/dev/cu.HC-05-DevB'
bt = serial.Serial(serial_port, 9600, timeout=3)

print("opened")

while(True):
    data = bt.read(packet_length)
    if len(data) == packet_length:
        print(struct.unpack("BBBBBBB", data))