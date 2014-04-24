from Tkinter import *

top,mid,btm=[0,0,0],[0,0,0],[0,0,0]
bord = [top,mid,btm]

def test_endgame(b=bord):
    if win(player=15):
        print 'Congratulations !!!'
        print 'You Win!!!'
        quit()
    elif win():
        print 'You\'re not so smart. You Lost !'
        quit()

def hzet(x, b=bord):
    r=x/3
    c=x%3
    if b[r][c] == 0:
        b[r][c]= 5
        bb[x].text.set("X")
        bb[x].ss.configure(bg='red')
        test_endgame()
        czet()
    else:
        print 'Illegal move'

def cputmove(r,c):
    bord[r][c] = 7
    i = 3*r + c
    bb[i].text.set("O")
    bb[i].ss.configure(bg='blue')
    test_endgame()
        
def czet(): #check if the computer can make a move and make it
    cb = [bord[0][:],bord[1][:],bord[2][:]] #copy the board
    emptyplace, lose = 0 , 0 #no empty place found yet
    for r in range(3):
        for c in range(3): #c is the index of the column
            if bord[r][c] == 0:
                cb[r][c] = 7
                if win(b=cb): #computer wins
                    cputmove(r,c)
                    print 'computer is gonna win'
                    return 1
                else:
                    emptyplace, row, col =1, r, c #remember this empty place
                    cb[r][c] = 5
                    if win(player=15,b=cb): #human wins
                        lose , row1, col1 = 1, r, c #remember this
                        print 'you are not gonna win, remembered' , row, col
                    cb[r][c] = 0
    #no winning move is found
    if lose: # a losing place is found
        cputmove(row1,col1)
        return 1
    elif emptyplace: #put in the last seen empty place
        cputmove(row,col)
        return 1
    print 'No move possible' #no move possible, bord is full
    print 'Draw !'
    quit()
        
def win(player=21,b=bord): #default check if computer wins
    for r in range(3): #check the rows
        if b[r][0]+b[r][1]+b[r][2] == player:
            return 1
    for c in range(3): #c is the index of the column
        if b[0][c]+b[1][c]+b[2][c] == player:
            return 1
    if b[0][0]+b[1][1]+b[2][2] == player:
            return 1
    if b[0][2]+b[1][1]+b[2][0] == player:
            return 1
    return 0

root = Tk()
root.title('tictactoe GUI')

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
            hzet(self.nummer)
        self.ss = Button(root, textvariable=self.text , command=human_move, bg='yellow', width=10, height=5)
        self.ss.grid(row=self.row, column=self.col)

bb = range(9)
for i in range(9):
    bb[i]= Knop(i, master=root)

mainloop()
print 'Game over'