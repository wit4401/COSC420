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

int main(int argc, char *args[]){
    int rows1,columns1,rows2,columns2;
    printf("Enter # of rows (Matrix 1): ");
    scanf("%d",&rows1);
    printf("Enter # of columns (Matrix 1): ");
    scanf("%d",&columns1);

    puts("");

    printf("Enter # of rows (Matrix 2): ");
    scanf("%d",&rows2);
    printf("Enter # of columns (Matrix 2): ");
    scanf("%d",&columns2);

    if(rows2!=columns1){
	    puts("Cannot Multipy with given values.");
	    exit(1);
    }

    int matA[rows1][columns1];
    int matB[rows2][columns2];
    int matResult[rows1][columns2];
    srand(time(NULL));

    for(int i=0;i<rows1;i++){
        for(int j=0;j<columns2;j++)
            matResult[i][j]=0;
    }
    for(int i=0;i<rows1;i++){
        for(int j=0;j<columns1;j++)
            matA[i][j]=rand()%11;
    }

    for(int i=0;i<rows2;i++){
        for(int j=0;j<columns2;j++)
            matB[i][j]=rand()%11;
    }

    for(int i=0;i<rows1;i++){
        for(int j=0;j<columns2;j++){
            for(int k=0;k<columns1;k++)
                matResult[i][j] += matA[i][k]*matB[k][j];
        }
    }

    puts("\nMatrix A:");
    for(int i=0;i<rows1;i++){
        for(int j=0;j<columns1;j++){
            printf("%d ",matA[i][j]);
        }
        puts("");
    }
    puts("\nMatrix B:");
    for(int i=0;i<rows2;i++){
        for(int j=0;j<columns2;j++){
            printf("%d ",matB[i][j]);
        }
        puts("");
    }
    puts("\nAxB:");
    for(int i=0;i<rows1;i++){
        for(int j=0;j<columns2;j++){
            printf("%d ",matResult[i][j]);
        }
        puts("");
    }
    exit(0);
}
