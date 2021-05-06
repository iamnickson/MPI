#include "mpi.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Print the message
    printf("Hello World! I am %d of %d\n", rank, size);
    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}