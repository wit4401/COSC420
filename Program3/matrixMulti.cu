/*
 Assuming each matrix is nxn we can construct a program using
 CUDA to implement matrix multiplication
*/
#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 10000 /* Size of arrays (Size of matrix: "sqrt(SIZE) x sqrt(SIZE)" */
#define GRID 10 /* Size of the grid (i.e. dimensions "Grid x Grid x Grid") */

__global__ void matrix_multiply(int *a,int *b, int *res, int n){
    int row = blockIdx.y*blockDim.y+threadIdx.y;
    int col = blockIdx.x*blockDim.x+threadIdx.x;
    if(row<n&&col<n){
        int temp = 0;
        for(int i=0;i<n;i++)
            temp+=a[row*n+i]*b[i*n+col];
        res[row*n+col]=temp;
    }
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
    cudaMalloc(&matA,sizeof(int)*SIZE);
    cudaMalloc(&matB,sizeof(int)*SIZE);
    cudaMalloc(&result,sizeof(int)*SIZE);

    // assigns random number to each index of the dynamic arrays to be added
    for(int i=0;i<SIZE;i++){
        matA[i]=rand()%11;
        matB[i]=rand()%11;
    }

    dim3 grid_size(GRID); //stores our grid dimensions
    dim3 block_size(SIZE/GRID);//stores our block dimensions

    //call the kernel with the appropriate grid and block dimensions
    matrix_multiply<<<grid_size,block_size>>>(matA,matB,result,SIZE);
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
    
    return 0;
}