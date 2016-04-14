#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 10000
#define max 10000

void iniciaCriba(int * criba, int tam){
    int i=2;
    int j;
    double raiz = sqrt(10000.0);
    for(;i<=raiz;i++)
        if(*(criba+i)==0)
            for(j=i*2;j<=tam;j+=i)
                *(criba+j)=1;
}

int intLen(int num){
    int l=0;
    while(num>0){
        l++;
        num/=10;
    }
    return l;
}

int checaCircular(int * primos,int num){
    int tamNum = intLen(num);
    int i=0;
    int j=0;
    for(;i<tamNum;i++){
        if(*(primos+num)==1)
            return 0;
        int menor = (num%10);
        num/=10;
        for(j=0;j<tamNum-1;j++)
            menor*=10;
        num+=menor;
    }
    return 1;
}

int main(){

    srand((unsigned)time(NULL));
    clock_t inicio,fin;
    int * criba = (int *)malloc(max*sizeof(int));
    unsigned short **matriz = (unsigned short**) malloc (N* sizeof(unsigned short*));
    char **matriz2 = (char**) malloc (N* sizeof(char*));

    int i = 0, j = 0;


    inicio = clock();
    for(;i <= max;i++){
        *(criba+i)=0;
    }
    
    iniciaCriba(criba,max);
    
    i=0;
    for(i = 0; i < N; ++i){
        matriz[i] = (unsigned short*) malloc(N*sizeof(unsigned short));
        matriz2[i] = (char*) malloc (N);
        j=0;
        for(; j <N; ++j){
            *(*(matriz +i)+j) = (unsigned short)(rand()%9901) + 100;
            *(*(matriz2+i)+j) = 0; 
        }
    }

    fin = clock();
    printf("Tiempo cargando datos: %f\n", (double)(fin-inicio)/CLOCKS_PER_SEC);

    double start = omp_get_wtime();
    #pragma omp parallel shared(matriz, matriz2, criba) private(i,j)
    {
        #pragma omp for schedule(auto) nowait
        for(i = 0; i< N; i++){
            for(j = 0; j <N ; j++){
                int esCircular = checaCircular(criba ,*(*(matriz+i)+j));
                *(*(matriz2+i)+j) = esCircular; 
                //if(esCircular == 1 && i < 100 && j < 100)
                //    printf("Primo Circular: %d\tPosicion:\tx: %d\ty:%d\n",*(*(matriz+i)+j),i,j);
            }
        }
    }

    printf("Paralelo omp: %f\n", omp_get_wtime()-start);

    inicio = clock();
        
    for(i = 0; i< N; i++){
        for(j = 0; j <N ; j++){
            int esCircular = checaCircular(criba ,*(*(matriz+i)+j));
            *(*(matriz2+i)+j) = esCircular; 
            //if(esCircular == 1 && i < 100 && j < 100)
            //    printf("Primo Circular: %d\tPosicion:\tx: %d\ty:%d\n",*(*(matriz+i)+j),i,j);
        }
    }

    fin = clock();
    printf("Secuencial: %f\n", (double)(fin-inicio)/CLOCKS_PER_SEC);
    free(matriz); 
    free(matriz2); 
    free(criba);
    return 0;
}
