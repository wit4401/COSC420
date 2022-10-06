/*
 * Homework_03 (Matrix Multiplication w/ pthreads)
 *
 * This program uses the pthread library to speed up matrix multiplication
 * of m of nxn matricies using m-1 threads
*/
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<time.h>
#include<pthread.h>

/* Note: These values are changed for all outputs in pdf */
#define MATRIX_N 100 /*  size of the matrix  */
#define NUM_MAT 30 /* number of matricies to be multiplied */

// defined struture that will hold all the matrix information
// for easy access by the threading function
typedef struct Matricies{
    long long int matrixArr[NUM_MAT][MATRIX_N][MATRIX_N];// array houses the matricies to be calculated
    long long int result[MATRIX_N][MATRIX_N]; // this will house the results of our calculations and be used in the next calculation
    long long int temp[MATRIX_N][MATRIX_N]; // a temporary matrix to hold the result until we copy it over to the result matrix
}matMult;

sem_t sem; // globally defined semaphore to help us sychronize the threads properly
matMult matricies; //define the matrix stucture globally for easy access in thread function

void *threadFunc(void *args){
    int val = *((int *) args);
    sem_wait(&sem);
    /*  beginning critical section  */
    if(val==1){ // if it is the first thread it will multiply the matricies in matrixArr[0] and matrixArr[1]
        for(int i=0;i<MATRIX_N;i++){
            for(int j=0;j<MATRIX_N;j++){
                for(int k=0;k<MATRIX_N;k++)
                    matricies.result[i][j]=matricies.matrixArr[0][i][k];
            }
        }
    }
    for(int i=0;i<MATRIX_N;i++){
        for(int j=0;j<MATRIX_N;j++){
            for(int k=0;k<MATRIX_N;k++)
                matricies.temp[i][j]+=matricies.result[i][k]*matricies.matrixArr[val][k][j];
        }
    }
    for(int i=0;i<MATRIX_N;i++){
        for(int j=0;j<MATRIX_N;j++){
            matricies.result[i][j]=matricies.temp[i][j];
            matricies.temp[i][j]=0;
        }
    }
    /* end of critical section */
    sem_post(&sem);
    return NULL;
}

int main(int argc, char *args[]){
    clock_t begin,end;
    sem_init(&sem,0,1);
    srand(time(NULL)); // declares seed for our RNG
    
    /* sets up the result and temporary matricies */
    for(int i=0;i<MATRIX_N;i++){
        for(int j=0;j<MATRIX_N;j++){
            matricies.result[i][j]=matricies.temp[i][j]=0;
        }
    }
    /* sets up all the matricies to be multiplied together */
    for(int h=0;h<NUM_MAT;h++){
        for(int i=0;i<MATRIX_N;i++){
            for(int j=0;j<MATRIX_N;j++)
                matricies.matrixArr[h][i][j]=rand()%11;
        }
    }
    
    /* creates an array of threads with NUM_MAT-1 threads */
    pthread_t *threads = malloc((NUM_MAT-1)*sizeof(pthread_t));
    
    begin=clock();
    // loop creates/starts the threads using pthread_create and sychronizes them using pthread_join()
    for(int i=0;i<NUM_MAT-1;i++){
        int threadNum=i+1;
        pthread_create(&threads[i],NULL,threadFunc,(void*)&threadNum);
        pthread_join(threads[i],NULL);
    }
    end=clock();
    printf("Parallel Runtime: %f sec\n",(double)(end-begin)/CLOCKS_PER_SEC);

    sem_destroy(&sem);

    // beginning of the serial program
    begin=clock();
    for(int i=0;i<MATRIX_N;i++){
        for(int j=0;j<MATRIX_N;j++){
            for(int k=0;k<MATRIX_N;k++)
                matricies.result[i][j]=matricies.matrixArr[0][i][k];
        }
    }

    for(int h=1;h<NUM_MAT;h++){
        for(int i=0;i<MATRIX_N;i++){
            for(int j=0;j<MATRIX_N;j++){
                for(int k=0;k<MATRIX_N;k++)
                    matricies.temp[i][j] += matricies.result[i][k]*matricies.matrixArr[h][k][j];
            }
        }
        for(int i=0;i<MATRIX_N;i++){
            for(int j=0;j<MATRIX_N;j++){
                matricies.result[i][j]=matricies.temp[i][j];
                matricies.temp[i][j]=0;
            }
        }
    }
    end=clock();
    printf("Serial Runtime: %f sec\n",(double)(end-begin)/CLOCKS_PER_SEC);

    free(threads); //frees the thread pointer
    exit(0);
}