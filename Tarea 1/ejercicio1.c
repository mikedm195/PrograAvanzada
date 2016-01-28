#include <stdio.h>
#include <stdlib.h>

struct Tripulante{
  char * nombre;
  char * apellido;
  int edad;
  char * rol;
};

struct Embarcacion{
  struct Tripulante dueno;
  char * nombre;
  int eslora;
  int manga;
  int maxTripulantes;
  int numTripulantes;
  struct Tripulante * tripulantes;
};

typedef void (* menu_t)(struct Embarcacion * embarcaciones);

void agregarEmbarcacion(struct Embarcacion * embarcaciones);
void agregarTripulante(struct Embarcacion * embarcaciones);
void verTripulacion(struct Embarcacion * embarcaciones);
void verEmbarcaciones(struct Embarcacion * embarcaciones);
int numEmbarcaciones = 0;

int main(){
  int global;
  int op = -1;
  char * menu = "1.Incorporar barco\n2.Incorporar tripulantes\n3.Ver tripulacion\n4.Ver embarcaciones\n5.Salir\nSelecciona tu opcion: ";
  menu_t * opciones = (menu_t *)malloc(4*sizeof(menu_t));  
  struct Embarcacion * embarcaciones;
  int * ptr = &numEmbarcaciones;

  embarcaciones = (struct Embarcacion *)malloc(sizeof(struct Embarcacion));

  *opciones = agregarEmbarcacion;
  *(opciones+1) = agregarTripulante;
  *(opciones+2) = verTripulacion;
  *(opciones+3) = verEmbarcaciones;

  while(op != 5){
    printf("%s",menu);
    scanf("%d",&op);
    if(op==1 && numEmbarcaciones > 0){
      printf("%d\n",numEmbarcaciones);
      embarcaciones = (struct Embarcacion *) realloc (embarcaciones,(numEmbarcaciones+1)*sizeof(struct Embarcacion));
    }
    if(op > 0 && op <5){
      (*(opciones[op-1]))(embarcaciones);
    }
  }
  int i = 0;
  for(;i<numEmbarcaciones;i++){
    int j = 0;
    for(;j<(embarcaciones+i)->numTripulantes;j++){
      free(((embarcaciones+i)->tripulantes+j)->nombre);
      free(((embarcaciones+i)->tripulantes+j)->apellido);
      free(((embarcaciones+i)->tripulantes+j)->rol);
    }
    free(((embarcaciones+i)->tripulantes+j));
    free((embarcaciones+i)->nombre);
    free((embarcaciones+i));
  }
  free(opciones);
  return 0;
}

void agregarEmbarcacion(struct Embarcacion * embarcaciones){

  //if(numEmbarcaciones>0)
    //embarcaciones = (struct Embarcacion *) realloc (embarcaciones,numEmbarcaciones*sizeof(struct Embarcacion));

  printf("Dame el nombre de la embarcaion: ");

  (embarcaciones+numEmbarcaciones)->nombre = (char*)malloc(50);
  scanf("%s", (embarcaciones + numEmbarcaciones)->nombre);

  printf("Dame la eslora: ");
  scanf("%i", &(embarcaciones + numEmbarcaciones)->eslora);
  printf("Dame la manga: ");
  scanf("%i", &(embarcaciones + numEmbarcaciones)->manga);
  printf("Dame el numero de tripulantes: ");
  scanf("%i", &(embarcaciones + numEmbarcaciones)->maxTripulantes);
  (embarcaciones + numEmbarcaciones)->numTripulantes = 0;
  (embarcaciones + numEmbarcaciones)->tripulantes = (struct Tripulante *)malloc((embarcaciones + numEmbarcaciones)->maxTripulantes*sizeof(struct Tripulante));

  (embarcaciones+numEmbarcaciones)->dueno.nombre = (char*)malloc(50);
  printf("Dame el nombre del dueño: ");
  scanf("%s", (embarcaciones + numEmbarcaciones)->dueno.nombre);
  (embarcaciones+numEmbarcaciones)->dueno.apellido = (char*)malloc(50);
  printf("Dame el apellido: ");
  scanf("%s", (embarcaciones + numEmbarcaciones)->dueno.apellido);
  printf("Dame la edad: ");
  scanf("%i", &(embarcaciones + numEmbarcaciones)->dueno.edad);
  (embarcaciones+numEmbarcaciones)->dueno.rol = (char*)malloc(5);
  (embarcaciones+numEmbarcaciones)->dueno.rol = "Dueño";

  numEmbarcaciones++;

}

