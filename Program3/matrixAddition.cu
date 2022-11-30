#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 2500

__global__ void matrix_addition(int *a,int *b, int *res,int n){
    int i = threadIdx.x;
    if (i<n)
        res = a[i]+b[i]
    
}

int main(int argc, char **argv){
    int *matA,*matB,*result;
    srand(time(NULL));

    cudaMalloc(&matA,sizeof(int)*SIZE);
    cudaMalloc(&matB,sizeof(int)*SIZE);
    cudaMalloc(&result,sizeof(int)*SIZE);

    for(int i=0;i<SIZE;i++){
        matA[i]=rand()%101;
        matB[i]=rand()%101;
        result[i]=0;
    }

    matrix_addition<<<1,1>>>(matA,matB,result);

    cudaFree(matA);
    cudaFree(matB);
    cudaFree(result);
    
    return 0;
}