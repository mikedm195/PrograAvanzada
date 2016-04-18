#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 5000

typedef struct Punto{
    float x;
    float y;
    float c;
}punto;

void inicializaMatriz(punto * puntos);


int main(){
    
    srand((unsigned int)time(NULL));

    punto * puntos = (punto *)malloc(N*sizeof(punto));
    punto c1;
    punto c2;

    inicializaMatriz(puntos);

    return 0;
}

void inicializaMatriz(punto * puntos){
    float max = 10;
    int i = 0;
    for(;i<N;i++){
        ((puntos+i)->x)=((float)rand()/(float)(RAND_MAX));
        ((puntos+i)->y)=((float)rand()/(float)(RAND_MAX));
        if(i<10)
            printf("%f\t%f\n",((puntos+i)->x),((puntos+i)->y));
    }
}
