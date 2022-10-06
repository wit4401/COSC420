/*
 * Serial Matrix Multiplication Program
 *
 * Multiplies two random mxn matricies with the bounds of the matrix determined by the
 * user. Each elemnet is a random number b/n 0 and 10
 *
 * Note: This is a Homework 3 extension to help me recall how to program matrix multiplication.
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define NUM 10
#define NUM_MAT 10

// defined struture that will hold all the matrix information
// for easy access by the threading function
typedef struct Matricies{
    long long int matrixArr[NUM_MAT][NUM][NUM];// array houses the matricies to be calculated
    long long int result[NUM][NUM]; // this will house the results of our calculations and be used in the next calculation
    long long int temp[NUM][NUM]; // a temporary matrix to hold the result until we copy it over to the result matrix
}matMult;

int main(int argc, char *args[]){
    clock_t begin,end;
    begin=clock();
    srand(time(NULL));
    matMult mat_struct;
    for(int i=0;i<NUM;i++){
        for(int j=0;j<NUM;j++)
            mat_struct.result[i][j]=mat_struct.temp[i][j]=0;
    }
    for(int h=0;h<NUM_MAT;h++){
        for(int i=0;i<NUM;i++){
            for(int j=0;j<NUM;j++)
                mat_struct.matrixArr[h][i][j]=rand()%11;
        }
    }

    for(int i=0;i<NUM;i++){
        for(int j=0;j<NUM;j++){
            for(int k=0;k<NUM;k++)
                mat_struct.result[i][j] += mat_struct.matrixArr[0][i][k]*mat_struct.matrixArr[1][k][j];
        }
    }

    for(int h=2;h<NUM_MAT;h++){
        for(int i=0;i<NUM;i++){
            for(int j=0;j<NUM;j++){
                for(int k=0;k<NUM;k++)
                    mat_struct.temp[i][j] += mat_struct.result[i][k]*mat_struct.matrixArr[h][k][j];
            }
        }
        for(int i=0;i<NUM;i++){
            for(int j=0;j<NUM;j++){
                mat_struct.result[i][j]=mat_struct.temp[i][j];
                mat_struct.temp[i][j]=0;
            }
        }
    }

    for(int h=0;h<NUM_MAT;h++){
        printf("Matrix %d:\n",h+1);
        for(int i=0;i<NUM;i++){
            for(int j=0;j<NUM;j++)
                printf("%lld ",mat_struct.matrixArr[h][i][j]);
            puts("");
        }
        puts("");
    }

    puts("Resulting Matrix:");
    for(int i=0;i<NUM;i++){
        for(int j=0;j<NUM;j++)
            printf("%lld ",mat_struct.result[i][j]);
        puts("");
    }
    puts("");
    end=clock();

    printf("%f sec\n",(double)(end-begin)/CLOCKS_PER_SEC);
    exit(0);
}
