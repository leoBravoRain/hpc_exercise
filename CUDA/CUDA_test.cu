#include <stdio.h>

void print_matrix(int *s, int N){

  for(int i = 0; i < N; ++i){

    printf("%i | ", s[i]);

  }

}

void init_matrix(int *m, int val, int N){

  for(int i = 0; i < N; ++i){

    m[i] = val;

  }

}

// kernel for run in GPU
// This is a device code beacuse run in GPU
__global__
void saxpy_CUDA(int *s, int a, int *x, int *y, int N){

  for( int i = 0; i < N; ++i){

    s[i] = a*x[i] + y[i];

  }

}

// This is host code because it runs on CPU
int main(int argc, char *argv[]){

  // printf("%i \n", 10);
  if(argc != 2){

    printf("compile must be: \n ./program_name N \n");
  }

  int N = atoi(argv[1]);

  int a = 2;
  // int *s = new int[N];
  // int *x = new int[N];
  // int *y = new int[N];

  int *s, *x, *y;

  // Allocate Unified Memory
  // It's accesible from GPU and CPU
  cudaMallocManaged(&s, N*sizeof(int));
  cudaMallocManaged(&x, N*sizeof(int));
  cudaMallocManaged(&y, N*sizeof(int));

  // Init matrix
  init_matrix(s, 0, N);
  init_matrix(x, 1, N);
  init_matrix(y, 0, N);

  // printf("%i \n", z);

  // saxpy function
  // s = a * x + y
  // saxpy_CUDA(s, a, x, y, N);

  // Launch saxpy_CUDA to kernel for run in GPU
  saxpy_CUDA<<<1,1>>>(s, a, x, y, N)  ;

  // Wait for GPU to finish before accesing on host
  cudaDeviceSynchronize();
  
  print_matrix(s, N);

  // Free memory
  cudaFree(s);
  cudaFree(x);
  cudaFree(y);

  return 0;

}

// #include <iostream>
// #include <math.h>
// #include <typeinfo>

// using namespace std;

// // Kernel function to add the elements of two arrays
// __global__
// void add(int n, float *x, float *y)
// {
//   for (int i = 0; i < n; i++)
//     y[i] = x[i] + y[i];
// }

// int main(void)
// {

//   // int N = 1<<20;
//   int N = 20;

//   // printf("%i \n", N);

//   // float *x, *y;
//   int *x, *y;


//   // Allocate Unified Memory – accessible from CPU or GPU
//   cudaMallocManaged(&x, N*sizeof(float));
//   cudaMallocManaged(&y, N*sizeof(float));

//   // initialize x and y arrays on the host
//   for (int i = 0; i < N; i++) {
//     x[i] = 1.0f;
//     y[i] = 2.0f;
//   }

//   // Run kernel on 1M elements on the GPU
//   add<<<1, 1>>>(N, x, y);

//   // Wait for GPU to finish before accessing on host
//   cudaDeviceSynchronize();

//   // Check for errors (all values should be 3.0f)
//   float maxError = 0.0f;
//   for (int i = 0; i < N; i++)
//     maxError = fmax(maxError, fabs(y[i]-3.0f));
//   std::cout << "Max error: " << maxError << std::endl;

//   // Free memory
//   cudaFree(x);
//   cudaFree(y);
  
//   return 0;
// }