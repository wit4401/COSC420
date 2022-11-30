#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 10000
#define GRID 10

__global__ void matrix_addition(int *a,int *b, int *res,int n){
    int i = threadIdx.x+(blockDim.x*blockIdx.x);
    if (i<n)
        res[i] = a[i]+b[i];
}

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
    int len=sqrt(SIZE);
    srand(time(NULL));

    cudaMallocManaged(&matA,SIZE*sizeof(int));
    cudaMallocManaged(&matB,SIZE*sizeof(int));
    cudaMallocManaged(&result,SIZE*sizeof(int));

    for(int i=0;i<SIZE;i++){
        matA[i]=rand()%101;
        matB[i]=rand()%101;
    }

    dim3 grid_size(GRID);
    dim3 block_size(SIZE/GRID);

    matrix_addition<<<grid_size,block_size>>>(matA,matB,result,SIZE);
    cudaDeviceSynchronize();

    printMatrix(matA,len);
    puts("\nPlus");
    printMatrix(matB,len);
    puts("\nEquals");
    printMatrix(result,len);
    puts("");

    cudaFree(matA);
    cudaFree(matB);
    cudaFree(result);
    
    exit(0);
}
