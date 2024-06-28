import serial
import time

serialPort_tnt0 = serial.Serial(port = "/dev/tnt0", baudrate=115200,
                           bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
serialPort_tnt1 = serial.Serial(port = "/dev/tnt1", baudrate=115200,
                           bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

i: int = -1
while(1):
    time.sleep(0.1)
    i += 1
    str = f"hello there {i} \r\n"
    serialPort_tnt0.write(str.encode('UTF-8'))

    # # Wait until there is data waiting in the serial buffer
    # if(serialPort_tnt1.in_waiting > 0):
    #     # Read data out of the buffer until a carraige return / new line is found
    #     serialString = serialPort_tnt1.readline()
    #     # Print the contents of the serial data
    #     print(serialString.decode('Ascii'))
    #     # exit
    #     break
