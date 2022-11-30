#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>
#define SIZE 25

__global__ void matrix_addition(int *a,int *b, int *res,int n){
    int i = threadIdx.x;
    if (i<n)
        res[i] = a[i]+b[i];
}

void printMatrix(int *mat, int len_row){
    int multiple=1;
    for (int i=0;i<SIZE;i++){
        if(i == (multiple*len_row)){
            printf("%d\n",mat[i]);
            multiple++;
        }
        else
            printf("%d ",mat[i]);
    }
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

    matrix_addition<<<1,1>>>(matA,matB,result,SIZE);
    cudaDeviceSynchronize();

    len=sqrt(SIZE);
    printMatrix(matA,SIZE,len);
    puts("Plus");
    printMatrix(matB,SIZE,len);
    puts("Equals");
    printMatrix(result,SIZE,len);

    cudaFree(matA);
    cudaFree(matB);
    cudaFree(result);
    
    exit(0);
}