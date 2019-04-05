#include <stdio.h>

int main(){

	int n_t = 10;

	#pragma omp parallel num_threads(n_t)

	printf("Hello, I am parrallel computing\n");

	return 0;

}