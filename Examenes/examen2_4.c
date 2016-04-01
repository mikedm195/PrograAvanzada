#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <time.h>

#define C 10
#define S 3
#define T 3
#define U 5
#define P 100

typedef struct Complejos{
    pthread_mutex_t salas[S]; 
    sem_t taquillas;
    int asientos[S];
}complejos;

complejos comp[C];    
int fila[P];
int indice=0;

void atiendePersona(void*p){
    int atendido = 0;
    int id = (int)p;
    int compAct = rand()%C;
    int registro = 0;
    printf("Cliente %d llego al complejo %d\n",id,compAct);
    sem_wait(&((comp[compAct]).taquillas));
    printf("Cliente %d esta siendo atendido en el complejo %d\n",id,compAct);
    sleep((rand()%2)+1);
    int i = 0;
    for(;i<S;i++){
        pthread_mutex_lock(&((comp[compAct]).salas[i]));
        if(comp[compAct].asientos[i]<U && atendido == 0){
            printf("Cliente %d reservo en sala %d en el complejo %d\n",id,i,compAct);
            comp[compAct].asientos[i]++;
            atendido = 1;
        }
        pthread_mutex_unlock(&((comp[compAct]).salas[i]));
    }
    sem_post(&((comp[compAct]).taquillas));

}

int main(){

    srand(time(NULL));

    pthread_t * personas = (pthread_t*)malloc(P*sizeof(pthread_t));
    pthread_t * aux;
    
    int i = 0;
    for(;i<C;i++){
        sem_init(&((comp[i]).taquillas),0,S);
    }

    for(aux = personas;aux<(personas+P);aux++){ 
        
        pthread_create(aux,NULL,atiendePersona,(void*)(aux-personas));
    }

    i=0; 
    for(;i<C;i++){
        sem_destroy(&((comp[i]).taquillas));
    }

    for(aux = personas;aux<(personas+P);aux++){ 
        pthread_join(*aux,NULL);
    }
    free(personas);

    return 0;
}
