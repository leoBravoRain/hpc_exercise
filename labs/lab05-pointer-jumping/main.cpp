#include <iostream>
#include <cstdio>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// int par_find_root(int *graph)
// Sequential finding
int seq_find_root(int *graph, int node, int n){

	int pointer;
	int next;

	for(int i = 0; i < n; ++i){

		// int pointer = graph[i];
		
		pointer = i;

		// printf("node: %i\n\n", pointer);

		next = graph[pointer];

		// printf("next: %i\n", next);

		// int dist = 0;

		//printf("distance %i\n", dist);

		while(pointer != next){

			// Update pointer
			pointer += 1;

			// printf("hi\n");
			// Update next
			next = graph[pointer];


			// dist += 1;

			// printf("pointer: %i\n", pointer);	

			// printf("next: %i\n", next);

			// printf("distance %i\n", dist);

		}

		// printf("FIND THE ROOT \n\n");
		graph[i] = pointer;

	}

	// printf("distance from node %i to root: %i\n", node, dist);

	return graph[node];

}

// Parallel root finding
int par_find_root(int *graph){

	// printf("parallel function\n");

	#pragma omp parallel
	{

		int tid = omp_get_thread_num();

		// printf("%i\n", tid);

		while(graph[tid] != graph[graph[tid]]){

			graph[tid] = graph[graph[tid]];

			// printf("thread %i in node: %i \n", tid, graph[tid]-1);

		}

		// while(p[tid] != p[ p[tid] ]){
		// 	p[tid] = p[ p[tid] ]; 
		// 	printf("thread %i  it %i\n", tid, c++);
		// 	//#pragma omp barrier
		// }

	}

	return graph[0];

}

void init_graph(int *graph, int n){

	for(int i = 0; i <= (n-1); ++i){

		graph[i] = i + 1;
	}

	graph[n-1] = n-1;

}

void print_graph(int *graph, int n){

	// printf("Graph: \n\n");
	for(int i = 0; i < n ; ++i){

		printf("%i\n", graph[i]);
	}

	// printf("\n\n");
}

int main(int argc, char **argv){

	if(argc != 2){
		fprintf(stderr, "./prog n \n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	// int nt = atoi(argv[2]);
	int nt = n;

	int graph [n] = {};
	int graph_par [n];

	int root;

	init_graph(graph, n);
	init_graph(graph_par, n);

	// printf("initial graph: \n");

	// print_graph(graph, n);

	// int node = atoi(argv[2]);

	double t1, t2;
    
    t1 = omp_get_wtime();

	root = 	seq_find_root(graph, n-1, n);

	t2 = omp_get_wtime() - t1;

	printf("Sequential time: %f\n", t2);

	// printf("final graph: \n");
	
	// print_graph(graph, n);


	// Parallel form
	omp_set_num_threads(nt);

	t1 = omp_get_wtime();

	root = par_find_root(graph_par);

	t2 = omp_get_wtime() - t1;

	printf("Parallel time: %f\n", t2);

	// printf("par graph\n");

	// print_graph(graph_par, n);

	return 0;
}
