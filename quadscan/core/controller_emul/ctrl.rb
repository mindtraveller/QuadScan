require 'io/console'
require "serialport"

#params for serial port
# port_str = "/dev/ttyUSB1"
# port_str = "/dev/ttyACM0"
port_str = "/dev/#{ARGV[1]}"

baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

MIN = 0

throttle = pitch = row = yaw = MIN
 
sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
 
while true do
  puts sp.gets.chomp

  begin
    # c = STDIN.read_nonblock(1)
    STDIN.echo = false
    STDIN.raw!

    c = STDIN.getc.chr
  rescue Errno::EAGAIN
    next
  ensure
    STDIN.echo = true
    STDIN.cooked!
  end

  case c
  when "w"
    sp.write "T\n"
    throttle += 1
  when "s"
    sp.write "t\n"
    throttle -= 1
  end

  # puts "pitch: #{pitch} row: #{row} yaw #{yaw}"

  # sp.write c
  c = nil
end
 
sp.close
