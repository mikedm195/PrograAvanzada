#include <stdio.h>
#include <stdlib.h>

int main(){
  int size=0;
  int elementos=0;
  char * posicion;
  char * temp;
  int veces;
  printf("Dame la longitud de la cadena: ");
  scanf("%d",&size);

  char * cadena = (char*)malloc(sizeof(char)*size);
  char * arreglo = (char*)malloc(sizeof(char)*size);

  printf("Dame la cadena: ");
  scanf("%s",cadena);
  printf("\n");
  posicion = cadena;
  temp = posicion+1;

  while(*posicion != '\0'){
    veces=1;
    temp = posicion+1;
    if(*posicion !='\n'){
      while(*temp != '\0'){
        if(*temp==*posicion){
          veces++;
          *temp='\n';

        }
        *temp++;
      }
      printf("%c\t%d\t",*posicion,veces);
      int i = 0;
      for(;i<veces;i++)
        printf("*");
      printf("\n");
      *posicion++;
    }
  }

  free(cadena);
  free(arreglo);

  return 0;
}
