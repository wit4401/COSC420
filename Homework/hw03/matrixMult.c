/*
 * Homework_03 (Matrix Multiplication w/ pthreads)
 *
 * This program uses the c pthread library to speed
 * up matrix multiplication in parallell.
*/

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int A[5][5];
int B[5][5];
int result[5][5];

void *threadFunc(void *args){

}

int main(int argc, char *args[]){
    pthread_t thread1,thread2,thread3,thread4,thread5;

    pthread_create(&thread1,NULL,threadFunc,NULL);
    pthread_create(&thread2,NULL,threadFunc,NULL);
    pthread_create(&thread3,NULL,threadFunc,NULL);
    pthread_create(&thread4,NULL,threadFunc,NULL);
    pthread_create(&thread5,NULL,threadFunc,NULL);

    printf("Hello World!\n");
    exit(0);
}