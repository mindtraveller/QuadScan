require 'io/console'
require "serialport"

#params for serial port
# port_str = "/dev/ttyUSB1"
# port_str = "/dev/ttyACM0"
port_str = "/dev/#{ARGV[0]}"

baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

MIN = 0
throttle = pitch = row = yaw = MIN
 
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
  when "x"
    sp.write "t\n"
    throttle -= 1
  when "s"
    sp.write "s\n"
  when "a"
    sp.write "Y\n"
  when "d"
    sp.write "y\n"
  when "q"
    sp.write "R\n"
  when "e"
    sp.write "r\n"
  when "z"
    sp.write "R\n"
  when "c"
    sp.write "r\n"
  end

  # puts "pitch: #{pitch} row: #{row} yaw #{yaw}"

  # sp.write c
  c = nil
end
 
sp.close
