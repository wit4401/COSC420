/*
 * Homework_03 (Matrix Multiplication w/ pthreads)
 *
 * This program uses the pthread library to speed up matrix multiplication
 * of 5 nxn matricies
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

void *threadFunc(void *args){
    
}

int main(int argc, char *args[]){
    int n;
    puts("How big will your nxn matrix be?");
    printf("n = ");
    scanf("%d",n);
    
    int A[n][n];
    int B[n][n];
    int C[n][n];
    int D[n][n];
    int E[n][n];
    int result[n][n];
    srand(time(NULL));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i][j]=rand()%11;
            B[i][j]=rand()%11;
            C[i][j]=rand()%11;
            D[i][j]=rand()%11;
            E[i][j]=rand()%11;
            result[i][j]=0;
        }
    }

    pthread_t *threads = malloc(4*sizeof(pthread_t));

    for(int i=0;i<5;i++){
        pthread_create(&threads[i],NULL,threadFunc,(void*));
        pthread_join(threads[i],NULL);
        pthread_exit();
    }

    exit(0);
}