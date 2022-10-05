/*
 * Homework_03 (Matrix Multiplication w/ pthreads)
 *
 * This program uses the pthread library to speed up matrix multiplication
 * of 5 nxn matricies
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

typedef struct Matricies{
    int A[5][5];
    int B[5][5];
    int C[5][5];
    int result[5][5];
    int temp[5][5];
}matMult;

pthread_mutex_t lock;
matMult matricies;

void *threadFunc(void *args){
    sleep(1);
    return NULL;
}

int main(int argc, char *args[]){
    srand(time(NULL));
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            matricies.A[i][j]=rand()%11;
            matricies.B[i][j]=rand()%11;
            matricies.C[i][j]=rand()%11;
            matricies.result[i][j]=matricies.temp[i][j]=0;
        }
    }

    pthread_t *threads = malloc(2*sizeof(pthread_t));

    for(int i=0;i<2;i++){
        pthread_create(&threads[i],NULL,threadFunc,NULL);
        pthread_join(threads[i],NULL);
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            printf("%d ",matricies.temp[i][j]);
        puts("");
    }

    pthread_exit(NULL);
    free(threads);
    exit(0);
}