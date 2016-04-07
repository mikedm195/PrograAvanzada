#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>

#define S 10
#define R 5
#define pesoRobot 6

typedef struct Seccion {
    pthread_mutex_t libre;
    int peso;
    int pesoActual;
}seccion;

seccion * secciones;

void comprar(void * p){
    int id = (int)p;
    int i = 0;
    while(i<S){
        pthread_mutex_lock(&((secciones+i)->libre));
        if(((secciones+i)->pesoActual + pesoRobot) <= (secciones+i)->peso ){
            printf("Robot %d entra a la seccion %d\tBuscando productos...\n",id,i);
            (secciones+i)->pesoActual += pesoRobot;
            if(i>0){
                pthread_mutex_lock(&((secciones+i-1)->libre));
                (secciones+i-1)->pesoActual -= pesoRobot;
                pthread_mutex_unlock(&((secciones+i-1)->libre));
            }
            int j=0;
            //for(;j<S;j++)
            //    printf("%d ",(secciones+j)->pesoActual);
            //printf("\n");
            pthread_mutex_unlock(&((secciones+i)->libre));
            sleep(rand()%5);
            printf("Robot %d acabo de rocojer los productos de la seccion %d\n",id,i);
            i++;
        }else{
            printf("Robot %d no puede avanzar\n",id);
            pthread_mutex_unlock(&((secciones+i)->libre));
            sleep(5);
        }
    }
    pthread_mutex_lock(&((secciones+i-1)->libre));
    (secciones+S-1)->pesoActual -= pesoRobot;
    pthread_mutex_unlock(&((secciones+i-1)->libre));

    printf("Robot %d acabo\n",id);
}

int main(){
    srand(time(NULL));

    secciones = (seccion*)malloc(S*sizeof(seccion));
    pthread_t * robots = (pthread_t*)malloc(R*sizeof(pthread_t));
    pthread_t * aux;

    int i = 0;
    printf("Peso de secciones: ");
    for(;i<S;i++){
        (secciones+i)->peso = (rand()%10)+10;
        (secciones+i)->pesoActual=0;
        printf("%d ",(secciones+i)->peso);
    }

    printf("\n");
    for(aux = robots;aux<(robots+R);aux++){
        pthread_create(aux,NULL,comprar,(void*)(aux-robots));
    }

    for(aux = robots;aux<(robots+R);aux++){
        pthread_join(*aux,NULL);
    }

    free(robots);
    free(secciones);
    return 0;
}
