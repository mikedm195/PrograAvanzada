#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define N 16
#define S 4

int mapa[N][N];
int maxs[N/S];

void creaMapa(){
	int i=0,j=0;
	int salida = N/4;
	for(;i<N;i++)
		for(j=0;j<N;j++)
			if(rand()%10>2)
				mapa[i][j]=0;
			else
				mapa[i][j]=1;
	for(i=0;i<N;i+=salida){
		mapa[i][i]==8;
		mapa[i+salida-1][i+salida-1]==8;
	}
	for(i=0;i<N/S;i++)
		maxs[i]=N*N;
}

void dibuja(){
	
}

void print(){
	int rutaMin = 0;
	int i=0,j=0,k=0;
	for(i=0;i<N/S;i++)
		rutaMin+=maxs[i];
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d",mapa[i][j]);
		}
		printf("\n");
	}

	if(rutaMin > N*N)
		printf("No se puede\n");
	else	
		printf("Ruta minima = %d\n",rutaMin);
}

void busca(void * p){
	int ns = (int)p;
	int s = ns*(N/S);
	int size = (N/S);
	buscar(s,s,s,0);
	printf("seccion %d  minimo %d\n",ns,maxs[ns]);
}

void buscar(int ini,int x, int y,int pasos){
	int limite = ini+(N/S)-1;
	if(x==limite && y==limite)
		if(pasos < maxs[ini/(N/S)])
			maxs[ini/(N/S)] = pasos;
	//if(pasos<max){
		if(x < limite && y < limite && mapa[x+1][y+1] != 1){
			if(maxs[ini/(N/S)]>=N*N)
				mapa[x][y]=8;
			buscar(ini,x+1,y+1,++pasos);
		}
		if(x < limite && mapa[x+1][y] !=1){
			if(maxs[ini/(N/S)]>=N*N)
				mapa[x][y]=8;
			buscar(ini,x+1,y,++pasos);
		}
		if(y < limite && mapa[x][y+1] !=1){
			if(maxs[ini/(N/S)]>=N*N)
				mapa[x][y]=8;
			buscar(ini,x,y+1,++pasos);
		}
	//}
}

void signalCtrl(int n){
	print();
}

int main(){
	srand(time(NULL));
	creaMapa();
	
	 signal(SIGUSR1, signalCtrl);

	int numSec = N/S;

	pthread_t * secciones = (pthread_t*)malloc(numSec*sizeof(pthread_t));
	pthread_t * aux;

	//aux = secciones;
	for(aux=secciones;aux<(secciones+numSec);aux++)
		pthread_create(aux,NULL,busca,(void*)(aux-secciones));
	
	aux = secciones;
	for(aux=secciones;aux<(secciones+numSec);aux++)
		pthread_join(*aux,NULL);
	
	print();
	free(secciones);
	return 0;
}
