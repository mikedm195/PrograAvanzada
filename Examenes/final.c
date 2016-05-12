#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

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
	for(i=salida-1;i<N;i+=salida)
		if(mapa[i][i]==1)
			mapa[i][i]=0;
	for(i=0;i<N/S;i++)
		maxs[i]=N*N;
}

void print(){
	int i=0,j=0,k=0;
	int salida = N/4;
	for(;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d",mapa[i][j]);
			if(j%salida==S-1)
				printf("|");
		}
		printf("\n");
		if(i%salida==S-1){
			for(k=0;k<N+S;k++)
				printf("_");
			printf("\n");
		}
	}
			
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
		if(x < limite && y < limite && mapa[x+1][y+1]==0)
			buscar(ini,x+1,y+1,++pasos);
		if(x < limite && mapa[x+1][y]==0)
			buscar(ini,x+1,y,++pasos);
		if(y < limite && mapa[x][y+1]==0)
			buscar(ini,x,y+1,++pasos);
	//}
}

int main(){
	srand(time(NULL));
	creaMapa();
	print();

	int numSec = N/S;

	pthread_t * secciones = (pthread_t*)malloc(numSec*sizeof(pthread_t));
	pthread_t * aux;

	//aux = secciones;
	for(aux=secciones;aux<(secciones+numSec);aux++)
		pthread_create(aux,NULL,busca,(void*)(aux-secciones));
	
	aux = secciones;
	for(aux=secciones;aux<(secciones+numSec);aux++)
		pthread_join(*aux,NULL);
	free(secciones);
	return 0;
}
