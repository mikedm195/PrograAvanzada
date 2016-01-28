#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef int (*t_imprime)(void *);

struct Libro{
  char * nombre;
  char * apellido;
  int edad;
  char * rol;
};

void recorre(void * vector,size_t count, size_t size);


int main(){

  int * vectorInt = (int *)malloc(10*sizeof(int));
  //struct Libro libros = (struct Libro *)malloc(sizeof(struct Libro));
  int i = 0;
  for(;i<10;i++){
    printf("%d ",i);
    *(vectorInt+i) = i;
  }
  printf("\n");

  recorre(vectorInt,N,sizeof(vectorInt));

  free(vectorInt);
  //free(libros);
  return 0;
}

void recorre(void * vector,size_t count, size_t size){
  char temp=' ';
  void * inicio = vector;
  void * fin = inicio + (10);
  void * aux = inicio;
  while(temp != 'e'){
    printf("n-next\tp-previous\tb-beguin\tl-last\te-end\n");
    scanf("%c",&temp);

    if(temp == 'n'){
      aux++;
    }
    if(temp == 'p'){
      aux--;
    }
    if(temp == 'b'){
      aux = inicio;
    }
    if(temp == 'l'){
      aux = fin;
    }

  }
}

void imprimeInt(int * vector){
  printf("%d\n",*(vector+1) );
}
