#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define U 5

FILE *data;
int medidas[U];
int alarmas[U];

pthread_t central;
pthread_mutex_t m[U*2] = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file = PTHREAD_MUTEX_INITIALIZER;

void registrar(int id);
void critical(int id);
void *funcion(void *p);
void *funcionCentral(void *p);

int main(int argc, char *argv[]){
	srand(time(NULL));

	pthread_t *uads = (pthread_t*)malloc(U*sizeof(pthread_t));
	pthread_create(&central, NULL, funcionCentral, NULL);
	
	int i = 0;
	for(i = 0; i < U; ++i)
    	pthread_create(uads+i, NULL, funcion, i);

	for(i = 0; i < U; ++i)
    	pthread_join(*(uads+i), NULL);

	pthread_join(central, NULL);

	free(uads);

  	return 0;
}

void registrar(int id){
	int i = 0;
	printf("Recibiendo señal\n");
  	for(i = 0; i < U; ++i){
	    pthread_mutex_lock(m+i);
	    pthread_mutex_lock(&file);
    
	    data = fopen("data", "a+");
    	fprintf(data, "UAD #%d = %d\n", i, medidas[i]);
	    fclose(data);
	    pthread_mutex_unlock(&file);
    	pthread_mutex_unlock(m+i);
	    alarm(rand()%5);
  	}
}

void critical(int id){
	int i = 0;
	for(i = 0; i < U; ++i){
    	pthread_mutex_lock(m+U+i);
    	if(alarmas[i]){
		    pthread_mutex_lock(&file);
      		data = fopen("data", "a+");
		    fprintf(data, "UAD #%d (valor critico)\n", i);
	        fclose(data);
      		pthread_mutex_unlock(&file);
      		alarmas[i]--;
    	}
    	pthread_mutex_unlock(m+i+U);
  	}
}

void *funcion(void *p){
	int aux = (int)p;
	int tmp;

  	while(1){
	    sleep(rand()%3+1);
   	 	pthread_mutex_lock(&(*(m + aux)));
    
	    medidas[aux] = rand()%10;
	    pthread_mutex_lock(&(*(m+aux)));
    
    	if(!(tmp = rand()%10)){
		    printf("UAD #%d (valor critico)\n", aux);
      		pthread_mutex_lock(m+aux+U);
  		    alarmas[aux]++;
		    pthread_kill(central, SIGUSR1);
		    pthread_mutex_unlock(m+aux+U);
	    }
  	}
}

void *funcionCentral(void *p){
	signal(SIGALRM, registrar);
	signal(SIGUSR1, critical);

	alarm(rand()%5);
	while(1);
}
