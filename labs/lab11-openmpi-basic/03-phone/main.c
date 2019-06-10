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

        printf("run as mpicc ./prog np \n");
        // exit(EXIT_FAILURE);

    }

    // Get np
    int np = atoi(argv[1]);

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    int name_len;

    MPI_Get_processor_name(processor_name, &name_len);

    // (1) pasar una matriz de nxn de 1 a 0

    // int *msg [np];
    // int msg;

    // El 1 la llena
    if(rank == 0){

        // copy string to msg
        // strcpy(msg, 'a');
        // msg[rank] = 0;
        int msg = 0;

        MPI_Send(msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(msg, 1, MPI_INT, np-2, MPI_COMM_WORLD);

        printf("message: %i\n", msg);

    }

    else{

        int msg;

        MPI_Recv(msg, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // MPI_Recv(slavemat, n*n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        msg += 1;

        MPI_Send(msg, 1, MPI_INT, (rank + 1) % world_size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    }
    
    // Finalize the MPI environment.
    MPI_Finalize();

}

