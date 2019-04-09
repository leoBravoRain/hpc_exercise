// #include <iostream>
// #include "omp.h"
// #include <stdio.h>
// #include <stdlib.h>

// #include <unistd.h>

// using namespace std;

// #define THREADS 4
// #define CHUNK_SIZE 100

#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
using namespace std;

// int main(int argc, char *argv[]){

// 	if(argc != 4){

// 		printf("./program_name \n mode (0:seq, 1: parallel) \n matrix_size (ej: 10) \n num_threads (ej: 2) \n");

// 		exit(EXIT_FAILURE);

// 	}

// 	// 0: parallel mode
// 	// 1: sequential mode
// 	int mode = atoi(argv[1]);
// 	int n = atoi(argv[2]);
// 	int th = atoi(argv[3]);

// 	// thread id
// 	int tid;

// 	// Number of threads
// 	int n_threads = th;

// 	// Set thread number
// 	// omp_set_num_threads(n_threads);

// 	// Set matrix size
// 	int matrix_size = n;

// 	int matrix [matrix_size];

// 	fill_n(matrix, matrix_size, 1);

// 	printf("Matrix size: %i \n", matrix_size);

// 	// printf("Initial matrix: \n");

// 	// for(int i = 0; i < matrix_size; ++i){

// 	// 	printf("%i \n", matrix[i]);

// 	// }	

// 	// For do matrix multiplication: 
// 	// result = const_mat * matrix
// 	int const_mat [matrix_size];

// 	fill_n(const_mat, matrix_size, 2);

// 	// printf("Const matrix: \n");

// 	// for(int i = 0; i < matrix_size; ++i){

// 	// 	printf("%i \n", const_mat[i]);

// 	// }	

// 	int result [matrix_size] = {0};

// 	// printf("Result matrix: \n");

// 	// for(int i = 0; i < matrix_size; ++i){

// 	// 	printf("%i \n", result[i]);

// 	// }

// 	// Variable for check the reduction
// 	int red_var = 0;

// 	printf("Start Processing matrix \n");

// 	printf("chunk size: %i \n", CHUNK_SIZE);

// 	// Parallel mode
// 	if(mode == 0){

// 		printf("Enter to parallel mode \n"); 

// 		double t1;
// 		double t2;


// 		// #pragma omp parallel private(tid)
// 		// #pragma omp parallel for

// 		// {

// 			// OMP automatic partitioning space iteration

// 			// #pragma omp parallel for reduction(+:red_var)

// 			printf("static shcedule \n");

// 			printf("Create sections parallel \n");

// 			int sum_critical = 0;
// 			int sum_par = 0;


// 			// Create sections
// 			t1 = omp_get_wtime(); // Start time
// 			#pragma omp parallel sections

// 			{

// 				#pragma omp section

// 				{

// 					printf("Section executed by thread %i \n ", omp_get_thread_num() );

// 					for(int i = 0; i< matrix_size*100; ++i){

// 						int a = i;
// 					}


// 				}

// 				#pragma omp section

// 				{
// 					printf("Section executed by thread %i \n ", omp_get_thread_num() );

// 					for(int i = 0; i< matrix_size*500; ++i){

// 						int a = i;
// 					}


// 				}

// 			}

// 			// Print execution time
// 			t2 = omp_get_wtime();

// 			printf("Finish parallel sections \n");


// 			printf("Executng time for random task parallel: %f (msec) \n ", (1000*(t2-t1)));

// 			printf("Executing same random task than before but sequentially \n");

// 			printf("Start sequential 'section' \n");

// 			t1 = omp_get_wtime();

// 			{

// 				printf("Section executed by thread %i \n ", omp_get_thread_num() );

// 				for(int i = 0; i< matrix_size*100; ++i){

// 					int a = i;
// 				}


// 			}


// 			{

// 				printf("Section executed by thread %i \n ", omp_get_thread_num());

// 				for(int i = 0; i< matrix_size*500; ++i){

// 					int a = i;
// 				}

// 			}


// 			// Print execution time
// 			t2 = omp_get_wtime();

// 			printf("Finish seq sections\n");

// 			printf("Executing time for random task sequential: %f (msec) \n ", (1000*(t2-t1)));

// 			// Dynamic schedule
// 			// #pragma omp parallel for schedule(dynamic) num_threads(4)
// 			t1 = omp_get_wtime(); // Get start time
// 			#pragma omp parallel for schedule(static) num_threads(THREADS)

// 			for(int i = 0; i < matrix_size; ++i){

// 				int tid = omp_get_thread_num();

// 				// int n_t = omp_get_num_threads();

// 				printf("Thread %i has sum_par value: %i \n", tid, sum_par);

// 				sum_par = sum_par + matrix[i];

// 				printf("Thread %i has sum_par value: %i \n", tid, sum_par);

// 				#pragma omp critical(sum_critical)

// 				{

// 					printf("Critical: num threads: %i \n id thread working: %i \n",omp_get_num_threads() , omp_get_thread_num());

// 					sum_critical = sum_critical + matrix[i];

// 				}


// 				// sleep(tid);

// 				// printf("thread %i (from %i total threads) is done \n", tid, n_t);

