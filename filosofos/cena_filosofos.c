#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

sem_t sillas;
sem_t tenedores;
sem_t cuchillos;

void* comer(void* p) {
    int id = (int) p;
    
    sem_wait(&sillas);
    printf("->Ya estoy sentado %d\n", id);
    
    sem_wait(&tenedores);
    printf("Ya tengo un tenedor %d\n", id);
   
    sem_wait(&cuchillos);
    printf("Ya tengo un cuchillo %d\n Filosofo %d esta comiendo\n", id, id);
    
    sleep((rand() % 5) + 5);
    
    printf("<-Acabé de comer %d\n", id);

    sem_post(&cuchillos);
    sem_post(&tenedores);
    sem_post(&sillas);	
}
int main() {
    srand((int) time(NULL));
    
    sem_init(&sillas, 0, 4);
    sem_init(&tenedores, 0, 3);
    sem_init(&cuchillos, 0, 3);

    pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));
    pthread_t* aux;

    for (aux = threads; aux < (threads + N); aux++) {
	pthread_create(aux, NULL, comer, (void*)(aux-threads));
    }

    for (aux = threads; aux < (threads + N); aux++) {
	pthread_join(*aux, NULL);
    }

    sem_destroy(&sillas);
    sem_destroy(&tenedores);
    sem_destroy(&cuchillos);
    free(threads);
    return 0;
}


