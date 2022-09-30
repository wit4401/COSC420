/*
 * Serial nxn Matrix Multiplication Program
 * to compare to the assigned parallel
 * version of the program
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char *args[]){
    int n;
    printf("Enter a value n: ");
    scanf("%d ",&n);

    int matA[n][n];
    int matB[n][n];
    int matResult[n][n];
    srand(time(NULL));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            matResult[i][j]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matA[i][j]=rand()%11;
            matB[i][j]=rand()%11;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++)
                matResult[i][j] += matA[i][k]*matB[k][j];
        }
    }
    puts("Matrix A:");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d ",matA[i][j]);
        }
        puts("");
    }
    puts("Matrix B:");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d ",matB[i][j]);
        }
        puts("");
    }
    puts("AxB:");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d ",matResult[i][j]);
        }
        puts("");
    }
    exit(0);
}