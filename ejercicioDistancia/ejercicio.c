#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define N 5000
#define E .0001

typedef struct Punto{
    double x;
    double y;
    double c;
}punto;

void inicializaMatriz(punto * puntos);
double dist(double x1,double y1,double x2,double y2);

int main(){
    
    srand((unsigned int)time(NULL));

    punto * puntos = (punto *)malloc(N*sizeof(punto));
    punto * distancias = (punto *)malloc(N*sizeof(punto)); 
    punto c1;
    punto c2;

    inicializaMatriz(puntos);
    c1.x = ((double)rand()/(double)(RAND_MAX));
    c1.y = ((double)rand()/(double)(RAND_MAX));
    c2.x = ((double)rand()/(double)(RAND_MAX));
    c2.y = ((double)rand()/(double)(RAND_MAX));
    
    double sumC1x=-1;
    double sumC1y=-1;
    double sumC2x=-1;
    double sumC2y=-1;
    double nC1 = 0.0;
    double nC2 = 0.0;

    int acabo = 0; 

    printf("\n");
	int i = 0;
    while(acabo==0){
	//for(;i<260;i++){
        int i = 0;
		sumC1x = 0;
		sumC1y = 0;
		sumC2x = 0;
		sumC2y = 0;
		nC1 = 0;
		nC2 = 0;
		#pragma omp parallel for private(i)
        for(i=0;i<N;i++){
            double distanciaC1 = dist((puntos+i)->x,(puntos+i)->y,c1.x,c1.y); 
            double distanciaC2 = dist((puntos+i)->x,(puntos+i)->y,c2.x,c2.y); 
			#pragma omp critical
			{
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
        }
        sumC1x /= nC1;
        sumC1y /= nC1;
        sumC2x /= nC2;
        sumC2y /= nC2;
    	if(dist(sumC1x,sumC1y,c1.x,c1.y) < E || dist(sumC2x,sumC2y,c2.x,c2.y) < E){
			acabo = 1;
		}
		
		//printf("C1(%f,%f)\n", c1.x, c1.y);
	    //printf("C2(%f,%f)\n", c2.x, c2.y);
    	//printf("==============================\n");
		
		c1.x = sumC1x;
		c1.y = sumC1y;
		c2.x = sumC2x;
		c2.y = sumC2y;
    }
	
    printf("=========================\n");
    printf("= C1(%f,%f) =\n", c1.x, c1.y);
    printf("= C2(%f,%f) =\n", c2.x, c2.y);
    printf("=========================\n");
    
	free(puntos);
	free(distancias);

    return 0;
}

void inicializaMatriz(punto * puntos){
    double max = 10;
    int i = 0;
    for(;i<N;i++){
        ((puntos+i)->x)=((double)rand()/(double)(RAND_MAX));
        ((puntos+i)->y)=((double)rand()/(double)(RAND_MAX));
        //if(i<10)
        //    printf("%f\t%f\n",((puntos+i)->x),((puntos+i)->y));
    }
}

double dist(double x1,double y1,double x2,double y2){
	double a = fabsf(x2 - x1);
	double b = fabsf(y2 - y1);
    return sqrt(a*a+b*b); 
}
