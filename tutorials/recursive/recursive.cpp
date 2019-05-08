// #include <cstdio>
// #include <stdio.h>

#include <stdlib.h>
#include <stdio.h>

int factorial(int n){

	printf("n = %i \n", n);

	// Base case
	if(n == 0){

		printf("n == 0\n");

		return 1;

	}

	// Recursive case
	else{

		printf("n > 0 \n");

		// Smaller instace than the original problem

		printf("Call to Factorial of (n - 1) = %i \n", n-1);

		int fact = n*factorial((n-1));

		printf("return factorial result of %i = %i \n", n, fact);

		return fact;
			
	}

}

int palindromo(){

	return 0;

}

int main(int argc, char *argv[]){

	int n = atoi(argv[1]);

	// printf("The word %i is palindromo?  %i \n", n, palindromo());

	printf("Factorial of %i is: %i \n", n, factorial(n));

	return 0;

}