#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

void init_array(int n, int *a){

	// init array
	for(int i = 0; i < n; ++i){

		a[i] = (int)rand() %10;

	}

}

void print_a(int n, int *a){

	for(int i = 0; i < n; ++i){

		printf("%i\n", a[i] );

	}

}

int seq_reduction(int *a, int n){

	int sum = 0;

	// reduction: sum
	for(int i = 0; i < n; ++i){

		sum += a[i];

	}

	return sum;

}

int par_reduction(int *a, int n, int nt){

	// int sum = 0;

	int *red_array = (int*)malloc(sizeof(int)*nt);

	#pragma omp parallel shared(red_array)
	{

		// 1) Reduce for each array. The idea is to get 2*threads elements
		int tid = omp_get_thread_num();
		int chunk = (n + nt - 1)/nt;
		int start = tid*chunk;
		int end = tid*chunk + chunk;
		
		int thread_sum = 0;

		// Each thread adds its elements
		for(int i = start; i < end && i < n; ++i){

			thread_sum += a[i];

		}

		red_array[tid] = thread_sum;

		// Wait all threads have their values
		#pragma omp barrier

		// printf("thread %i sum: %i\n", tid, red_array[tid]);

		// if(tid == 0){

		// 	for(int i = 0; i < nt; i++){

		// 		printf("red array [%i] value: %i\n", i, red_array[i]);
		// 	}

		// }
		// Reduction in parallel
		// this is O(log2(n))
		int l = nt/2;

		// printf("l value 0: %i\n", l);

		while(l > 0){

			// printf("l value: %i\n", l );
			if(tid < l){

				// printf("thread %i, update its value from %i to %i\n", tid, red_array[tid + l], red_array[tid + l] + red_array[tid] );

				red_array[tid] = red_array[tid] + red_array[tid + l];

			}

			l = l/2;

			#pragma omp barrier

		}

	}

	// return reduction
	return red_array[0];
	

}

int main(int argc, char *argv[]){

	if(argc != 3){

		printf("./prog array_size n_threads\n");
		exit(EXIT_FAILURE);

	}

	// take length of array
	int n = atoi(argv[1]);
	int nt = atoi(argv[2]);
    omp_set_num_threads(nt);

	// define
	int *array = (int*)malloc(sizeof(int) * n * n);

	init_array(n, array);

	// print_a(n, array);

	int sum;
	float t_aux, t1;
	// Seq reduction
    printf("Seq reduction \n");

    t_aux = omp_get_wtime();

    sum = seq_reduction(array, n);

    t1 = omp_get_wtime() - t_aux;

    printf("result of reduction: %i\n", sum);

    printf("Time for seq reduction: %f \n", t1);

    // Paralellized reduction
    printf("Par reduction \n");

    t_aux = omp_get_wtime();

    sum = par_reduction(array, n, nt);

    t1 = omp_get_wtime() - t_aux;

    printf("result of reduction: %i\n", sum);

    printf("Time for par reduction: %f \n", t1);


	return 0;

}