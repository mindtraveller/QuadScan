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
  begin
    while (i = sp.read_nonblock(1))
      print i
    end
  rescue Exception => e
    # puts ""
  end

  begin
    c = STDIN.read_nonblock(1)
    # STDIN.echo = false
    # STDIN.raw!

    # c = STDIN.getc.chr
    # c = STDIN.getch
    exit(0) if c == "0"

  rescue Errno::EAGAIN
    sleep(0.003)
    next
  ensure
    # STDIN.echo = true
    # STDIN.cooked!
  end

  case c
  when "w"
    sp.write "T"
    throttle += 1
  when "x"
    sp.write "t"
    throttle -= 1
  when "s"
    sp.write "s"
  when "a"
    sp.write "Y"
  when "d"
    sp.write "y"
  when "q"
    sp.write "R"
  when "e"
    sp.write "r"
  when "z"
    sp.write "P"
  when "c"
    sp.write "p"
  when "1"
    sp.write "T"
    sp.write "Y"
    sp.write "R"
    sp.write "P"
  when "2"
    sp.write "t"
    sp.write "y"
    sp.write "r"
    sp.write "p"
  end

  # puts "pitch: #{pitch} row: #{row} yaw #{yaw}"

  # sp.write c
  c = nil
end
 
sp.close
