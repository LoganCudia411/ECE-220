#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------


/*This program solves a given 9x9 sudoku board using a recursive algorithim. To start off, I created 3 functions that 
define whether a value (1-9) could be placed at a specifc cell (row,col). is_val_in_row, is_val_in_col, and is_val_in_3x3_zone
are all conditions we must check in order to actually place the value in a specific cell. This is all checked in the is_val_valid function that returns 1 if a value can 
be placed. The solve_sudoku calls all of these functions and uses a base case and a recursive case to solve a given sudoku board. 
The base case is that if we are able to go through every cell in the board and it has a correct value. If not, we keep the location of the empty cell stored then 
use that location in the recusive case. The recusive case checks what value (1-9) should be at that cell by calling is_val_valid.
We then call the function again to check the status of the board and repeat until solve_sudoku returns 1. */

// You are free to declare any private functions if needed.


// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  int j;
  assert(i>=0 && i<9);
  //go through every column index at inputted row to see if val appears there 
  for (j=0; j<9; j++){
    if(val == sudoku[i][j]){
      return 1; //return true 
    }
  }
  return 0; //return false 
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  int i; 
  assert(j>=0 && j<9);
  //go through every row index at inputted column to see if val exists in any cell
  for (i = 0; i<9; i++){  
    if(val == sudoku[i][j]){
      return 1; //return true 
    }
  }
  return 0; //return false 
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   int row, col; 
  assert(i>=0 && i<9);
  int x = i/3; // we need to put i and j into different variables in order to specify what 3x3 sub matrix we are looking at 
  int y = j/3;

  for(row = x*3; row<=x*3+2; row++){ //after we specify we multiply by 3 then stop after we offset by 2 from the original row/col
    for(col = y*3; col<=y*3+2; col++){
      if(sudoku[row][col]==val){
        return 1;
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  int row, col,grid;
   // moving returned values into corresponding variables
  row = is_val_in_row(val, i, sudoku);
  col = is_val_in_col(val, j, sudoku); 
  grid = is_val_in_3x3_zone(val, i, j, sudoku);
  assert(i>=0 && i<9 && j>=0 && j<9);
  //if any of these functions return 1, we are not able to put a value in the cell since it has already appeared in either
  // the row, column or 3x3 matrix
  if(row==1 || col==1 || grid==1){ 
    return 0; //cannot be filled
  }
  return 1; //can be filled
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  int  row, col,flag=0;
  //loop through every cell of the board to see if it has a value (1-9)
  for (row = 0; row<9; row++){
    for(col=0; col<9; col++){
      if(sudoku[row][col]==0){
        flag = 1; //if flag =1 then we found an unfilled cell at (row,col)
        break;
      }
    }
    if (flag == 1){ //breaking out of both loops
      break; 
    }
  }
  if(flag == 0){
    return 1; //if we go through the nested loop without breaking, the board is filled properly. 
  }

//col and row currently hold the position of an empty cell
int num;
for(num = 1; num<=9; num++){
  if(is_val_valid(num,row,col,sudoku)==1){  //if we are able to place either (1-9) at (row,col)
    sudoku[row][col]=num; //places value in cell
    if(solve_sudoku(sudoku)==1){ //recalls function to see if we have finished the board
      return 1; //if the recall returns 1 then we end the inital function call
    }

    sudoku[row][col]=0; //only occurs when the board cannot be solved, we leave the cell as unfilled
  }
}
  return 0; //only reached when board is unsolvable
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





