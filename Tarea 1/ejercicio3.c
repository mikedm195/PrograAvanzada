#include <stdio.h>
#include <stdlib.h>

struct Cama{
  char * nombre;
  char * apellido;
  int edad;
  char * telefono;
  int cama;
  int disponible;
};

typedef void (* menu_t)(struct Cama * camas);

void agregarPaciente(struct Cama * camas);
void verCama(struct Cama * camas);
void darAlta(struct Cama * camas);
void mostrarPacientes(struct Cama * camas);
void verDisponibles(struct Cama * camas);

int numDisponibles = 0;
int numCamas=0;

int main(){
  int op = -1;

  char * menu = "1.Agregar paciente\n2.Ver camas\n3.Dar de alta\n4.Mostrar Pacientes\n5.Ver camas disponibles/ocupadas\n6 .Salir\nSelecciona tu opcion: ";
  menu_t * opciones = (menu_t *)malloc(5*sizeof(menu_t));

  struct Cama * camas;

  camas = (struct Cama *)malloc(sizeof(struct Cama));

  *opciones = agregarPaciente;
  *(opciones+1) = verCama;
  *(opciones+2) = darAlta;
  *(opciones+3) = mostrarPacientes;
  *(opciones+4) = verDisponibles;

  while(op != 6){
    printf("%s",menu);
    scanf("%d",&op);
    if(op > 0 && op <6){
      if(op==1 && numDisponibles==0){
        camas = (struct Cama *) realloc (camas,(5+numCamas)*sizeof(struct Cama));
        numCamas+=5;
        numDisponibles=5;
        printf("Se agregaron 5 camas mas!!!\n");
      }
      (*(opciones[op-1]))(camas);
    }
  }

  int i = 0;
  for(;i<numCamas;i++){
    free((camas+i)->nombre);
    free((camas+i)->apellido);
    free((camas+i)->telefono);
  }
  free(camas);
  free(opciones);

  return 0;
}

void agregarPaciente(struct Cama * camas){

  int i=0;
  while((camas+i)->disponible !=0) i++;

  (camas+i)->nombre = (char*)malloc(50);
  printf("Dame el nombre del dueño: ");
  scanf("%s", (camas + i)->nombre);
  (camas+i)->apellido = (char*)malloc(50);
  printf("Dame el apellido: ");
  scanf("%s", (camas + i)->apellido);
  printf("Dame la edad: ");
  scanf("%i", &(camas + i)->edad);
  (camas+i)->telefono = (char*)malloc(50);
  printf("Dame el telefono: ");
  scanf("%s", (camas + i)->telefono);
  (camas+i)->cama = i;
  (camas+i)->disponible = 1;

  numDisponibles--;

}
void verCama(struct Cama * camas){
  int n;
  printf("Que cama quieres ver: ");
  scanf("%d",&n);

  if((camas+n)->disponible==1){
    printf("\tNum. Cama: %d\t%s %s\tEdad: %d\tTel: %s\n",n,(camas+n)->nombre,(camas+n)->apellido,(camas+n)->edad,(camas+n)->telefono);
  }else{
    printf("\tNum. Cama: %d\tDisponible\n",n);
  }

}
void darAlta(struct Cama * camas){
  int n;
  printf("Que numero de cama quiere dar de alta: ");
  scanf("%d",&n);
  if(n>=0 && n < numCamas){
    if((camas+n)->disponible == 1){
      (camas+n)->disponible = 0;
    }else{
      printf("Esa cama ya esta ocupada\n");
    }
  }else{
    printf("No existe esa cama\n");
  }
  numDisponibles++;
}
void mostrarPacientes(struct Cama * camas){
  int i = 0;
  for(;i<numCamas;i++){
    if((camas+i)->disponible==1){
      printf("\tNum. Cama: %d\t%s %s\tEdad: %d\tTel: %s\n",i,(camas+i)->nombre,(camas+i)->apellido,(camas+i)->edad,(camas+i)->telefono);
    }else{
      printf("\tNum. Cama: %d\tDisponible\n",i);
    }
  }
}
void verDisponibles(struct Cama * camas){
  printf("Disponibles: %d\t Ocupadas: %d\n",numDisponibles,numCamas-numDisponibles);
}
