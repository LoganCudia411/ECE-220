#include <stdlib.h>
#include <stdio.h>
//The function print_semiprimes takes input numbers [a,b] and prints all of the 
//semiprime numbers in between that range including a & b. A semiprime number is the product of 
// two prime numbers. The error of double within the print_semiprimes occured because we did not 
// exit the nested for-loop after discovering a semiprime. Additionally, the conditions for the if
// statements were incorrect since we want to know if the number is prime or if returned the value 1 from 
// the is_prime nested function. For the is_prime function, the return 0 and return 1 needed to be swapped. 
// Lastly, we needed to use the ret variable in the semiprime function to return 1 or 0 
// back to the main function. 

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1 || number == 0) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0 ) { //check if the remainder is 0
        return 0; //exit loop and return 0 if not prime
        }
    }
    return 1;  // if we go through the loop and do not
            // encounter the if statement, number is prime and return 1
   }

/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0; //value we are returning
    for (i = a; i <=b; i++) { //for each item in interval
        // check if semiprime, then if it is j must be a cofactor
        // if j is prime then k has to be prime as well (j*k = semiprime)
        for (j = 2; j <= i; j++) { 
            if (i%j == 0) {
                if (is_prime(j)==1) {
                    k = i/j; //check if cofactor is prime 
                    if (is_prime(k)==1) {
                        printf("%d ", i);
                        ret = 1;
                        break; // break to exit initial for loop and 
                              //prevent double printing
                        
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
