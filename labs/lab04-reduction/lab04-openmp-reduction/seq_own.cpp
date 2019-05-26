#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main(int argc, char *argv[]){

	if(argc != 2){

		printf("./prog array_size\n");
		exit(EXIT_FAILURE);

	}

	// take length of array
	int n = atoi(argv[1]);

	// define
	int *array = (int*)malloc(sizeof(int) * n * n);

	// init array
	for(int i = 0; i < n; ++i){

		array[i] = (int)rand() %10;

	}

	for(int i = 0; i < n; ++i){

		printf("%i\n", array[i] );

	}

	int sum = 0;

	// reduction: sum
	for(int i = 0; i < n; ++i){

		sum += array[i];

	}

	printf("result of reduction: %i\n", sum);
	
	return 0;

}