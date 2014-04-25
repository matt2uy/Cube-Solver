from Tkinter import *

top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
bord = [top,mid,btm]

counter = 0

def change_color(x, b=bord):
    global counter
    r=x/3
    c=x%3
    if b[r][c] == 0:
        b[r][c]= 5
        bb[x].ss.configure(bg='white')
        counter = 1

    elif counter == 0:
        bb[x].ss.configure(bg='white')
        counter = 1

    elif counter == 1:
        bb[x].ss.configure(bg='blue')
        counter = 2

        ### keep following the cycle of white-yellow-red...
    elif counter == 2:
        bb[x].ss.configure(bg='red')
        counter = 3

    elif counter == 3:
        bb[x].ss.configure(bg='green')
        counter = 4

    elif counter == 4:
        bb[x].ss.configure(bg='orange')
        counter = 5

    elif counter == 5:
        bb[x].ss.configure(bg='yellow')
        counter = 0



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
        self.ss = Button(root, command=human_move, bg='yellow', width=10, height=5)
        self.ss.grid(row=self.row, column=self.col)

bb = range(9)
for i in range(9):
    bb[i]= Knop(i, master=root)

mainloop()
print 'Game over'