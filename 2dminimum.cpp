#include <stdio.h>
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //int rows = 0, cols = 0, min = 0, value = 0, n;
    int rows = 0, cols = 0,  value = 0, n;
    
    bool done = false;
    //int done = 0, numprocs, rank, i, j;
    int numprocs, rank, i, j;
    srand(time(NULL));
    double startwtime = 0.0, endwtime;
    int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);
    while (!done) {
        printf("rank = %d\n", rank);
        if (rank == 0) {
            printf("Enter the height/width of the matrix\n");
            scanf_s("%d", &rows);
            scanf_s("%d", &cols);
            startwtime = MPI_Wtime();
        }
        int min;
        if (rows == 0 || cols == 0) {
            done = true;
        }
        else {
            int** arr = (int**)malloc(rows * sizeof(int*));    //creating 2d array
            for (i = 0; i < rows; i++) {
                arr[i] = (int*)malloc(cols * sizeof(int));
            }
            for (i = 0; i < rows; i++) {         //Array filling
                for (j = 0; j < cols; j++) {
                    arr[i][j] = rand();
                }
            }
            for (i = 0; i < rows; i++) {      // output of the array to the screen for clarity
                for (j = 0; j < cols; j++) {
                    printf("%d\t", arr[i][j]);
                }
                printf("\n");
            }
            MPI_Scatter(&arr[0][0], rows * cols / numprocs, MPI_INT, &arr[rows][cols], rows * cols / numprocs, MPI_INT, 0, MPI_COMM_WORLD);
            min = 0;
            for (i = 0; i < cols; i++) {
                for (j = 0; j < rows; j++) {
                    if (min > arr[j][i]) { min = arr[j][i]; }
                }
            }
            MPI_Reduce(&min, &value, rows * cols / numprocs, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

            /*min = arr[0][0];
            for (i = 0; i < rows; i++) {                              //find min value
                for (j = 0; j < cols; j++) {                          //
                    if (min > arr[i][j]) { min = arr[i][j]; }         //need to parallize
                }
            }*/
            printf("numprocs = %d\n", numprocs);
            
            if (rank == 0) {
                endwtime = MPI_Wtime();
                printf("min = %d\n", min);
                printf("wall clock time = %f\n", endwtime - startwtime);
                fflush(stdout);
                for (i = 0; i < rows; i++) {
                    free(arr[i]);
                }
                free(arr);
            }
        }
    }
    MPI_Finalize();
    return 0;
}