/*

 * countLiveNeighbor

 * Inputs:

 * board: 1-D array of the current game board. 1 represents a live cell.

 * 0 represents a dead cell

 * boardRowSize: the number of rows on the game board.

 * boardColSize: the number of cols on the game board.

 * row: the row of the cell that needs to count alive neighbors.

 * col: the col of the cell that needs to count alive neighbors.

 * Output:

 * return the number of alive neighbors. There are at most eight neighbors.

 * Pay attention for the edge and corner cells, they have less neighbors.

 * 

 */

//partners: cudia2

/*In this program, we need to write three functions: countLiveNeighbor, updateBoard, and aliveStable. For countLiveNeighbor, we need to count the

number of live neighbors at a given cell. In order to do this, we need to create a nested forloop for rows ranging from [row-1,row+1] and columns

ranging from [column-1,column+1]. After this, we write condition statements to make sure that neither the rows or the columns are outside of

the total rowsize or columnsize. After all conditions are met, we check to see if the value at the spot we looped at is 1. IF this is found, we incriment

the counter. The return value of this function is the amount of live neighbors. For the updateBoard game, we needed to iterate through the gameboard

and check the count of live neighbors at a particular position. Firstly, we made a nested forloop to iterate through the whole 1d array. After looping

to a value, we call the countLiveNeighbor function and get a count for live neighbors. Once we copy the current value of the target cell and

check the count of live neighbors, we set conditions to check the count and value and determine if we should change the value. After iterating through

the whole loop and updating values if nesecary, we copy these values into the real board. Lastly the final function we need to finish is aliveStable

function. For this function, we need to check whether the current game board is going to change or not. I first created a temp array to copy the current 

board into. Afterwards, I called the updateBoard function to make nesecary changes to the board. After calling this function, I looped through

the temporary array and the new updated board to check if there were any changes. If there were changes, return 0, if not, return 1 and exit.*/



int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

    int currRow, currCol, num_live=0;

    for(currRow=row-1; currRow<=row+1; currRow++){//first loop starts with row above target row

        if(currRow >= boardRowSize  || currRow<0){//if there is no row above the target, skip to row below target

        continue;

        }

        for(currCol=col-1; currCol<=col+1; currCol++){//inner loop for the columns 

            if(currCol>=boardColSize  || currCol < 0){//if column is out of range, go to next iteration

                continue;

            }else if(currRow == row && currCol == col){//if we are in the target cell, move to next cell

                continue;



            } else if(board[currRow * boardColSize + currCol] == 1){//if the cell at this position equals 1, increment counter

                num_live+=1;

            }

        }

    }

    return num_live;

}













/*

 * Update the game board to the next step.

 * Input: 

 * board: 1-D array of the current game board. 1 represents a live cell.

 * 0 represents a dead cell

 * boardRowSize: the number of rows on the game board.

 * boardColSize: the number of cols on the game board.

 * Output: board is updated with new values for next step.

 */

 

    static int size;

   

void updateBoard(int* board, int boardRowSize, int boardColSize) {

    size=boardRowSize*boardColSize;//get total size of 1d array using 2d array height and width

    int boardcpy[size]; //create a copy matrix to put changes into

    int i, j, count=0, value;

    for(i=0; i<boardRowSize; i++){//outer loop for rows

        for(j=0; j<boardColSize; j++){//outer loop for columns

            boardcpy[i*boardColSize+j]=board[i*boardColSize+j];//make copy of valyes

            count=countLiveNeighbor(board, boardRowSize, boardColSize, i, j);//count number of live neighbors

            value=board[i*boardColSize+j];//put current value of target cell into holder

            if(value==1){

                if(count==2||count==3){//alive cell stays alive

                    continue;



                }else if(count>3){//alive cell dies by overpopulation

                    boardcpy[i*boardColSize+j]=0; //current entry doesnt have enough live neighbors (2-3), therefore dies. 

                    continue;

                }else{//alive cell dies by underpopulation

                    boardcpy[i*boardColSize+j]=0; //current entry doesnt have enough live neighbors (2-3), therefore dies. 

                    continue;

                    }

            }     

            if(value==0){

                if(count==3){

                boardcpy[i*boardColSize+j]=1;//change current entry

                }

            }

        

    }

    

}

//copy loop to put values of boardcpy into board

 for(i=0; i<boardRowSize; i++){

        for(j=0; j<boardColSize; j++){

            board[i*boardColSize+j]=boardcpy[i*boardColSize+j];

            }

     }

}



/*

 * aliveStable

 * Checks if the alive cells stay the same for next step

 * board: 1-D array of the current game board. 1 represents a live cell.

 * 0 represents a dead cell

 * boardRowSize: the number of rows on the game board.

 * boardColSize: the number of cols on the game board.

 * Output: return 1 if the alive cells for next step is exactly the same with 

 * current step or there is no alive cells at all.

 * return 0 if the alive cells change for the next step.

 */ 

int aliveStable(int* board, int boardRowSize, int boardColSize){

    int i;

    int board2[size];//create board copy

     for(i=0; i<size; i++){

            board2[i]=*(board+i); //increment pointer to next entry then dereference, copy current board into board2

        }

     

    updateBoard(board2, boardRowSize, boardColSize);// update board to board2

//create a loop to check each value 

    for(i=0; i<size; i++){

        if(*(board+i)!=board2[i]){//if updated board doesnt equal original board, then return 0

            return 0;

        }

    }

    return 1;

}