from Tkinter import *

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

def enter_yellow_face():
    top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
    bord = [top,mid,btm]

    yellow_face = ['y', 'y', 'y',
                'y', 'y', 'y',
                'y', 'y', 'y']
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
            counter[x] = 1
            print 'white'
            yellow_face[x] = 'w'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 1
            print 'white'
            yellow_face[x] = 'w'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 2
            print 'blue'
            yellow_face[x] = 'b'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 3
            print 'red'
            yellow_face[x] = 'r'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 4
            print 'green'
            yellow_face[x] = 'g'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 5
            print 'orange'
            yellow_face[x] = 'o'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 0
            print 'yellow'
            yellow_face[x] = 'y'

    root = Tk()
    root.title('Enter Yellow Face')

    class Knop():
        """This is the docstring of the class"""

        def __init__(self, i, master=None):
            self.nummer = i
            self.row = i/3
            self.col = i%3
            def human_move():
                print 'knop nummer', self.nummer  ,'ingedrukt'
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
            counter[x] = 1
            print 'blue'
            white_face[x] = 'b'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 1
            print 'red'
            white_face[x] = 'r'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 2
            print 'green'
            white_face[x] = 'g'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 3
            print 'orange'
            white_face[x] = 'o'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 4
            print 'yellow'
            white_face[x] = 'y'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 5
            print 'white'
            white_face[x] = 'w'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 0
            print 'blue'
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
                print 'knop nummer', self.nummer  ,'ingedrukt'
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
            print 'red'
            blue_face[x] = 'r'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 1
            print 'green'
            blue_face[x] = 'g'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 2
            print 'orange'
            blue_face[x] = 'o'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 3
            print 'yellow'
            blue_face[x] = 'y'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 4
            print 'white'
            blue_face[x] = 'w'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 5
            print 'blue'
            blue_face[x] = 'b'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 0
            print 'red'
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
                print 'knop nummer', self.nummer  ,'ingedrukt'
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
            counter[x] = 1
            print 'green'
            red_face[x] = 'g'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 1
            print 'orange'
            red_face[x] = 'o'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 2
            print 'yellow'
            red_face[x] = 'y'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 3
            print 'white'
            red_face[x] = 'w'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 4
            print 'blue'
            red_face[x] = 'b'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 5
            print 'red'
            red_face[x] = 'r'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 0
            print 'green'
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
                print 'knop nummer', self.nummer  ,'ingedrukt'
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
            counter[x] = 1
            print 'orange'
            green_face[x] = 'o'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 1
            print 'yellow'
            green_face[x] = 'y'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 2
            print 'white'
            green_face[x] = 'w'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 3
            print 'blue'
            green_face[x] = 'b'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 4
            print 'red'
            green_face[x] = 'r'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 5
            print 'green'
            green_face[x] = 'g'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 0
            print 'orange'
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
                print 'knop nummer', self.nummer  ,'ingedrukt'
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
            counter[x] = 1
            print 'yellow'
            orange_face[x] = 'y'

        elif counter[x] == 0:
            bb[x].ss.configure(bg='white', activebackground='white')
            counter[x] = 1
            print 'white'
            orange_face[x] = 'w'

        elif counter[x] == 1:
            bb[x].ss.configure(bg='blue', activebackground='blue')
            counter[x] = 2
            print 'blue'
            orange_face[x] = 'b'

            ### keep following the cycle of white-yellow-red...
        elif counter[x] == 2:
            bb[x].ss.configure(bg='red', activebackground='red')
            counter[x] = 3
            print 'red'
            orange_face[x] = 'r'

        elif counter[x] == 3:
            bb[x].ss.configure(bg='green', activebackground='green')
            counter[x] = 4
            print 'green'
            orange_face[x] = 'g'

        elif counter[x] == 4:
            bb[x].ss.configure(bg='orange', activebackground='orange')
            counter[x] = 5
            print 'orange'
            orange_face[x] = 'o'

        elif counter[x] == 5:
            bb[x].ss.configure(bg='yellow', activebackground='yellow')
            counter[x] = 0
            print 'yellow'
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
                print 'knop nummer', self.nummer  ,'ingedrukt'
                change_color(self.nummer)
            self.ss = Button(root, command=human_move, bg='orange', activebackground='orange', width=10, height=5)
            self.ss.grid(row=self.row, column=self.col) 
            
            next_face = Button(root, text="Done",  command=root.destroy)
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

enter_cube()
print_cube()