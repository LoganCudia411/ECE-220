/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

//partners: cudia2

/*In this program, we need to create 3 functions: set seed, start gane, and make guess.
for the first function, set seed, we need to check if the input that the user inputted is valid.
In order to do this, we need to use sscanf and place the string of input from the user. There should 
only be numbers, not letters. If we encounter an invalid input, then the return value of sscanf will be zero.
For the second function, start game, we need to generate a solution set for the given seed. In order to do this, we pass
the address of the arguements into the function. Then we generate a random number from 1-8 using modulous, addition, and rand(). Once
we create a random number, we store those values into the static solution variables. Finally, for the last function, make 
guess, we have to create a function which will sscanf for user guess, check if the guess is formatted corretly, and if it is 
formatted correctly, calculate the number of misplaced and perfect numbers. In order to implement this algorithm,
I first sscanf for user input and check the return value. After verifying the input, I created an two arrays holding
the solution set and the user input set. After getting the user input I moved the values into the arguments of the function, in order
to continiously run the function. Afterwards, we need to calculate the mismatched and perfect numbers. I created a loop to check how many
of the numbers were perfectly placed. Then after this, created a nested for loop checking each remaining unpaired guess for mismatches. After
running the function successfully, we return 1. */

#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//  
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    
//checking to see if seed is valid
    int seed; 
    char post[2];
    

    if(sscanf(seed_str, "%d%1s", &seed, post) == 1){
        srand(seed);
        return 1;
    }
    printf("set_seed: invalid seed\n");
    
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    *one=(rand()%8)+1;
    *two=(rand()%8)+1;
    *three=(rand()%8)+1;
    *four=(rand()%8)+1;

    //your code here
    solution1=*one;
    solution2=*two;
    solution3=*three;
    solution4=*four;
    guess_number=1;
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    int i,j,k;
    int error=0;
    int perfect=0;
    int misplaced=0;
    char post[2];
    int w, x, y, z;
    int input_check = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
    int user_guess[]={w,x,y,z};
    int solution[]={solution1, solution2, solution3, solution4};
    if(w>8 || x>8 || y>8 || z>8 || input_check==0 || input_check!=4 || w<1 || x<1 || y<1 || z<0){
        printf("make_guess: invalid guess\n");
        error=1;
    }
    if(error==1){
        return 0;
    }
    //put user input into the pointers of the argument
    *one=w;
    *two=x;
    *three=y;
    *four=z;
    int guess_paired[4];
    int solution_paired[4];
    //loop too check if everything is in the right place with the right value
    for (i=0; i<4; i++){
        if(user_guess[i]==solution[i]){
            guess_paired[i]=1;
            solution_paired[i]=1;
            perfect++;
        }else if(user_guess[i]!=solution[i]){
            guess_paired[i]=0;
            solution_paired[i]=0;
            continue;
        }
    }
    //if there are mismatches, calculate how many with a nested for loop for the
    //users input and the each solution
    if(perfect!=4){
        for(j=0; j<4; j++){
            if(guess_paired[j]==1){
                continue;
            }
            for(k=0; k<4; k++){
                //if solution is already paired, continue to next solution
                if(solution_paired[k]==1){
                    continue;
                }
                //if we compare solutions and guess at the same spot, we are repeating
                //earlier for loop 
                if(i==j){
                    continue;
                }
                //check to see if there are misplaced pairs
                if(user_guess[j]==solution[k]){
                    guess_paired[j]=1;
                    solution_paired[k]=1;
                    misplaced++;
                    break;
                }else{
                    
                    continue;
                }

            }
        }

    }

   
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
    guess_number++;
    
    return 1;
}




