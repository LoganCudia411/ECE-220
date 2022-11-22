#include "prime.h"
#include <stdio.h>
int is_prime(int n){
  // Return 1 if n is a prime, and 0 if it is not
  
  int i;  
  if(n==2){
    return 1;
  }
  for (i = 2; i < n; i++){
    if (n ==0 || n ==1){
    return 0;
    }
    if(n % i == 0){
      return 0; 
    }
}
return 1; 
}
