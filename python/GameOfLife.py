
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


def init_board_with_given_states(size):
    game_board=np.zeros([size+2,size+2])
    
    # Still life 1:
    
    game_board[3,3]=1
    game_board[3,4]=1
    game_board[4,3]=1
    game_board[4,4]=1

    # # Still life 2:
    
    game_board[8,8]=1
    game_board[8,9]=1
    game_board[9,8]=1
    game_board[9,10]=1
    game_board[10,9]=1


    # # Still life 3: Boat
    
    game_board[12,12]=1
    game_board[13,11]=1
    game_board[13,13]=1
    game_board[14,12]=1

    #  Oscillators 1
    
    game_board[17,17]=1
    game_board[17,18]=1
    game_board[17,19]=1
    
    
    # Oscillators 2:
    
    game_board[8,16]=1
    game_board[8,17]=1
    game_board[9,16]=1
    game_board[9,17]=1

    game_board[10,18]=1
    game_board[10,19]=1
    game_board[11,18]=1
    game_board[11,19]=1
    
    #Glider
     
    game_board[18,3]=1
    game_board[17,3]=1
    game_board[16,3]=1
    game_board[16,2]=1
    game_board[17,1]=1

    

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
            
            # Handles live cells
            if board[i,j]==1:
                

                if (mask[i,j]==2 or mask[i,j]==3):
                # Keep alive if 2 or 3 neighbours
                    continue
                    # KILL IF >2 or <1
                else:
                    board[i,j]=0

            # Handles dead cells 
            elif mask[i,j]==3:
                board[i,j]=1
                
    return board

def plot(board,size):
    
    cmap = colors.ListedColormap(['Black','White'])
    plt.pcolor(board[1:size+1,1:size+1],cmap=cmap)


def main():
    
    size=30
    
    # p=0.9
    # board2=init_board(size,p)
    
    board2=init_board_with_given_states(size)
    # input()
    while (1):
        
        # time.sleep(1)
        t = time.time()
        
        mask=get_mask(board2,size)
        
        board2=update_state(board2,mask,size)


        plot(board2,size)
        plt.pause(0.001)
        print(time.time()-t)
        plt.clf()

        




# Config for matplotlib
plt.rcParams['figure.figsize'] = [15, 8]

# Main program
# if __name__=="__main__":
main()

