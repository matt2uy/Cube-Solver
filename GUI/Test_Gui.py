from Tkinter import *

top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
bord = [top,mid,btm]

red_face = ['y', 'y', 'y',
            'y', 'y', 'y',
            'y', 'y', 'y']
counter = 0

def change_color(x, b=bord):
    # seems like x is the square number out of the 9 squares
    global counter
    r=x/3
    c=x%3
    if b[r][c] == 0:
        b[r][c]= 5
        bb[x].ss.configure(bg='white', activebackground='white')
        counter = 1
        print 'white'
        red_face[x] = 'w'

    elif counter == 0:
        bb[x].ss.configure(bg='white', activebackground='white')
        counter = 1
        print 'white'
        red_face[x] = 'w'

    elif counter == 1:
        bb[x].ss.configure(bg='blue', activebackground='blue')
        counter = 2
        print 'blue'
        red_face[x] = 'b'

        ### keep following the cycle of white-yellow-red...
    elif counter == 2:
        bb[x].ss.configure(bg='red', activebackground='red')
        counter = 3
        print 'red'
        red_face[x] = 'r'

    elif counter == 3:
        bb[x].ss.configure(bg='green', activebackground='green')
        counter = 4
        print 'green'
        red_face[x] = 'g'

    elif counter == 4:
        bb[x].ss.configure(bg='orange', activebackground='orange')
        counter = 5
        print 'orange'
        red_face[x] = 'o'

    elif counter == 5:
        bb[x].ss.configure(bg='yellow', activebackground='yellow')
        counter = 0
        print 'yellow'
        red_face[x] = 'y'



root = Tk()
root.title('Enter Cube State')

class Knop():
    """This is the docstring of the class"""

    def __init__(self, i, master=None):
        self.nummer = i
        self.row = i/3
        self.col = i%3
        def human_move():
            print 'knop nummer', self.nummer  ,'ingedrukt'
            change_color(self.nummer)
        self.ss = Button(root, repeatinterval=100, command=human_move, bg='yellow', activebackground='yellow', width=10, height=5)
        self.ss.grid(row=self.row, column=self.col)

bb = range(9)
for i in range(9):
    bb[i]= Knop(i, master=root)

mainloop()
print 'Cube State:'
print red_face[0], red_face[1], red_face[2]
print red_face[3], red_face[4], red_face[5]
print red_face[6], red_face[7], red_face[8]