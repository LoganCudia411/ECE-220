#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* This program uses file I/O and dynamic memory allocation to get input from a text file and transfer specific data into a struct data type. 
We can then utilize this struct to hold many elements of a maze such the dimensions, end cell, start cell, and total cells. We use a depth first search 
(DPS) algorithim to to solve the maze. 

First we open the input file and extract the dimensions, allocate memory for that, then store that in our struct. We do this as well for our row pointer which points to each row of the array and 
for each individual cell which would be of type char. The destroyMaze function frees all memory afiliated with our struct. PrintMaze prints our maze using a nested for loop. Lastly, the solveMazeDFS uses recursion 
with back tracking to evaluate each cell to its immediate left, up, right, and down (in that order). It makes sure to move only when it is valid, if the next cell wasnt a wall char, start char, or an already visited cell. If 
we reach a dead end, we back track and mark our previous position as visited. 
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */

maze_t * createMaze(char * fileName)
{
    //declaring a pointer of that will point to the input file
    FILE *file; 
    file = fopen(fileName, "r");

    //allocating memory for actual maze
    maze_t * maze = malloc(sizeof(maze_t));

    //getting dimensions from file 
    int f_w, f_h; 
    fscanf(file, "%d %d", &f_w, &f_h);
    maze->width = f_h; 
    maze->height = f_w; 

    //allocating memory for the ROW POINTER of type char each row of the array
    maze->cells = (char**)malloc(sizeof(char*)*maze->height);

    int i,j;
    char cell, newline;
    //allocate memory for the actual row of the array all of which are type char
    for(i = 0; i<maze->height; i++){
       maze->cells[i] = (char*)malloc( sizeof(char)*(maze->width));
    }
    fscanf(file,"%c",&newline);// to get rid of the '\n' after the row where the dimensions are given
    //traversing the entire maze in the to transfer it to our struct
    for(i=0; i<f_h; i++){
        for(j=0; j<f_w; j++){
            fscanf(file, "%c", &cell);//scan each cell
            // need to get the newline char out of cycle so store it in a useless vairable
             maze->cells[i][j] = cell; //this line gives each cell the specific character
            if(cell=='S'){//if the character we scan is 'S'
                maze->startColumn = j;
                maze->startRow = i; 
            }
            if(cell== 'E'){ //if the character we scan is 'E'
                maze->endRow = i; 
                maze->endColumn = j; 
            }
        }
        //a new line will be at the end of every row
        fscanf(file, "%c", &newline);
        }
        fclose(file); //close the file 
    return maze; //returning pointer
    }
    


/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i; 
    for(i=0; i<maze->height; i++){
        free(maze->cells[i]); //if we free by height then width will get freed as well
    }
    //free up rest of struct
    free(maze->cells);
    free(maze);
    }

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    //printing maze using nested for loop
   int i, j; 
   for (i=0; i<maze->height; i++){
    for(j=0; j<maze->width; j++){
        printf("%c", maze->cells[i][j]);
    }
    printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
     //checking if within bounds
    if(col< 0|| row<0 || row>=maze->height || col >= maze->width){
        return 0;
    }
    if(maze->cells[row][col]== 'E'){ //base case if we have reached the end cell
        return 1;
        }
    //checking if it is not empty while also not being our starting point
    if(maze->cells[row][col]!=' ' && maze->cells[row][col]!='S'){
        return 0;
    }
    //here we set the cell to path if it is not at start
    if(maze->cells[row][col]!='S'){
        maze->cells[row][col]='*';
    }
    //order of which we check all possible directions
    if(solveMazeDFS(maze, col, row-1)){ //left
        return 1; 
    }
    if(solveMazeDFS(maze, col+1, row)){ //up
        return 1; 
    }
    if(solveMazeDFS(maze, col, row+1)){ //right
        return 1; 
    }
    if(solveMazeDFS(maze, col-1, row)){ //down
        return 1; 
    }
    //set as visited in order to backtrack
   if(maze->cells[row][col]!='S'){
    maze->cells[row][col]='~';
   }
        return 0;
}

