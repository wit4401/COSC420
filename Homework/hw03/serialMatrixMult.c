#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *args[]){
    int A[2][2] = {1, 2, 
                   3, 4};

    int B[2][2] = {1, 2,
                   3, 4};
    
    int result[2][2]={0,0,
                      0,0};
                      
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++)
                result[i][j] += A[i][k]*B[k][j];
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d ",result[i][j]);
        }
        puts("");
    }
    exit(0);
}
