#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define G 100
#define E 50

pthread_mutex_t * Gen;
pthread_mutex_t * Emp;
int numGen[G];
int numEmp[E];

void * operaG(void*p){
    int id = (int)p;
    int t = ((rand() % 5)+5);
    
    int lock = -1;
    while(lock){
        int i = 0;
        for(;i<5;i++){
            if(pthread_mutex_trylock((Gen+i))==0){
                printf("cliente general %d\tcajero general %d\t%d segundos\n", id, i, t);
                sleep(t);
                if(++numGen[i]==5){
                    printf("Soy el cajero general %d voy a descansar\n",i);
                    sleep(5);
                    numGen[i]=0;
                }
                pthread_mutex_unlock((Gen+i));
                lock = 0;
                break;
            }
        }
        i=0;
        if(lock){
            for(;i<3;i++){
                if(pthread_mutex_trylock((Emp+i))==0){
                    printf("cliente general %d\tcajero empresarial %d\t%d segundos\n", id, i, t);
                    sleep(t);
                    if(++numEmp[i]==5){
                        printf("Soy el cajero empresarial %d voy a descansar\n",i);
                        sleep(5);
                        numEmp[i]=0;
                    }
                    pthread_mutex_unlock((Emp+i));
                    lock = 0;
                    break;
                }
            }
        }
    }
}

void * operaE(void*p){
    int id = (int)p;
    int t = ((rand() % 5)+5);

    int lock = -1;
    while(lock){
        int i=0;
        for(;i<3;i++){
            if(pthread_mutex_trylock((Emp+i))==0){
                printf("cliente empresarial %d\tcajero empresarial %d\t%d segundos\n", id, i, t);
                sleep(t);
                if(++numEmp[i]==5){
                    printf("Soy el cajero empresarial %d voy a descansar\n",i);
                    sleep(5);
                    numEmp[i]=0;
                }
                pthread_mutex_unlock((Emp+i));
                lock = 0;
                break;
            }
        }
    }
}

int main(){
    srand((unsigned)time(NULL));

    Gen = (pthread_mutex_t*)malloc(5*sizeof(pthread_mutex_t));
    Emp = (pthread_mutex_t*)malloc(3*sizeof(pthread_mutex_t));

    pthread_t* generalesT = (pthread_t*) malloc(G * sizeof(pthread_t));
    pthread_t* empresarialesT = (pthread_t*) malloc(E * sizeof(pthread_t));
    pthread_t* aux;

    int id = 1;
    for(aux = empresarialesT;aux<(empresarialesT+E);aux++,id++){
        pthread_create(aux,NULL,operaE,(void*)id);
    }
    id = 0;
    for(aux = generalesT;aux<(generalesT+G);aux++,id++){
        pthread_create(aux,NULL,operaG,(void*)id);
    }
        
    for(aux = generalesT;aux<(generalesT+G);aux++){
        pthread_join(*aux,NULL);
    }
    for(aux = empresarialesT;aux<(empresarialesT+E);aux++){
        pthread_join(*aux,NULL);
    }

    free(generalesT);
    free(empresarialesT);
    free(Gen);
    free(Emp);

    return 0;
}
