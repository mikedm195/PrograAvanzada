#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#define numPersonas 10

pthread_mutex_t mutex;
int genero=-1;//-1=vacio 0=hombre 1=mujer
int enFila[2];//muestra cuentos hombres y mujeres hacen fila para entrar
int adentro;//Cuantas personas estan adentro del baño

void mujer(){

    while(genero == 0);
    genero = 1;

    pthread_mutex_lock(&mutex);
       
    printf("=>Entra una mujer (%d en espera)\n",--enFila[1]);
        
    pthread_mutex_unlock(&mutex);
    adentro++;
    sleep(rand()%5);
    
    printf("=>Sale una mujer\n");

    adentro--;
    if(adentro == 0){
        printf("=>Sanitario vacio\n");
        genero = -1;
        pthread_mutex_unlock(&mutex);
    }
}

void hombre(){
    
    while(genero == 1);
    genero = 0;

    pthread_mutex_lock(&mutex);
        
    printf("=>Entra un hombre (%d en espera)\n",--enFila[0]);

    pthread_mutex_unlock(&mutex);
    adentro++;
    sleep((rand()%5)+2);
    
    printf("=>Sale un hombre\n");

    adentro--;
    if(adentro == 0){
        printf("=>Sanitario vacio\n");
        genero = -1;
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    srand(time(NULL));
    
    pthread_t * persona = (pthread_t*)malloc(numPersonas*sizeof(pthread_t));
    pthread_t * aux;
    printf("=>Sanitario Vacio\n");
    for(aux = persona;aux<(persona+numPersonas);aux++){
        int temp = rand()%2;
        if(temp==0){
            printf("=>LLega un hombre (%d en espera)\n",++enFila[0]);
            pthread_create(aux,NULL,hombre,NULL);
        }else{
            printf("=>LLega una mujer (%d en espera)\n",++enFila[1]);
            pthread_create(aux,NULL, mujer,NULL);
        }

        sleep(rand()%3);
    }
    for(aux = persona;aux<(persona+numPersonas);aux++){
        pthread_join(*aux,NULL);
    }
    free(persona);
    return 0;
}
