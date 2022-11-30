/*
 Assuming each matrix is nxn we can construct a program using
 CUDA to implement matrix multiplication
*/
#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 1024

__global__ void matrix_multiply(int *a,int *b, int *res){

}

int main(int argc, char **argv){
    int matA*,matB*,result;

    cudaMalloc(&matA,sizeof(int)*SIZE);
    cudaMalloc(&matB,sizeof(int)*SIZE);

    matrix_multiply<<<1,1>>>(matA,matB,result);
    

    return 0;
}