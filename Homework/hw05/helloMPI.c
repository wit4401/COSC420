#include<stdio.h>
#include<stdlib.h>
#include <mpi.h>

int main(int argc,char **argv){
    int rank;//place holder for the processor #

    MPI_Init(NULL,NULL); // initializes the processors
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); // retrieves the rank of the current process
    printf("Hello World from Processor %d\n",rank); // each processor prints out basic message
    MPI_Finalize(); // stops/merges processors back to main CPU
    exit(0);
}