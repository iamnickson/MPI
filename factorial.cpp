#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv)
{
	int rank, process, i, n, quotient, j, mod;
	int factorial, result = 1;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &process);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		printf("Enter the number to find its factorial: ");
		scanf_s("%d", &n);
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	quotient = n / process;
	mod = n % process;
	for (i = rank * quotient + 1;i <= rank * quotient + quotient;i++)
	{
		result = result * i;
	}
	if (mod != 0)
	{
		if (rank == process - 1)
		{
			for (j = i;j <= (rank + 1) * quotient + mod;j++)
			{
				result = result * j;
			}
		}
	}
	MPI_Reduce(&result, &factorial, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("\n%d! = %d ", n, factorial);
	}
	MPI_Finalize();
	return 0;
}