void agregarTripulante(struct Embarcacion * embarcaciones){
  int op;

  printf("A que embarcacion quiere agregar: \n");
  int i = 0;
  for(;i<numEmbarcaciones;i++){
    printf("\t%d- %s\n",i,(embarcaciones+i)->nombre);
  }
  scanf("%d", &op);

  int numTrip = (embarcaciones+op)->numTripulantes;

  if(numTrip<(embarcaciones+op)->maxTripulantes){
    ((embarcaciones+op)->tripulantes+numTrip)->nombre = (char*)malloc(50);
    printf("Dame el nombre del tripulante: ");
    scanf("%s", ((embarcaciones+op)->tripulantes+numTrip)->nombre);

    ((embarcaciones+op)->tripulantes+numTrip)->apellido = (char*)malloc(50);
    printf("Dame el apellido: ");
    scanf("%s", ((embarcaciones+op)->tripulantes+numTrip)->apellido);
    printf("Dame la edad: ");
    scanf("%i", &((embarcaciones+op)->tripulantes+numTrip)->edad);
    printf("Dame el rol: ");
    ((embarcaciones+op)->tripulantes+numTrip)->rol = (char*)malloc(50);
    scanf("%s", ((embarcaciones+op)->tripulantes+numTrip)->rol);

    (embarcaciones+op)->numTripulantes++;
  }else{
    printf("La embarcacion ya esta llena\n");
  }
}

void verTripulacion(struct Embarcacion * embarcaciones){
  int op;

  printf("A que embarcacion quiere ver: \n");
  int i = 0;
  for(;i<numEmbarcaciones;i++){
    printf("\t%d- %s\n",i,(embarcaciones+i)->nombre);
  }
  scanf("%d", &op);

  printf("Nombre de Embarcacion: %s\n",(embarcaciones + op)->nombre);
  printf("\tEslora: %d\n\tManga: %i\n",(embarcaciones + op)->eslora,(embarcaciones + op)->manga);
  printf("\tMaximo de tripulantes: %i\tDisponibles: %i\n\tDueño:\n",((embarcaciones + op)->maxTripulantes),(embarcaciones + op)->maxTripulantes-(embarcaciones + op)->numTripulantes);

  printf("\t\t%s %s",(embarcaciones+op)->dueno.nombre,(embarcaciones+op)->dueno.apellido);
  printf("\tEdad: %i\tRol: %s\n\tTripulantes:\n",(embarcaciones+op)->dueno.edad,(embarcaciones+op)->dueno.rol);

  int j=0;
  for(;j<(embarcaciones + op)->numTripulantes;j++){
    printf("\t\t%s %s",((embarcaciones+op)->tripulantes+j)->nombre,((embarcaciones+op)->tripulantes+j)->apellido);
    printf("\tEdad: %i\tRol: %s\n",((embarcaciones+op)->tripulantes+j)->edad,((embarcaciones+op)->tripulantes+j)->rol);
  }

}

void verEmbarcaciones(struct Embarcacion * embarcaciones){
  int i=0;
  for(;i<numEmbarcaciones;i++){
    printf("Nombre de Embarcacion: %s\n",(embarcaciones + i)->nombre);
    printf("\tEslora: %d\n\tManga: %i\n",(embarcaciones + i)->eslora,(embarcaciones + i)->manga);
    printf("\tMaximo de tripulantes: %i\tDisponibles: %i\n\tDueño:\n",((embarcaciones + i)->maxTripulantes),(embarcaciones + i)->maxTripulantes-(embarcaciones + i)->numTripulantes);

    printf("\t\t%s %s",(embarcaciones+i)->dueno.nombre,(embarcaciones+i)->dueno.apellido);
    printf("\tEdad: %i\tRol: %s\n\tTripulantes:\n",(embarcaciones+i)->dueno.edad,(embarcaciones+i)->dueno.rol);

    int j=0;
    for(;j<(embarcaciones + i)->numTripulantes;j++){
      printf("\t\t%s %s",((embarcaciones+i)->tripulantes+j)->nombre,((embarcaciones+i)->tripulantes+j)->apellido);
      printf("\tEdad: %i\tRol: %s\n",((embarcaciones+i)->tripulantes+j)->edad,((embarcaciones+i)->tripulantes+j)->rol);
    }
  }
}
