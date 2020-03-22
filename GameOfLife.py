
# coding: utf-8

import numpy as np
import time
import matplotlib
from matplotlib import pyplot as plt
from matplotlib import colors
matplotlib.use('Qt4Agg') 
#  Game of Life implementation

def init_board(size, p):
    # Init size+2xsize+2 board with probability p of cell being alive
    game_board=np.zeros([size+2,size+2])
    for i in range(1,size+1):
        for k in range (1,size+1):
            if np.random.random([1])>p:
                game_board[i,k]=1
    return game_board

def get_mask(board,size):
    masked_board=np.zeros([size+2,size+2])
    counter=0
    for i in range(1,size+1):
            for j in range(1,size+1):
                #start counting
                for l in [-1,0,1]:
                    for k in [-1,0,1]:
                        if l==k and k==0:
                            continue
                        if board[i+l,j+k]==1:
                            counter+=1
                masked_board[i,j]=counter
                counter=0
    return masked_board          

def update_state(board, mask,size):
    for i in range(1,size+1):
        for j in range (1,size+1):
            if board[i,j]==1:
                if (mask[i,j]==1 or mask[i,j]==2):
                    # KEEP ALIVE IF 1 OR 2
                    continue
                    # KILL IF >2 or <1
                else:
                    board[i,j]=0
            elif mask[i,j]>2 and board[i,j]==0:
                    # RESURRECT IF 3 OR MORE NB
                board[i,j]=1
    return board

def plot(board,size):
    cmap = colors.ListedColormap(['Black','White'])
    plt.pcolor(board[1:size+1,1:size+1],cmap=cmap)
    # plt.draw()

def main():
    size=30
    p=0.9
    board2=init_board(size,p)
    while (1):
        t = time.time()
        mask=get_mask(board2,size)
        board2=update_state(board2,mask,size)
        plot(board2,size)
        plt.pause(0.001)
        print(time.time()-t)
        plt.clf()
    # plt.show()

plt.rcParams['figure.figsize'] = [15, 8]

main()

