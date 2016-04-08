#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define F 3

pthread_mutex_t * disponible;
int tabacos,papeles,fosforos;
pthread_mutex_t tabaco,papel,fosforo;

void administra(){
    int hayIngredientes;
    while(1){
        hayIngredientes=0;
        if(pthread_mutex_trylock(disponible)==0){
            printf("El agente toma tabaco y lo pone sobre la mesa\n");
            pthread_mutex_lock(&tabaco);
            tabacos++;
            pthread_mutex_unlock(&tabaco);
            hayIngredientes = 1;
            pthread_mutex_unlock(disponible);
        }else{
            printf("No se pudo tomar tabaco porque estan fumando/descansando\n");
        }
        if(pthread_mutex_trylock((disponible+1))==0){
            printf("El agente toma papel y lo pone sobre la mesa\n");
            pthread_mutex_lock(&papel);
            papeles++;
            pthread_mutex_unlock(&papel);
            hayIngredientes = 1;
            pthread_mutex_unlock((disponible+1));
        }else{
            printf("No se pudo tomar papel porque estan fumando/descansando\n");
        }
        if(pthread_mutex_trylock((disponible+2))==0){
            printf("El agente toma fosforo y lo pone sobre la mesa\n");
            pthread_mutex_lock(&fosforo);
            fosforos++;
            pthread_mutex_unlock(&fosforo);
            hayIngredientes = 1;
            pthread_mutex_unlock((disponible+2));
        }else{
            printf("No se pudo tomar fosforo porque estan fumando/descansando\n");
        }
        
        if(hayIngredientes==0){
            printf("Como no habian ingredientes el agente se va a hacer otras actividades\n");
            sleep(10);
        }

        sleep(15);
    }
}

void fuma(void * p){
    int id = (int)p;
    int tieneTabaco=0,tienePapel=0,tieneFosforo=0;
    while(1){
        if(tieneTabaco==0){
            pthread_mutex_lock(&tabaco);
            if(tabacos>0){
                tieneTabaco++;
                printf("Fumador %d toma tabaco\n",id);
                tabacos--;
            }
            pthread_mutex_unlock(&tabaco);
        }
        if(tienePapel==0){
            pthread_mutex_lock(&papel);
            if(papeles>0){
                tienePapel++;
                printf("Fumador %d toma papel\n",id);
                papeles--;
            }
            pthread_mutex_unlock(&papel);
        }
        if(tieneFosforo==0){
            pthread_mutex_lock(&fosforo);
            if(fosforos>0){
                tieneFosforo++;
                printf("Fumador %d toma fosforo\n",id);
                fosforos--;
            }
            pthread_mutex_unlock(&fosforo);
        }
        if(tieneFosforo>0&&tienePapel>0&&tieneTabaco>0){
            pthread_mutex_lock((disponible+id));
            printf("Fumador %d esta fumando\n",id);
            sleep(10);
            printf("Fumador %d ecabo de fumar... esta descansando\n",id);
            //pthread_mutex_unlock((disponible+id));
            sleep(20);
            printf("Fumador %d listo para seguir fumando\n",id);
            tieneFosforo=0;tienePapel=0;tieneTabaco=0;
            pthread_mutex_unlock((disponible+id));
        }
    }

}

int main(){

    pthread_t agente;
    pthread_t * fumador;
    pthread_t * aux;

    fumador = (pthread_t*)malloc(F*sizeof(pthread_t));
    disponible = (pthread_mutex_t*)malloc(F*sizeof(pthread_mutex_t));

    pthread_create(&agente,NULL,administra,NULL);

    for(aux=fumador;aux<(fumador+F);aux++)
        pthread_create(aux,NULL,fuma,(void*)(aux-fumador));

    for(aux=fumador;aux<(fumador+F);aux++)
        pthread_join(*aux,NULL);
   

    pthread_join(agente,NULL);

    free(fumador);
    free(disponible);


    return 0;
}
