"""
corresponds with receive_parse.cpp

Transfers the 6 cube face arrays 
from the computer  (here)
to their equivalent 
in the arduino


Run here: $ cd Dropbox/'Cube Solver'/Project
		  $ python Send_Cube_State.py
"""
from Tkinter import *
import serial
import time
#ser = serial.Serial('/dev/ttyACM0', 9600)
ser = serial.Serial('/dev/ttyACM7', 9600) 

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

def reset_arduino():
    ser.setDTR(False) # Drop DTR
    time.sleep(0.022) # similar to ide
    ser.setDTR(True)  # Up the DTR back


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

###### Gui functions ########
def enter_yellow_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]
    counter = [0, 0, 0,
               0, 0, 0,
               0, 0, 0]

    def change_color(x, b=bord):
        # seems like x is the square number out of the 9 squares
        #global counter
        r=x/3
        c=x%3
        if b[r][c] == 0:
            b[r][c]= 5
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 0
            yellow_face[x] = 'w'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 1
            yellow_face[x] = 'b'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 2
            yellow_face[x] = 'r'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 3
            yellow_face[x] = 'g'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 4
            yellow_face[x] = 'o'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 5
            yellow_face[x] = 'y'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 0
            yellow_face[x] = 'w'

    root = Tk()
    root.title('Enter Yellow Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='yellow', activebackground='yellow', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Next Face",  command=root.destroy)
            next_face.grid(row=4, column=1)  

    bb = range(9)
    for i in range(9):
        bb[i]= Knop(i, master=root)

    mainloop()

def enter_white_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]
    counter = [0, 0, 0,
               0, 0, 0,
               0, 0, 0]

    def change_color(x, b=bord):
        # seems like x is the square number out of the 9 squares
        r=x/3
        c=x%3
        if b[r][c] == 0:
            b[r][c]= 5
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 0
            white_face[x] = 'b'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 1
            white_face[x] = 'r'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 2
            white_face[x] = 'g'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 3
            white_face[x] = 'o'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 4
            white_face[x] = 'y'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 5
            white_face[x] = 'w'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 0
            white_face[x] = 'b'

    root = Tk()
    root.title('Enter White Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='white', activebackground='white', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Next Face",  command=root.destroy)
            next_face.grid(row=4, column=1)

    bb = range(9)
    for i in range(9):
        bb[i]= Knop(i, master=root)

    mainloop()

def enter_blue_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]

    counter = [0, 0, 0,
               0, 0, 0,
               0, 0, 0]

    def change_color(x, b=bord):
        # seems like x is the square number out of the 9 squares
        r=x/3
        c=x%3
        if b[r][c] == 0:
            b[r][c]= 5
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 0
            blue_face[x] = 'r'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 1
            blue_face[x] = 'g'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 2
            blue_face[x] = 'o'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 3
            blue_face[x] = 'y'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 4
            blue_face[x] = 'w'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 5
            blue_face[x] = 'b'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 0
            blue_face[x] = 'r'

    root = Tk()
    root.title('Enter Blue Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='blue', activebackground='blue', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Next Face",  command=root.destroy)
            next_face.grid(row=4, column=1) 

    bb = range(9)
    for i in range(9):
        bb[i]= Knop(i, master=root)

    mainloop()

def enter_red_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]

    counter = [0, 0, 0,
               0, 0, 0,
               0, 0, 0]

    def change_color(x, b=bord):
        # seems like x is the square number out of the 9 squares
        r=x/3
        c=x%3
        if b[r][c] == 0:
            b[r][c]= 5
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 0
            red_face[x] = 'g'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 1
            red_face[x] = 'o'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 2
            red_face[x] = 'y'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 3
            red_face[x] = 'w'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 4
            red_face[x] = 'b'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 5
            red_face[x] = 'r'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 0
            red_face[x] = 'g'

    root = Tk()
    root.title('Enter Red Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='red', activebackground='red', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Next Face",  command=root.destroy)
            next_face.grid(row=4, column=1) 

    bb = range(9)
    for i in range(9):
        bb[i]= Knop(i, master=root)

    mainloop()

def enter_green_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]

    counter = [0, 0, 0,
               0, 0, 0,
               0, 0, 0]

    def change_color(x, b=bord):
        # seems like x is the square number out of the 9 squares
        r=x/3
        c=x%3
        if b[r][c] == 0:
            b[r][c]= 5
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 0
            green_face[x] = 'o'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 1
            green_face[x] = 'y'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 2
            green_face[x] = 'w'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 3
            green_face[x] = 'b'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 4
            green_face[x] = 'r'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 5
            green_face[x] = 'g'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 0
            green_face[x] = 'o'

    root = Tk()
    root.title('Enter Green Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='green', activebackground='green', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Next Face",  command=root.destroy)
            next_face.grid(row=4, column=1)

    bb = range(9)
    for i in range(9):
        bb[i]= Knop(i, master=root)

    mainloop()

def enter_orange_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]

    counter = [0, 0, 0,
               0, 0, 0,
               0, 0, 0]

    def change_color(x, b=bord):
        # seems like x is the square number out of the 9 squares
        r=x/3
        c=x%3
        if b[r][c] == 0:
            b[r][c]= 5
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 0
            orange_face[x] = 'y'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 1
            orange_face[x] = 'w'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 2
            orange_face[x] = 'b'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 3
            orange_face[x] = 'r'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 4
            orange_face[x] = 'g'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 5
            orange_face[x] = 'o'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 0
            orange_face[x] = 'y'

    root = Tk()
    root.title('Enter Orange Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='orange', activebackground='orange', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Send Cube!",  command=root.destroy)
            next_face.grid(row=4, column=1) 

    bb = range(9)
    for i in range(9):
        bb[i]= Knop(i, master=root)

    mainloop()

def print_face(current_face):
    print current_face[0], current_face[1], current_face[2]
    print current_face[3], current_face[4], current_face[5]
    print current_face[6], current_face[7], current_face[8]
def print_cube():
    print "Yellow Face: "
    print_face(yellow_face)

    print "White Face: "
    print_face(white_face)

    print "Blue Face: "
    print_face(blue_face)

    print "Red Face: "
    print_face(red_face)

    print "Green Face: "
    print_face(green_face)

    print "Orange Face: "
    print_face(orange_face)

def enter_cube():
    enter_yellow_face()
    enter_white_face()
    enter_blue_face()
    enter_red_face()
    enter_green_face()
    enter_orange_face()

############## Script start ###################


# do gui stuff

enter_cube()
print_cube()

###### put in function send_cube_state(): #########

reset_arduino() # get arduino ready
# wait until arduino sends out request for the cube string
while ser.readline() == "":
    #nothing
    print "Waiting for Arduino..."

# send cube string
print "sending cube string..."
raw_cube_string = generate_raw_cube()
send_raw_cube()
while True:
    time.sleep(0.01)
    # show cube colours from arduino
    print ser.readline()

