#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	// Initialize MPI environment
	// Contruct a communicator
	//Assign rank to each process*/
	MPI_Init(NULL, NULL);

	// Get number of process
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
    int rank;
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   	// Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

	/*printf("Hello world from processor %s !\n", processor_name);*/

	if(rank == 0){

		int data = -1;

		printf("Sending data %i from master\n", data);

		MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

	}

	else if(rank == 1){

		printf("From slave process\n");

		int data;

		MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Receive data %i from master to process %i\n", data, rank);

	}
	// Finalize the MPI environment
	MPI_Finalize();

	return 0;


}