"""
Transfers the 6 cube face arrays 
from the computer  (here)
to their equivalent 
in the arduino


Run here: $ cd Dropbox/'Cube Solver'/Code/Serial_Comm/Serial
		  $ python Send_Serial.py

while all_cubes assigned == False:
	arduino: ready
	computer: send
	arduino: recieve
"""

import serial
import time
ser = serial.Serial('/dev/ttyACM4', 9600)

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

orange_face = ['a', 'b', 'c',
		 	   'a', 'o', 'f',
			   'g', 'h', 'i']



num_of_cubes = len(yellow_face)


# send all colors to arduino for one face
def send_face(face):
	
	print "Face: ", face[4]
	ready_signal = ser.readline()	# original signal message

	for cube_num in range(num_of_cubes):
		
		# wait until arduino is ready
		ardu_ready = False	
		
		while ardu_ready == False:
			arduino_status = ser.readline()
			time.sleep(0.01)
			if arduino_status == ready_signal:	# if arduino is ready
				ardu_ready = True
				time.sleep(0.01)

		# send the color
		ser.write(face[cube_num])
		print "color sent: ", face[cube_num]
		time.sleep(0.01)

		"""# wait until arduino confirms
		ardu_received == False
		received_signal = ser.readline()

		while ardu_received == False:
			arduino_status = ser.readline()
			time.sleep(0.01)
			if arduino_status == received_signal:	# if arduino is ready
				ardu_ready = True
				time.sleep(0.01)"""



def send_whole_cube():
	send_face(yellow_face)
	send_face(white_face)
	send_face(blue_face)
	send_face(red_face)
	send_face(green_face)
	send_face(orange_face)

send_whole_cube()	

while True:
	print ser.readline()