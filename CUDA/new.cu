#include <stdio.h>

// kernel
__global__
void add_vectors(int *c, int *a, int *b, int n){

    // printf("Add vectors function\n");

    // printf("n value: %i \n", n);

    int index = threadIdx.x;

    int stride = blockDim.x;

    // int index = blockIdx.x * blockDim.x + threadIdx.x;
    
    // int stride = blockDim.x * gridDim.x;

    // printf("%i \n", index);

    for(int i = index; i < n; i += stride){

        // printf("thead %i working with index: %i \n", index, i);

        c[i] = a[i] + b[i];

    }

}

int main(int argc, char *argv[]){

    // Define
    // int *a;
    // int *b;
    // int n = 1000000;
    int n = atoi(argv[1]);
    int nt = atoi(argv[2]);

    int blocks = n/nt;

    printf("blocks: %i \n", blocks);
    printf("works: %i\n", n);
    printf("threads: %i \n", nt);

    // Define and assign vector to dynamic memory
    int *a = (int *) malloc(sizeof(int)*n);
    int *b = (int *) malloc(sizeof(int)*n);
    int *c = (int *) malloc(sizeof(int)*n);

    // Pointers for device memory
    int *d_a;
    int *d_b;
    int *d_c;

    // Assign in device memory
    cudaMalloc((void**)&d_a, sizeof(int) * n);
    cudaMalloc((void**)&d_b, sizeof(int) * n);
    cudaMalloc((void**)&d_c, sizeof(int) * n);

    // init value
    for(int i = 0; i < n; ++i){

        a[i] = 1;
        b[i] = 2;

    }

    // Transfer memory from host to device
    cudaMemcpy(d_a, a, sizeof(int) * n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(int) * n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, sizeof(int) * n, cudaMemcpyHostToDevice);

    // CPU call
    // add_vectors(c, a, b, n);

    // n = 10000
    // 256 t: 1,1797 ms
    // 1 t: 1,1688 ms

    // n = 1.000.000
    // 1 t: 124,12 ms
    // 256 t: 125,34 ms

    // GPU call: Launch kernel
    add_vectors<<<blocks,nt>>>(d_c, d_a, d_b, n);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    // Transfer data back to host memory
    cudaMemcpy(c, d_c, sizeof(int) * n, cudaMemcpyDeviceToHost);

    // for(int i = 0; i < n; ++i){

    //     printf("%i \n", c[i]);

    // }

    cudaFree(a);
    cudaFree(b);
    cudaFree(c);

    free(a);
    free(b);
    free(c);

    return 0;

}

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <assert.h>
// // #include <cuda.h>
// // #include <cuda_runtime.h>

// #define N 10000000
// #define MAX_ERR 1e-6

// __global__ 
// void vector_add(float *out, float *a, float *b, int n) {

//     printf("running in GPU \n" );

//     for(int i = 0; i < n; i ++){
//         out[i] = a[i] + b[i];
//     }
// }

// int main(){
//     float *a, *b, *out;
//     float *d_a, *d_b, *d_out; 

//     // Allocate host memory
//     a   = (float*)malloc(sizeof(float) * N);
//     b   = (float*)malloc(sizeof(float) * N);
//     out = (float*)malloc(sizeof(float) * N);

//     // Initialize host arrays
//     for(int i = 0; i < N; i++){
//         a[i] = 1.0f;
//         b[i] = 2.0f;
//     }

//     // Allocate device memory
//     cudaMalloc((void**)&d_a, sizeof(float) * N);
//     cudaMalloc((void**)&d_b, sizeof(float) * N);
//     cudaMalloc((void**)&d_out, sizeof(float) * N);

//     // Transfer data from host to device memory
//     cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
//     cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);

//     // Executing kernel 
//     vector_add<<<1,10>>>(d_out, d_a, d_b, N);
    
//     // Transfer data back to host memory
//     cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

//     // Verification
//     for(int i = 0; i < N; i++){
//         assert(fabs(out[i] - a[i] - b[i]) < MAX_ERR);
//     }
//     printf("out[0] = %f\n", out[0]);
//     printf("PASSED\n");

//     // Deallocate device memory
//     cudaFree(d_a);
//     cudaFree(d_b);
//     cudaFree(d_out);

//     // Deallocate host memory
//     free(a); 
//     free(b); 
//     free(out);
// }