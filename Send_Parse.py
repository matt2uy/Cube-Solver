"""
corresponds with receive_parse.cpp

Transfers the 6 cube face arrays 
from the computer  (here)
to their equivalent 
in the arduino


Run here: $ cd Dropbox/'Cube Solver'/Code/Serial_Comm/Bulk_Parse
		  $ python Serial_Parse.py

while all_cubes assigned == False:
	arduino: ready
	computer: send
	arduino: recieve
"""

import serial
import time
ser = serial.Serial('/dev/ttyACM0', 9600)

# reset arduino
ser.setDTR(False) # Drop DTR
time.sleep(0.022) # similar to ide
ser.setDTR(True)  # Up the DTR back


yellow_face = ['y', 'y', 'y',
		 	   'd', 'y', 'y',
			   'g', 'y', 'y']

white_face = ['a', 'b', 'c',
		 	  'd', 'w', 'f',
			  'g', 'h', 'i']

blue_face = ['a', 'b', 'c',
		 	 'b', 'b', 'f',
			 'g', 'h', 'i']

red_face = ['a', 'r', 'c',
		 	'd', 'r', 'f',
			'g', 'h', 'i']

green_face = ['a', 'b', 'c',
		 	  'd', 'g', 'f',
			  'g', 'h', 'i']

orange_face = ['g', 'o', 'c',
		 	   'g', 'o', 'o',
			   'g', 'h', 'i']

raw_cube_string = ""

def generate_raw_cube():
	raw_cube_string = ""
	for color in yellow_face:
		raw_cube_string = raw_cube_string + color
		#catenate 'raw_cube_string' with yellow_face[0], [1], on and on.....

	for color in white_face:
		raw_cube_string = raw_cube_string + color
		#catenate 'raw_cube_string' with yellow_face[0], [1], on and on.....
	
	for color in red_face:
		raw_cube_string = raw_cube_string + color
		#catenate 'raw_cube_string' with yellow_face[0], [1], on and on.....
	
	for color in blue_face:
		raw_cube_string = raw_cube_string + color
		#catenate 'raw_cube_string' with yellow_face[0], [1], on and on.....

	for color in green_face:
		raw_cube_string = raw_cube_string + color
		#catenate 'raw_cube_string' with yellow_face[0], [1], on and on.....

	for color in orange_face:
		raw_cube_string = raw_cube_string + color
		#catenate 'raw_cube_string' with yellow_face[0], [1], on and on.....
	return raw_cube_string
# send all colors to arduino in one string
def send_raw_cube():
	ready_signal = ser.readline()	# original signal message

	# wait until arduino is ready
	ardu_ready = False	
		
	while ardu_ready == False:
		arduino_status = ser.readline()
		time.sleep(0.01)
		if arduino_status == ready_signal:	# if arduino is ready
			ardu_ready = True
			time.sleep(0.01)

	# send the raw_cube_string<
	ser.write(raw_cube_string)
	print "color sent: ", raw_cube_string

	time.sleep(0.01)

raw_cube_string = generate_raw_cube()
send_raw_cube()	
while True:
	time.sleep(0.01)
	# show cube colours from arduino
	print ser.readline()