#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include <iostream>

using namespace std;

// (1) haga un programa saxpy y mida el tiempo del calculo
// (2) introduzca paralelismo con OpenMP, de distintas formas
//      a) funcion saxpy1 con parallel for
//      b) funcion saxpy2 con parallel for y chuncksize = 1
//      c) funcion saxpy3 manual con particion segmentos continuos
//      d) funcion saxpy4 manual con particion segmentos intercalados
// (3) experimente comparando el resultado de cada metodo a distintos tamanos
// (4) saque conclusiones sobre el rendimiento obtenido, como escala con n y p


// Analysis Leo
// 1) Saxpy1 and saxp3 should have similar execution time because they divide the total work (n) 
//    in similar chunk size and continuos (saxpy1 assign chunksize automatically and saxpy3 manually)
// 2) Saxpy2 and saxpy4 should have similar execution time because they assign the chunk size equal to 1
//    to each work (element of vector) is assigned intercalary.

// 3) For n large: Saxpy 1 and Saxpy3 (continuos segments of work)has a better perfomance than saxpy2 and saxpy4.
//    It must be because interleaved segments can generate false sharing (invalidate of cache line and
//    it obligate to reload the cache line from memory) taking more time in an additional "process".

//     The best option is to assign the work of thread (number of elements) the more separetad and contiuos possible.

//  For n small: saxpy 1-3 and saxpy 2-4 has similar behavior.

// Fill a vector with c values in each element
void init_vec(int *a, int n, int c){

    for(int i = 0; i<n; ++i){

        a[i] = c;

    }

}

// funcion saxpy1 con parallel for
void saxpy1(int a, int n, int *s, int *x, int *y){

    // Parallel for
	#pragma omp parallel for

    // For parallelized
	for(int i = 0; i < n; ++i){

        // Make saxpy operation
		s[i] = a * x[i] + y[i];

	}

}

// funcion saxpy2 con parallel for y chuncksize = 1
void saxpy2(int a, int n, int *s, int *x, int *y, int chunksize){

	// printf("hola");

	#pragma omp parallel for schedule(static, chunksize)

	for(int i = 0; i < n; ++i){

		s[i] = a * x[i] + y[i];

	}

}

// funcion saxpy3 manual con particion segmentos continuos
void saxpy3(int a, int n, int *s, int *x, int *y){

    // #pragma omp parallel
    #pragma omp parallel shared(s,x,y)

    {

        int chunk_size = n/omp_get_num_threads();

        int tid = omp_get_thread_num();

        int start = chunk_size*tid;

        int end = chunk_size*tid + chunk_size;

        for(int i = start; i < end; ++i){

            s[i] = a * x[i] + y[i];

        }

    }

}

// funcion saxpy4 manual con particion segmentos intercalados
void saxpy4(int a, int n, int *s, int *x, int *y){

    #pragma omp parallel shared(s,x,y)
    {

        int n_t = omp_get_num_threads();

        int tid = omp_get_thread_num();

        for(int i = tid; i < n; i += n_t){

            s[i] = a * x[i] + y[i];

        }

    }

}

// Main function
int main(int argc, char **argv){

    if(argc != 4){

        fprintf(stderr, "error, ejecutar como: ./prog N threads method \n");

        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);

    int n_t = atoi(argv[2]);

    // int chunksize = atoi(argv[3]);

    int method = atoi(argv[3]);

    omp_set_num_threads(n_t);

    int nt = 1;

    double t1=0.0, t2=0.0;

    int a = 10;

    // Creacion vectors
    int *x = new int[N];
    int *y = new int[N];
    int *s = new int[N];

    // Init vectors
    init_vec(x, N, 1);
    init_vec(y, N, 2);
    init_vec(s, N, 1);


    switch (method){

        // funcion saxpy1 con parallel for
        case 1:

            // int *s
            t1 = omp_get_wtime();

            // Call saxpy
            saxpy1(a, N, s, x, y);

            // Take final time
            t2 = omp_get_wtime();

            printf("Method 1: N=%i    threads=%i   %f secs\n", N, n_t, t2-t1);

            break;

        // funcion saxpy2 con parallel for y chuncksize = 1
        case 2:

            // int *s
            t1 = omp_get_wtime();

            saxpy2(a, N, s, x, y, 1);

            t2 = omp_get_wtime();

            printf("Method 2: N=%i    threads=%i   %f secs chunksize  = %i \n", N, n_t, t2-t1, 1);

            break;

       // funcion saxpy3 manual con particion segmentos continuos 
        case 3:

            // int *s
            t1 = omp_get_wtime();

            saxpy3(a, N, s, x, y);

            t2 = omp_get_wtime();

            printf("Method 3: N=%i    threads=%i   %f secs \n", N, n_t, t2-t1);

            break;

        // funcion saxpy4 manual con particion segmentos intercalados
        case 4:

            // int *s
            t1 = omp_get_wtime();

            saxpy4(a, N, s, x, y);

            t2 = omp_get_wtime();

            printf("Method 4: N=%i    threads=%i   %f secs \n", N, n_t, t2-t1);

            break;

    }

}
