// #include <random>

#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

// Analysis:
// Why the parallel algorithm take more time than sequential?
// Why do you add the critical directive to cont variable in parallel mode?

// Busqueda secuencial modo sobrio
// void sober_search(int n, long boy_position, bool *founded, int *founded_position, int *matrix){
std::pair<int,int> sober_search(int n, long boy_position, bool *founded, int *founded_position, int *matrix){

	printf("Secuential mode \n");

	// cout << matrix[0] << endl;

	// Define execution time variables
	double t1;
	double t2;

	bool local_founded_seq = false; 
	// int local_founded_position_seq = 0;
	int cont_seq = 1;

	// coordenates of boy 
	std::pair<int, int> local_founded_position_seq(-1,-1);

	// cout << location.second << endl;

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
				local_founded_position_seq = std::pair<int, int> (i,j);

				//break
				// break;
			}

		}

	}

	// cout << local_founded_position_seq.first << endl;

	// Finish search and show execution time
	t2 = omp_get_wtime();
	printf("Executng time for sequential search in sober mode: %f (msec) \n ", (1000*(t2-t1)));

	// Print message depending if it was founded
	// local_founded_seq ? printf("Boy was founded (seq mode) in position: %i \n", local_founded_position_seq) : printf("Boy was not founded in seq mode\n");

	// Start search in parallel mode
	printf("Start search in parallel sober mode \n");


	int cont = 1;
	bool local_founded_par = false; 
	// int local_founded_position_par = 0;
	// int tid = 0;
	std::pair<int, int> local_founded_position_par(-1,-1);

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
					// local_founded_position_par = index;
					local_founded_position_par = std::pair<int, int>(i,j);

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
		// *founded_position = local_founded_position_seq;
		// cont = false;

		return local_founded_position_seq;

	}

	else{

		// local_founded_seq ? printf("Parallel mode not found the boy \n") : printf("Sequential mode not found the boy \n");

		return local_founded_position_seq;

	}
}

// Analysis

// 1) Analize how is the parallelism of while loop (Base on read, omp cannot parallelize while loop)
// Analize cristobal's code

// Busqueda secuencial en modo borracho
void drunk_search(const long boy_position, bool *founded, const int matrix_size, int *founded_position, int *matrix, const int n){

	// Service fro create random number
	random_device r;

	// Counter
	int count = 0;

	double t1,t2;

	bool local_founded_seq = false; 
	int local_founded_position_seq = 0;

	long rn;

	int row, col;
	int index;

	printf("Start seq mode \n");

	// int ra = rand() % (matrix_size-1);
	row = r() % n;
	col = r() % n;

	// printf("%i, %i \n", row, col);

	index = row*n+col;

	// Get first matrix[rn value]
	int val = matrix[index];

	// Start time
	t1 = omp_get_wtime();

	// While boy is not founded
	while(val == 0 && !local_founded_seq){

		row = r() % n;
		col = r() % n;

		index = row*n+col;

		// printf("while: %i, %i \n", row, col);

		// int ra = rand() % (matrix_size-1);
		// rn = r() % matrix_size;

		// if random position is equal to boy position
		if(matrix[index] == 1){

			// Set variables
			// *founded = true;
			// *founded_position = rn;

			local_founded_seq = true;
			local_founded_position_seq = rn;
			val = 1;
			//break
			// break;

		}

		// add 1 to counter
		++count;

	}

	// printf("val value: %i\n", val);

	t2 = omp_get_wtime();
	printf("Executng time for sequential search in drunk mode: %f (msec) \n ", (1000*(t2-t1)));

	// Print message
	printf("Number of Iterations: %i \n", count);



	// Parallel mode



	// Counter
	count = 0;

	printf("Start parallel mode \n");

	bool local_founded_par = false; 
	int local_founded_position_par = 0;
	// int tid = 0;
	int go = true;

	// Start time
	t1 = omp_get_wtime();

	// random_device r;
	std::vector<std::default_random_engine> generators;
	for (int i = 0, N = omp_get_max_threads(); i < N; ++i) {
	    generators.emplace_back(default_random_engine(r()));
	}

	// int N = omp_get_num_threads();
	// vector<int> v(N);

	// int row, col;
	// int val_par;
	// int index;

	// Parallel mode
	#pragma omp parallel shared(go)

	{

		// int row, col;
		int tid = omp_get_thread_num();
		// int ra = rand() % (matrix_size-1);

		// int rn = r() % matrix_size;

		// printf("random number thread %i: %i \n", tid, val);

		default_random_engine& engine = generators[tid];

		uniform_int_distribution<int> uniform_dist(0, n-1);

		// row, column of thread
		row = uniform_dist(engine);
		col = uniform_dist(engine);

		// printf("%i\n", );

		// Get index
		index = row * n + col;

		// get value with index
		int val_par = matrix[index];

		// printf("INITIAL. row, colum of thread %i: %i, %i. val: %i \n", tid, row, col, val_par);
		// cout << uniform_dist(engine) << endl;

		// Perform heavy calculations
		// cout << uniform_int_distribution<int> uniform_dist(1, n) << endl;

		// cout << uniform_int_distribution<int> uniform_dist(1, n) << endl;

		// v[i] = uniform_dist(engine); // I assume this is thread unsafe

		// int val = matrix[rn];

		// While boy is not founded
		while(val_par == 0 && go){

			// row, column of thread
			row = uniform_dist(engine);
			col = uniform_dist(engine);

			// printf("%i\n", );

			// Get index
			index = row * n + col;

			// get value with index
			val_par = matrix[index];

			// printf("while. row, colum of thread %i: %i, %i. val: %i \n", tid, row, col, val_par);

			// default_random_engine& engine = generators[omp_get_thread_num()];

			// // Perform heavy calculations
			// uniform_int_distribution<int> uniform_dist(1, 100);
			// v[i] = uniform_dist(engine); // I assume this is thread unsafe

			// int ra = rand() % (matrix_size-1);
			// long rn = r() % matrix_size;

			// tid = omp_get_thread_num();

			// printf("random number for thread %i: %li \n", tid, rn);

			// if random position is equal to boy position
			// if(matrix[rn] == 1){

			// 	// Set variables
			// 	// *founded = true;
			// 	// *founded_position = rn;
			// 	local_founded_par = true;
			// 	local_founded_position_par = rn;
			// 	//break
			// 	// break;

			// }

			// add 1 to counter
			#pragma omp critical
			{

				++count;

			}

		}

		// If one thread found the boy
		if(val_par != 0){

			local_founded_par = true;
			
			// Set go on false for every threads
			#pragma omp critical
			{
				go = false;
			}

		}


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