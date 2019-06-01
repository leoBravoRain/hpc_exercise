#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

void init_array(int n, double *a){

	// init array
	for(int i = 0; i < n; ++i){

		a[i] = (double)(rand())/(double)RAND_MAX;

	}

}

void print_a(int n, int *a){

	for(int i = 0; i < n; ++i){

		printf("%i\n", a[i] );

	}

}

double seq_reduction(double *a, int n){

	double sum = 0;

	// reduction: sum
	for(int i = 0; i < n; ++i){

		sum += a[i];

	}

	return sum;

}

double par_reduction(double *a, int n, int nt){

	double sum = 0.0f;

	#pragma omp parallel for reduction(+: sum)
	for(int i = 0; i < n; ++i){

		sum += a[i];

	}

	return sum;
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
	double *array = (double*)malloc(sizeof(double) * n);

	// Init array
	init_array(n, array);

	// define
	double sum, par_sum;
	float t_aux, t1;

	// Seq reduction
    // printf("Seq reduction \n");

    // aux time
    t_aux = omp_get_wtime();

    // call to seq reduction
    sum = seq_reduction(array, n);

    // final time
    t1 = omp_get_wtime() - t_aux;

    // print results
    // printf("result of reduction: %f\n", sum);
    printf("Time for seq reduction: %f [ms]\n", t1*1000);

    // Paralellized reduction
    // printf("Par reduction \n");

    // aux time
    t_aux = omp_get_wtime();

    // par reduction
    par_sum = par_reduction(array, n, nt);

    // final time
    t1 = omp_get_wtime() - t_aux;

    // print results
    // printf("result of reduction: %f\n", par_sum);
    printf("Time for par reduction: %f \n [ms]", t1*1000);
    printf("difference between reduction values: %f \n", sum - par_sum );

    // free memory
    free(array);
    
	return 0;

}