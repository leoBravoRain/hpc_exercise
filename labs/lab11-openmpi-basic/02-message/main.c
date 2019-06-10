#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void llenar_matrix(int *a, int n){

    for(int i = 0; i < n*n; ++i){

        a[i] = i;

    }

}


void print_matrix(int *a, int n){

    for(int i = 0; i < n; ++i){

        for(int j = 0; j < n; ++j){

            printf("%i ", a[i*n + j]);

        }

        printf("\n");

    }

}

int main(int argc, char** argv) {
    
    if(argc != 2){

        printf("run as mpicc ./prog n \n");
        // exit(EXIT_FAILURE);

    }

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    int name_len;

    MPI_Get_processor_name(processor_name, &name_len);

    // (1) pasar una matriz de nxn de 1 a 0

    // El 1 la llena
    if(world_rank == 0){

        // Get n matrix size
        int n = atoi(argv[1]);

        // master create matrix
        int *mat = (int*)malloc(sizeof(int)*n*n);

        // a) master send n
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // master send matrix to slave
        MPI_Send(mat, n*n, MPI_INT, 1, 1, MPI_COMM_WORLD);

        // Master wait matrix with values
        MPI_Recv(mat, n*n, MPI_INT, 1, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("printing matrix from process: %i\n", world_rank);

        print_matrix(mat, n);

        // print

    }

    // Slaves
    else{

        int n = -1;

        // recibir el n
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // printf("%i\n", n);

        int *slavemat = (int*)malloc(sizeof(int)*n*n);

        // Receive matrix
        MPI_Recv(slavemat, n*n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("fill matrix from process: %i\n", world_rank);

        llenar_matrix(slavemat, n);

        MPI_Send(slavemat, n*n, MPI_INT, 0, 5, MPI_COMM_WORLD);

    }

    // Print off a hello world message
    // printf("Hello world from processor %s, rank %d out of %d processors\n",
           // processor_name, world_rank, world_size);

    // printf("hi leo\n");
    
    // Finalize the MPI environment.
    MPI_Finalize();
}

