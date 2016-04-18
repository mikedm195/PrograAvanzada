#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 5000
#define E .0001

typedef struct Punto{
    float x;
    float y;
    float c;
}punto;

void inicializaMatriz(punto * puntos);


int main(){
    
    srand((unsigned int)time(NULL));

    punto * puntos = (punto *)malloc(N*sizeof(punto));
    punto * distancias = (punto *)malloc(N*sizeof(punto)); 
    punto c1;
    punto c2;

    inicializaMatriz(puntos);
    c1.x = ((float)rand()/(float)(RAND_MAX));
    c1.y = ((float)rand()/(float)(RAND_MAX));
    c2.x = ((float)rand()/(float)(RAND_MAX));
    c2.y = ((float)rand()/(float)(RAND_MAX));
    
    punto temp1;
    temp1.x = -1.0;
    temp1.y = -1.0;
    
    punto temp2;
    temp2.x = -1.0;
    temp2.y = -1.0;
    
    float sumC1x=-1;
    float sumC1y=-1;
    float sumC2x=-1;
    float sumC2y=-1;
    float nC1 = 0.0;
    float nC2 = 0.0;
    
    printf("1\n");
    //while((c1.x-sumC1x + c1.y-sumC1y) > E && (c2.x-sumC2x + c2.y-sumC2y) > E){
        int i = 0;
        for(;i<N;i++){
            float distanciaC1 = abs((puntos+i)->x - c1.x)/abs((puntos+i)->y - c1.y);
            float distanciaC2 = abs((puntos+i)->x - c2.x)/abs((puntos+i)->y - c2.y);
            printf("2\n");
            if(distanciaC1 < distanciaC2){
                sumC1x += ((puntos+i)->x);
                sumC1y += ((puntos+i)->y);
                nC1++;
            }else{
                sumC2x += ((puntos+i)->x);
                sumC2y += ((puntos+i)->y);
                nC2++;
            }
        }
        sumC1x /= nC1;
        sumC1y /= nC1;
        sumC2x /= nC2;
        sumC2y /= nC2;
    //}
    printf("%f\t%f\n%f\t%f\n",sumC1x,sumC1y,sumC2x,sumC2y);

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
