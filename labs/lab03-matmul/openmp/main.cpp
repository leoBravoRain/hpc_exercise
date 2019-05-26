#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <omp.h>

void matmul_accum(int oi, int oj, int k, int *a, int *b, int *c, int n, int bsize){
    for(int i=0; i<bsize; ++i){
        for(int j=0; j<bsize; ++j){

            printf("i matrix = %i \nj matrix = %i\nj block = %i\ni block = %i\nk = %i\n", oj, oi, j, i, k);

            int val = 0;
            printf("val = ");
            for(int r=0; r<bsize; ++r){
                val += a[(i+oi)*n+(k*bsize + r)] * b[(k*bsize + r)*n + (j+oj)];
                printf("a[%i] * b [%i] + ", (i+oi)*n+(k*bsize + r), (k*bsize + r)*n + (j+oj));
            }

            printf("\n");
        //printf("val = %i\n", val);
        //getchar();
            c[(i+oi)*n + (j+oj)] += val;
            printf("C[%i] \n", (i+oi)*n + (j+oj));

        }
    }
}
// implementar
void block_matmul(int *a, int *b, int *c, int n, int bsize){
    int blocks = n/bsize;
    // #pragma omp parallel for
    for(int i=0; i<n; i=i+bsize){
        for(int j=0; j<n; j=j+bsize){
            for(int k=0; k<blocks; ++k){
                matmul_accum(i, j, k, a, b, c, n, bsize);
            }
        }
    }
}

void min_mat_mul(int *a, int *b, int *c, int n, int bsize, int oi, int oj, int k){

    int val;

    // Iter by block row
    for(int i = 0; i < bsize; ++i){

        // iter by block column
        for(int j = 0; j < bsize; ++j){

            val = 0;

            // iter inside a row or column of block
            for(int r = 0; r < bsize; ++r){

                // Accumulate value
                val += a[(i+oi)*n+(k*bsize + r)] * b[(k*bsize + r)*n + (j+oj)];

            }

            c[(i+oi)*n + (j+oj)] += val;
        }

    }

}

void block_mat_mul(int *a, int *b, int *c, int n, int bsize){

    // n° block
    int blocks = n / bsize;

    // iter by row
    for(int i = 0; i < n; i += bsize){

        // iter by colum
        for(int j = 0; j < n; j += bsize){

            // iter by block
            for(int k = 0; k < blocks; ++k){

                // Multiply each min matrix (size: bsize x bsize)
                min_mat_mul(a, b, c, n, bsize, i, j, k);

            }


        }


    }

}


void mat_mul_seq(int *a, int *b, int *c, int n){

    // row
    for(int i = 0; i < n; ++i){

        // column
        for(int j = 0; j < n; ++j){

            int val = 0;

            // index by each row and column
            for(int k = 0; k < n; ++k){

                val += a[i*n + k]*b[k*n + j];

            }

            c[i*n + j] = val;

        }

    }

}

void init_mat(int *a, int n){

    for(int i = 0; i < (n*n); ++i){

        a[i] = i + 1;

    }

}


void init_mat_val(int *c, int n, int val){

    for(int i = 0; i < n*n; ++i){

        c[i] = val;

    }

}

void print_mat(int *a, int n){

    for(int i = 0; i < (n*n); ++i){

        printf("%i  %i \n", n*n, a[i]);

    }

}

void block_mat_mul_par(int *a, int *b, int *c, int n, int bsize){

    // n° block
    int blocks = n / bsize;

    // iter by row
    #pragma omp parallel for
    // #pragma omp parallel for
    for(int i = 0; i < n; i += bsize){

        // iter by colum
        for(int j = 0; j < n; j += bsize){

            // iter by block
            for(int k = 0; k < blocks; ++k){

                // Multiply each min matrix (size: bsize x bsize)
                min_mat_mul(a, b, c, n, bsize, i, j, k);

            }


        }


    }

}

int main(int argc, char *argv[]){

    if(argc != 4){

        printf("./program matrix_size block_size n_threads\n");
        exit(EXIT_FAILURE);

    }

    int n = atoi(argv[1]);

    int bsize = atoi(argv[2]);

    int nt = atoi(argv[3]);

    omp_set_num_threads(nt);

    int *a = (int*)malloc(sizeof(int) * n * n);
    int *b = (int*)malloc(sizeof(int) * n * n);
    int *c = (int*)malloc(sizeof(int) * n * n);
    int *c_block = (int*)malloc(sizeof(int) * n * n);

    init_mat(a, n);
    init_mat(b, n);
    init_mat_val(c, n, 0);
    init_mat_val(c_block, n, 0);

    // printf("Matrix a: \n");
    // print_mat(a, n);

    // printf("Matrix b: \n");
    // print_mat(b, n);

    // printf("Matrix c: \n");
    // print_mat(c, n);

    // mat mul basic
    printf("basic matmul \n");

    float t_aux = omp_get_wtime();

    // mat mul
    mat_mul_seq(a, b, c, n);

    float t1 = omp_get_wtime() - t_aux;

    printf("Time for basic matmul: %f \n", t1);

    printf("result for basic matmul: \n");
    // print_mat(c, n);


    // Block matmul
    printf("block matmul \n");

    t_aux = omp_get_wtime();

    // mat mul block
    // block_matmul(a, b, c_block, n, bsize);
    block_mat_mul(a, b, c_block, n, bsize);

    t1 = omp_get_wtime() - t_aux;

    printf("Time for block matmul: %f \n", t1);

    // printf("result for block matmul: \n");
    // print_mat(c, n);

    // Block matmul paralellized
    printf("block matmul \n");

    t_aux = omp_get_wtime();

    // mat mul block
    // block_matmul(a, b, c_block, n, bsize);
    block_mat_mul_par(a, b, c_block, n, bsize);

    t1 = omp_get_wtime() - t_aux;

    printf("Time for block matmul: %f \n", t1);

    printf("size: %i \n", sizeof(int)*bsize);

    return 0;

}

