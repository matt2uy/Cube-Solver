import serial
import time
ser = serial.Serial('/dev/ttyACM0', 9600)

# reset arduino
ser.setDTR(False) # Drop DTR
time.sleep(0.022) # similar to ide
ser.setDTR(True)  # Up the DTR back
 
value1 = 123;
value2 = 17;
# load up all the values into a byte array
# then send the full byte array out over serial
# NOTE: This only works for values from 0-255  
byte out[] = new byte[2]
out[0] = byte(value1)
out[1] = byte(value2)
port.write(out);
