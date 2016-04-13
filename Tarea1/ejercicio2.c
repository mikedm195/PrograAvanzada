#include <stdio.h>
#include	<stdlib.h>
#include <time.h>

struct Persona {
  char* nombre;
  int edad;
  int* respuestas;
};

void agregarPersona(struct Persona * );
void agregarPregunta(char***);

void llenarEncuesta(struct Persona * p, char***);
void histograma(struct Persona * p, char***);
void histogramaEdades(struct Persona * p, char***);
void Borrar(struct Persona * p, char***);

int numPersonas;


int main ( int argc, char *argv[] ){

  srand((int) time(NULL));

  printf("Cuantas personas van a ser: ");
  scanf("%d",&numPersonas);

  struct Persona* personas = (struct Persona*) malloc (numPersonas * sizeof(struct Persona));
  char*** preguntas = (char***) malloc (10 * sizeof(char**));

  agregarPersona(personas);

  agregarPregunta(preguntas);

  llenarEncuesta(personas, preguntas);

  histograma(personas, preguntas);

  histogramaEdades(personas, preguntas);

  Borrar(personas, preguntas);

  return 0;
}

void agregarPersona(struct Persona * p){
  int i = 0;
  for(;i<numPersonas;i++){
    (p+i)->nombre = (char*) malloc (25);
    printf("Nombre: ");
    scanf("%s", (p+i)->nombre);
    int d = 0;
    while (d > 120 || d < 17){
      printf("Edad: ");
      scanf("%d", &d);
      if (d < 17)
        printf("Muy joven\n");
      else if (d > 120)
        printf("Muy viejo");
      else
        (p+i)->edad = d;
    }
    (p+i)->respuestas = (int *) malloc (10 * sizeof(int));
  }
}

void agregarPregunta(char*** p){
  int i = 0;
  for(;i<10;i++){
    *(p+i) = (char**) malloc (7 * sizeof(char*));
    int j;
    *(*(p+i)) = (char*) malloc (25);
    printf("Encabezado: ");
    scanf("%s", *(*(p+i)));
    for (j = 1; j < 7; ++j){
      printf("Opcion -%d", j);
      *(*(p+i)+j) = (char *) malloc (25);
      scanf("%s", (*(*(p+i)+j)));
    }
  }
}

void llenarEncuesta(struct Persona* p, char*** e){
  time_t t;
  int i, j;
  for (i = 0; i < numPersonas; ++i){
    for(j = 0; j < 10; ++j){
      int num = rand() % 7;
      *((p+i)->respuestas+j) = num;
      if(num>0)
        printf("%s selecciono la %d opcion de la pregunta %d\n",(p+i)->nombre,num,j);
      else
      printf("%s no respondio la pregunta %d\n",(p+i)->nombre,j);
    }
    printf("\n");
  }
}

void histograma(struct Persona* p, char*** e){
  int i,j,k;
  int cont = 0;
  int* conts = (int *) malloc (7 * sizeof(int));
  for (i = 0; i < 7; ++i)
    *(conts+i) = 0;

  for ( i = 0; i < 10; i++){
    for(j = 0; j < numPersonas; j++){
      int res = *((p+j)->respuestas+i);
      (*(conts+res))++;
    }
    printf("Pregunta %d\n", i);
    printf("No Respuesta Frecuencia\n");
    for (j = 1; j < 7; ++j){
      printf(" %d\t%d\t", j,*(conts+j));
      for (k = 0; k < *(conts+j); k++)
      printf("*");
      printf("\n");
    }
    for (j = 0; j < 7; ++j)
      *(conts+j) = 0;
    printf("\n");
  }
  free(conts);

}

void histogramaEdades(struct Persona* p, char***e){
  int * cont = (int*) malloc (5 * sizeof(int));
  int i, j, k;
  printf("----Histograma por edades----\n");
  for (i = 0; i < 10; ++i){
    printf("Pregunta %d\n", i);
    printf("No [18-25] [26-35] [36-45] [46-65] [66-120]\n");
    for(j = 1; j < 7; ++j){
      printf("%d ", j);
      for(k = 0; k < numPersonas; ++k){
        if(*((p+k)->respuestas+i) == j){
          if ((p+k)->edad < 26)
            *cont = *cont +1;
          else if((p+k)->edad < 36)
            *(cont+1) = *(cont+1) +1;
          else if((p+k)->edad < 46)
            *(cont+2) = *(cont+2) +1;
          else if((p+k)->edad < 66)
            *(cont+3) = *(cont+3) +1;
          else if((p+k)->edad < 120)
            *(cont+4) = *(cont+4) +1;
        }
      }
      printf(" \t%d\t%d\t%d\t%d\t%d\n",*cont, *(cont+1), *(cont+2), *(cont+3), *(cont+4));
      for (k = 0; k < 5; k++){
        *(cont+k) = 0;
      }
    }
  }
  free (cont);
}

void Borrar(struct Persona* p, char*** q){
  int i,j;
  for (i = 0; i < numPersonas; i++){
    free ((p+i)->nombre);
    free ((p+i)->respuestas);
  }
  free(p);
  for (i = 0; i < 10; i++){
    for(j = 0; j < 7; j++){
      free(*(*(q+i)+j));
    }
    free(*(q+i));
  }
  free(q);
}
