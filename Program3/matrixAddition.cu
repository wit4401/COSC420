#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 1024

__global__ void matrix_addition(int *a,int *b, int *res){

}

int main(int argc, char **argv){
    int *matA,*matB,*result;

    cudaMalloc(&matA,sizeof(int)*SIZE);
    cudaMalloc(&matB,sizeof(int)*SIZE);
    cudaMalloc(&result,sizeof(int)*SIZE);

    matrix_addition<<<1,1>>>(matA,matB,result);

    cudaFree(matA);
    cudaFree(matB);
    cudaFree(result);
    
    return 0;
}