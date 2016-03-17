#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#define N 150

sem_t semGen;
sem_t semEmp;

int main(){
 
    pthread_t hilo1;
    
    sem_init(&semGen,0,5);
    sem_init(&semEmp,0,3);

    pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));


    sem_destroy(&semGen);
    sem_destroy(&semEmp);
    free(threads);

    return 0;
}
