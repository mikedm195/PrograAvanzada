#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <time.h>

#define numEnanitos 9

sem_t sillas;
pthread_mutex_t blanca;
int hayEnanitos;
int acabo = 0;
int comida = 0;

void atiendeEnanito(){
    while(hayEnanitos == 0){
        pthread_mutex_lock(&blanca);
        printf("Blancanieves se fue porque no hay enanitos pendientes por servir\n");
        sleep(5);
        if(acabo == 1) break;
        printf("Llego Blancanieves\n");
        pthread_mutex_unlock(&blanca);
    }
    while(hayEnanitos > 0){
        printf("Ya esta servido, puedes empezar a comer\n");
        comida++;
        sleep(1);
        hayEnanitos--;
    }
}

void blancan(){
    while(acabo == 0){
        atiendeEnanito();
    }
}

void enano(void * p){
    int id = (int)p;
    sem_wait(&sillas);
    printf("Ya me sente (enano %d)\n",id);
    hayEnanitos++;
    
    pthread_mutex_lock(&blanca);
    
    while(comida==0);
    printf("Voy a empezar a comer (enano %d)\n",id);
    comida --;

    pthread_mutex_unlock(&blanca);
    
    sleep(rand()%10);

    printf("Ya acabe de comer (enano %d)\n",id);

    sem_post(&sillas);

}

int main(){
    
    srand(time(NULL));

    sem_init(&sillas,0,4);
    
    pthread_t Blancanieves;
    pthread_t * Enanito = (pthread_t *)malloc(numEnanitos*sizeof(pthread_t));
    pthread_t * aux;

    pthread_create(&Blancanieves,NULL,blancan,NULL);

    aux = Enanito;

    for(;aux<(Enanito+numEnanitos);aux++){
        sleep((rand()%5));
        printf("Llego enanito %d\n",(aux-Enanito));
        pthread_create(aux,NULL,enano,(void*)(aux-Enanito));
    }

    for(aux=Enanito;aux<(Enanito+numEnanitos);aux++){
        pthread_join(*aux,NULL);
    }
    acabo = 1;
    pthread_join(Blancanieves,NULL);
    free(Enanito);
    return 0;
}
