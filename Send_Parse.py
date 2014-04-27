"""
corresponds with receive_parse.cpp

Transfers the 6 cube face arrays 
from the computer  (here)
to their equivalent 
in the arduino


Run here: $ cd Dropbox/'Cube Solver'/Code/Serial_Comm/Bulk_Parse
		  $ python Serial_Parse.py
"""
from Tkinter import *
import serial
import time
ser = serial.Serial('/dev/ttyACM0', 9600)

# reset arduino
ser.setDTR(False) # Drop DTR
time.sleep(0.022) # similar to ide
ser.setDTR(True)  # Up the DTR back


yellow_face = ['y', 'y', 'y',
               'y', 'y', 'y',
               'y', 'y', 'y']

white_face = ['w', 'w', 'w',
              'w', 'w', 'w',
              'w', 'w', 'w']

blue_face = ['b', 'b', 'b',
             'b', 'b', 'b',
             'b', 'b', 'b']

red_face = ['r', 'r', 'r',
            'r', 'r', 'r',
            'r', 'r', 'r']

green_face = ['g', 'g', 'g',
              'g', 'g', 'g',
              'g', 'g', 'g']

orange_face = ['o', 'o', 'o',
               'o', 'o', 'o',
               'o', 'o', 'o']

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

############## Script start ###################


# do gui stuff


# make a function for this
print "sending cube string..."
'''raw_cube_string = generate_raw_cube()
send_raw_cube()	'''
while True:
	time.sleep(0.01)
	# show cube colours from arduino
	print ser.readline()