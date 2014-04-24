from Tkinter import *

top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
bord = [top,mid,btm]

def change_color(x, b=bord):
    r=x/3
    c=x%3
    if b[r][c] == 0:
        b[r][c]= 5
        bb[x].ss.configure(bg='red')
    else:
        bb[x].ss.configure(bg='blue')
        ### keep following the cycle of white-yellow-red...
        ######## maybe use pictures if colors aren't available



root = Tk()
root.title('Enter Cube State')

class Knop():
    """This is the docstring of the class"""

    def __init__(self, i, master=None):
        self.nummer = i
        self.row = i/3
        self.col = i%3
        self.text = StringVar()
        self.text.set("")
        def human_move():
            print 'knop nummer', self.nummer  ,'ingedrukt'
            change_color(self.nummer)
        self.ss = Button(root, textvariable=self.text , command=human_move, bg='yellow', width=10, height=5)
        self.ss.grid(row=self.row, column=self.col)

bb = range(9)
for i in range(9):
    bb[i]= Knop(i, master=root)

mainloop()
print 'Game over'