#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 10000 /* Size of arrays (Size of matrix: "sqrt(SIZE) x sqrt(SIZE)" */
#define GRID 10 /* Size of the grid (i.e. dimensions "Grid x Grid x Grid") */

/* Our kernel, i.e. the instructions for each thread in this case adding together numbers in the same spot */
__global__ void matrix_addition(int *a,int *b, int *res,int n){
    int i = threadIdx.x+(blockDim.x*blockIdx.x);
    if (i<n)
        res[i] = a[i]+b[i];
}

/* Prints out the given matrix */
void printMatrix(int *mat, int len_row){
    int multiple=1;
    for (int i=0;i<SIZE;i++){
        if(i == (multiple*len_row)-1){
            printf("%d\n",mat[i]);
            multiple++;
        }
        else
            printf("%d ",mat[i]);
    }
}

int main(int argc, char **argv){
    int *matA,*matB,*result;
    int len=sqrt(SIZE);/* length of each row/column */
    srand(time(NULL));
    
    //allocate appropriate memory to each dynamic array
    cudaMallocManaged(&matA,SIZE*sizeof(int));
    cudaMallocManaged(&matB,SIZE*sizeof(int));
    cudaMallocManaged(&result,SIZE*sizeof(int));

    // assigns random number to each index of the dynamic arrays to be added
    for(int i=0;i<SIZE;i++){
        matA[i]=rand()%101;
        matB[i]=rand()%101;
    }

    dim3 grid_size(GRID); //stores our grid dimensions
    dim3 block_size(SIZE/GRID);//stores our block dimensions

    //call the kernel with the appropriate grid and block dimensions
    matrix_addition<<<grid_size,block_size>>>(matA,matB,result,SIZE);
    cudaDeviceSynchronize();

    //print out results from computation
    printMatrix(matA,len);
    puts("\nPlus");
    printMatrix(matB,len);
    puts("\nEquals");
    printMatrix(result,len);
    puts("");

    //clean up memory
    cudaFree(matA);
    cudaFree(matB);
    cudaFree(result);
    
    exit(0);
}
