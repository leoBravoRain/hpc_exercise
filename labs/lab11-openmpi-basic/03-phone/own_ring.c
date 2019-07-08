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

	// Send message to first slave
	if(rank == 0){

		int data = 0;

		printf("Sending data from master: %i\n", data);

		// send data to first slave
		MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

		// Receive data from last slave
		MPI_Recv(&data, 1, MPI_INT, (world_size - 1) , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Received data in master process from slave: %i\n", data);

	}

	// If it's a slave
	else{

		// Declare variable
		int data;

		// Receive data from previus process
		MPI_Recv(&data, 1, MPI_INT, (rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		/*printf("Receive data from master to process %i: %i\n", rank, data);*/

		// Update data
		data += 1;

		printf("Sendig data to next process from process %i: %i\n", rank, data);

		// send data to next process
		MPI_Send(&data, 1, MPI_INT, (rank + 1) % world_size, 0, MPI_COMM_WORLD);

	}
	// Finalize the MPI environment
	MPI_Finalize();

	return 0;


}