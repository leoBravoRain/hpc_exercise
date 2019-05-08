#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include <cstdio>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <omp.h>

#include "functions.h"

#include <unistd.h> // sleep function

using namespace std;

// ./prog n grupo modo
int main(int argc, char *argv[]){

	// Check for number of arguments
	if(argc != 4){

		printf("\n You must write:\n 1) n (n° columns) \n 2) grupo (num threads) \n 3) modo (0: sobrio, 1: borracho)\n");

		exit(EXIT_FAILURE);

	}

	// Matrix size
	int n = atoi(argv[1]);
	int group = atoi(argv[2]);
	int modo = atoi(argv[3]);

	// Set number of threads
	// omp_set_num_threads
	omp_set_num_threads(group);

	// Flatten matrix
	long matrix_size = (long)n*n;

	printf("User input for n: %i \n", n);
	printf("Matrix size: %li \n", matrix_size);

	// Create the matrix
	int *matrix = new int[matrix_size] {};

	// set the position of boy randomly
	/* initialize random seed: */
	// srand (time(NULL));

	random_device r;

	// int r = (int)r()%matrix_size;
	long boy_position = r() % matrix_size;

	printf("Boy position: %li \n", boy_position);

	// // Set the boy in matrix
	matrix[boy_position] = 1;

	// // variable for indicate is boy was founded
	bool founded(false);
	int founded_position(0);

	// Iterate through the matrix

	// busqueda sobrio
	if(modo == 0){

		printf("Sobrio mode\n"); fflush(stdout);

		// sleep(2);

		// Sequential
		sober_search(n, boy_position, &founded, &founded_position, matrix);

	}

	// Drunk mode
	else if(modo == 1){

		printf("Drunk mode \n");

		// Drunked Sequential
		std::pair<int, int>  boy_pos = drunk_search(boy_position, &founded, matrix_size, &founded_position, matrix, n, group);

		// cout << (boy_pos.first*n+boy_pos.second) << endl;
	}

	// Print messagge
	// founded ? printf("Boy was founded in position: %i \n", founded_position) : printf("Boy wasn't founded.\n");
	founded ? printf("Boy was founded \n") : printf("Boy wasn't founded.\n");

	// return value
	return 0;

}