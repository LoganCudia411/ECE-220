#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
    // Declare variables
    int n_pair;
    float omega1,omega2,fx,x_i; 
    
    // Prompt user for input
    printf("Enter values of n, omega1, and omega2 in that order.\n");
    
    
    // Get user input
    scanf("%d, %f, %f", &n_pair, &omega1, &omega2); 
    // Compute function output
    /* for i from 0 to n-1
     *     compute and print xi and f(xi)
     *     use sin() function from math.h
     */
    int loop ;
    for (loop =0; loop < n_pair; loop++)
    { 
         ; 
        x_i = (loop* M_PI)/n_pair;
        fx= sin(omega1*x_i)+ (.5*sin(omega2*x_i));
    
        printf("(%f,%f)\n",x_i,fx);
      
     }

    return 0;
}

