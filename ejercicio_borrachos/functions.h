// #include <random>

#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

// Busqueda secuencial modo sobrio
void seq_sobrio(int n, long r, bool *founded, int *boy_position){

	// iterate through Rows
	for(int i = 0; i < (n); ++i){

		// Iterate through columns
		for(int j = 0; j < (n); ++j){

			// Linear index
			int index = i*n + j;

			// Check if boy is in current position
			if(index == r){

				// Set variables
				*founded = true;
				*boy_position = index;

				//break
				break;
			}

		}

	}

}

// Busqueda secuencial en modo borracho
void seq_borracho(const long boy_position, bool *founded, const int matrix_size, int *founded_position){

	// Service fro create random number
	random_device r;

	// Counter
	int count = 1;

	// While boy is not founded
	while(!(*founded)){

		// int ra = rand() % (matrix_size-1);
		long rn = r() % matrix_size;

		// if random position is equal to boy position
		if(rn == boy_position){

			// Set variables
			*founded = true;
			*founded_position = rn;

			//break
			break;

		}

		// add 1 to counter
		++count;

	}

	// Print message
	printf("Number of Iterations: %i \n", count);

}

#endif