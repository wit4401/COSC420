/*
 * Homework_03 (Matrix Multiplication w/ pthreads)
 *
 * This program uses the c pthread library to speed
 * up matrix multiplication in parallell.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

void *threadFunc(void *args){

}

int main(int argc, char *args[]){
    int numOfMat;
    srand(time(NULL));

    pthread_t *threads = malloc(sizeof(pthread_t));

    for(int i=0;i<5;i++){
        pthread_create(threads[i],NULL,threadFunc,NULL);
        pthread_join(threads[i],NULL);
    }

    exit(0);
}