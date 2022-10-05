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

struct Matricies{
    int A[5][5];
    int B[5][5];
    int C[5][5];
    int result[5][5];
    int temp[5][5];
};

void *threadFunc(void *args){
    Matricies my_struct = *((Matricies*) args);
    if(isZeroMat(my_struct.result)){
        for(int i=0;i<5;i++){
            for(int n=0;j<5;j++)

        }
    }
    else{
        for(int i=0;i<5;i++){
            for(int n=0;j<5;j++)

        }
    }
    return NULL;
}

int isZeroMat(Matricies mat_struct){
    int ret;
    for(int i=0;i<5;i++){
        for(int n=0;j<5;j++){
            if(mat_struct[i][j]!=0)
                ret=0;
        }
    }
    if(ret='\0')
        ret=1;

    return ret;
}

int main(int argc, char *args[]){
    Matricies matMult;
    srand(time(NULL));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matMult.A[i][j]=rand()%11;
            matMult.B[i][j]=rand()%11;
            matMult.C[i][j]=rand()%11;
            matMult.result[i][j]=0;
        }
    }

    pthread_t *threads = malloc(2*sizeof(pthread_t));

    for(int i=0;i<2;i++){
        pthread_create(&threads[i],NULL,threadFunc,(void*)&matMult);
        pthread_join(threads[i],NULL);
    }

    pthread_exit(NULL);
    free(threads);
    exit(0);
}