// 				// printf("const: %i, matrix value: %i, result = %i \n", const_mat[i], matrix[i], const_mat[i]*matrix[i]);

// 				// printf("total threads: %i \n", omp_get_num_threads());

// 				// if(tid == 0 and i == 0){

// 				// 	printf("total threads: %i\n chunk size: %i \n", n_t, (matrix_size/n_t));

// 				// }

// 				// result[i] = const_mat[i]*matrix[i];

// 				// // Reduction
// 				// red_var += matrix[i];

// 				// printf("thread: %i. Start in: %i. Finish in: %i. Working on index: %i \n", tid, start-1, finish, i);

// 			}

// 			printf("Work done !. \n It pass the barrier \n");

// 			printf("Result for sum with critical: %i \n", sum_critical);

// 			printf("Result for sum with parallel: %i \n", sum_par);

// 			// Print executin time 
// 			t2 = omp_get_wtime();

// 			double static_time = 1000*(t2-t1);
// 			printf("Execution time of parallel static schedule for loop (msec): %f \n", static_time);

// 			// Dynamic schedule

// 			t1 = omp_get_wtime();

// 			printf("dynamic shcedule \n");
// 			#pragma omp parallel for schedule(dynamic, CHUNK_SIZE) num_threads(THREADS)

// 			for(int i = 0; i < matrix_size; ++i){

// 				// int tid = omp_get_thread_num();

// 				// int n_t = omp_get_num_threads();

// 				// sleep(tid);

// 				// printf("thread %i (from %i total threads) is done \n", tid, n_t);

// 			}			

// 			t2 = omp_get_wtime();

// 			double dynamic_time = 1000*(t2-t1);

// 			printf("Execution time of parallel dynamic schedule for loop (msec): %f \n", dynamic_time);


// 			printf("Difference dynamic - static: %f (msec) \n", (double)(dynamic_time - static_time));


// 			// Guided schedule

// 			// Guided schedule

// 			t1 = omp_get_wtime();

// 			printf("guided shcedule \n");
// 			#pragma omp parallel for schedule(guided) num_threads(THREADS)

// 			for(int i = 0; i < matrix_size; ++i){

// 				// int tid = omp_get_thread_num();

// 				// int n_t = omp_get_num_threads();

// 				// sleep(tid);

// 				// printf("thread %i (from %i total threads) is done \n", tid, n_t);

// 			}			

// 			t2 = omp_get_wtime();

// 			double guided = 1000*(t2-t1);

// 			printf("Execution time of parallel guided schedule for loop (msec): %f \n", guided);


// 			// printf("Difference dynamic - static: %f (msec) \n", (double)(dynamic_time - static_time));

// 			// Partitioning iteration space by ourself

// 			// tid  = omp_get_thread_num();

// 			// n_threads = omp_get_num_threads();

// 			// int start = tid*(matrix_size/n_threads) + 1;

// 			// int finish = (tid + 1)*(matrix_size/n_threads);

// 			// printf("thread: %i. Start in: %i. Finish in: %i. \n", tid, start-1, finish);

// 			// for(int i = (start-1); i < finish; ++i){

// 			// 	matrix[i] += 1;

// 			// 	printf("thread: %i. Start in: %i. Finish in: %i. Working on index: %i \n", tid, start-1, finish, i);

// 			// }

// 		// }

// 	}

// 	// Sequential mode
// 	if(mode == 1){

// 		printf("Enter to sequential mode \n");

// 		double t1 = omp_get_wtime();

// 		{

// 			for(int i = 0; i < matrix_size; ++i){

// 				// printf("%i \n",matrix[i]);

// 				// matrix[i] += 1;
// 				// result[i] = const_mat[i]*matrix[i];

// 				red_var += matrix[i];

// 				// printf("%i \n",matrix[i]);

// 			}

			
// 		}

// 		double t2 = omp_get_wtime();

// 		printf("Execution time of sequential for loop (msec): %f \n", 1000*(t2-t1));
// 	}

// 	printf("reduction result: %i \n", red_var);

// 	// printf("Final matrix: \n");

// 	// for(int i = 0; i < matrix_size; ++i){

// 	// 	cout << result[i] << endl;

// 	// }

// 	// printf("\n \n");

// 	return 0;
// }

int main(int argc, char *argv[]) {
    random_device r;
    std::vector<std::default_random_engine> generators;
    for (int i = 0, N = omp_get_max_threads(); i < N; ++i) {
        generators.emplace_back(default_random_engine(r()));
    }

    int N = atoi(argv[1]);
    vector<int> v(N);

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {

        // Get the generator based on thread id
        default_random_engine& engine = generators[omp_get_thread_num()];

        cout << engine << endl;
        
  //       // Perform heavy calculations
  //       uniform_int_distribution<int> uniform_dist(1, 10);

		// // cout << uniform_dist << endl;

  //       cout << uniform_dist(engine) << endl;

  //       v[i] = uniform_dist(engine); // I assume this is thread unsafe

        // cout << v[i] << endl;

    }


    // for(int i = 0; i < N; ++i){

    // 	// printf("Total threads %i, running thread %i, random number: %i \n", omp_get_num_threads(), omp_get_thread_num(), v[i]);
    // 	cout << v[i] << endl;

    // }
    return 0;
}