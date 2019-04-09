// #include <random>

#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

// Analysis:
// Why the parallel algorithm take more time than sequential?
// Why do you add the critical directive to cont variable in parallel mode?

// Busqueda secuencial modo sobrio
void sober_search(int n, long boy_position, bool *founded, int *founded_position, int *matrix){

	printf("Secuential mode \n");

	// cout << matrix[0] << endl;

	// Define execution time variables
	double t1;
	double t2;

	bool local_founded_seq = false; 
	int local_founded_position_seq = 0;
	int cont_seq = 1;

	// Start search
	printf("Start search in sequential sober mode \n");

	t1 = omp_get_wtime();

	// iterate through Rows
	for(int i = 0; i < (n) && cont_seq; ++i){
	// for(int i = 0; i < (n) ; ++i){

		// Iterate through columns
		for(int j = 0; j < (n) && cont_seq; ++j){
		// for(int j = 0; j < (n); ++j){

			// Linear index
			int index = i*n + j;

			// Check if boy is in current position
			if(matrix[index] == 1){

				// Set variables
				// *founded = true;
				// *founded_position = index;
				cont_seq = 0;

				local_founded_seq = true;
				local_founded_position_seq = index;

				//break
				// break;
			}

		}

	}


	// Finish search and show execution time
	t2 = omp_get_wtime();
	printf("Executng time for sequential search in sober mode: %f (msec) \n ", (1000*(t2-t1)));

	// Print message depending if it was founded
	// local_founded_seq ? printf("Boy was founded (seq mode) in position: %i \n", local_founded_position_seq) : printf("Boy was not founded in seq mode\n");

	// Start search in parallel mode
	printf("Start search in parallel sober mode \n");


	int cont = 1;
	bool local_founded_par = false; 
	int local_founded_position_par = 0;
	// int tid = 0;

	t1 = omp_get_wtime();

	// Parallel mode with openmp directive
	#pragma omp parallel shared(cont)
	// #pragma omp parallel 
	{

		// int n_t = omp_get_num_threads();
		// printf("num threads: %i \n", n_t);

		// Doing chunksize
		int tid = omp_get_thread_num();
		int chunk_size = (n)/omp_get_num_threads();
		int start = chunk_size*tid;
		int end = chunk_size*tid + chunk_size;

		// #pragma omp for schedule(static)
		// #pragma omp for
		// iterate through Rows
		for(int i = start; i < end && cont ; ++i){
		// for(int i = 0; i < n && cont ; ++i){
		// for(int i = 0; i < n ; ++i){

		// for(int i=start; i<end && seguir; i++){

			// Iterate through columns
			for(int j = 0; j < (n) && cont; ++j){
			// for(int j = 0; j < (n); ++j){

				// Linear index
				long index = (long)i*n + (long)j;

				// int tid = omp_get_thread_num();

				// printf("Thread %i with index: %i, %i \n", tid, i, j);

				// Check if boy is in current position
				if(matrix[index] == 1){

					// Set variables
					// *founded = true;
					// *founded_position = index;
					#pragma omp critical

					{

						// ¿Por que se agrega esto?

						cont = 0;

					}

					local_founded_par = true;
					local_founded_position_par = index;

					//break
					// break;
				}

			}

		}

	}

	// Finish search and show execution time
	t2 = omp_get_wtime();
	printf("Executng time for parallel search in sober mode: %f (msec) \n ", (1000*(t2-t1)));

	// Print message depending if it was founded
	// local_founded_par ? printf("Boy was founded (par mode) in position: %i \n", local_founded_position_par) : printf("Boy was not founded in par mode\n");


	// If both methods, seq and par founded boy in same position
	if(local_founded_seq && local_founded_par && local_founded_position_seq == local_founded_position_par){

		// Set variables
		*founded = true;
		*founded_position = local_founded_position_seq;
		// cont = false;

	}

	else{

		local_founded_seq ? printf("Parallel mode not found the boy \n") : printf("Sequential mode not found the boy \n");

	}
}

// Analysis

// 1) Analize how is the parallelism of while loop (Base on read, omp cannot parallelize while loop)
// Analize cristobal's code

// Busqueda secuencial en modo borracho
void drunk_search(const long boy_position, bool *founded, const int matrix_size, int *founded_position, int *matrix){

	// Service fro create random number
	random_device r;

	// Counter
	int count = 1;

	double t1,t2;

	bool local_founded_seq = false; 
	int local_founded_position_seq = 0;

	printf("Start seq mode \n");

	// Start time
	t1 = omp_get_wtime();

	// While boy is not founded
	while(!local_founded_seq){

		// int ra = rand() % (matrix_size-1);
		long rn = r() % matrix_size;

		// if random position is equal to boy position
		if(matrix[rn] == 1){

			// Set variables
			// *founded = true;
			// *founded_position = rn;

			local_founded_seq = true;
			local_founded_position_seq = rn;
			//break
			// break;

		}

		// add 1 to counter
		++count;

	}

	t2 = omp_get_wtime();
	printf("Executng time for sequential search in drunk mode: %f (msec) \n ", (1000*(t2-t1)));

	// Print message
	printf("Number of Iterations: %i \n", count);

	// Counter
	count = 1;

	printf("Start parallel mode \n");

	bool local_founded_par = false; 
	int local_founded_position_par = 0;

	// Start time
	t1 = omp_get_wtime();

	// Parallel mode
	#pragma omp parallel 

	// While boy is not founded
	while(!local_founded_par){

		// int ra = rand() % (matrix_size-1);
		long rn = r() % matrix_size;

		// if random position is equal to boy position
		if(matrix[rn] == 1){

			// Set variables
			// *founded = true;
			// *founded_position = rn;
			local_founded_par = true;
			local_founded_position_par = rn;
			//break
			// break;

		}

		// add 1 to counter
		++count;

	}

	t2 = omp_get_wtime();
	printf("Executng time for sequential search in drunk mode: %f (msec) \n ", (1000*(t2-t1)));

	// Print message
	printf("Number of Iterations: %i \n", count);

	// If both methods, seq and par founded boy in same position
	if(local_founded_seq && local_founded_par && local_founded_position_seq == local_founded_position_par){

		// Set variables
		*founded = true;
		*founded_position = local_founded_position_seq;
		// cont = false;

	}

	else{

		local_founded_seq ? printf("Parallel mode not found the boy \n") : printf("Sequential mode not found the boy \n");

	}
}

#endif