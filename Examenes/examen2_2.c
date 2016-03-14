#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define temp 3
#define PATH "datos"
#define ndir 7

char *buffer[20];
FILE *file = NULL;
int grabar = 0;

void control_alarm(int signal){
  printf("Señal de  alarma\n");
  grabar = 0;
}

void borrar();

void existe();

void imprimir();

int main(int argc, char *argv[]){
  int i = 0;
  signal(SIGALRM, SIG_DFL);
  alarm(2);
  signal(SIGALRM, control_alarm);
  existe();
  while(i < ndir){
    printf("Creando\n");
    int signal;
    grabar = 1;
    sprintf(buffer, "./datos/a%d", i);
    i++;
    file = fopen(buffer, "w+");
    alarm(temp);
    while(grabar)
      fputc('x', file);
    fclose(file);
  }
  imprimir();
  printf("\n");
  return 0;
}
void borrar(){
  struct dirent *d;
  DIR *dir;
  char buf[256];
  dir = opendir(PATH);
  while(d = readdir(dir)){
    if(d->d_type == DT_REG){
      printf("Borrando ---> %s\n", d->d_name);
      sprintf(buf, "%s/%s", PATH, d->d_name);
      unlink(buf);
      remove(buf);
    }
  }
}
void existe(){
  int status;
  DIR *dir = opendir(PATH);
  if (dir){
    printf("El directorio ya existe\n");
    borrar();
    closedir(dir);
  }else if(ENOENT == errno){
    printf("El directorio no existe\nCreando directorio\n");
    mkdir(PATH, 0777);
  }else{
    printf("Error al abrir directorio\n");
  }
}
void imprimir(){
  printf("\n");
  DIR *dir; 
  dir = opendir(PATH);
  struct dirent *d;
  struct stat s;
  char *path;
  if (dir){
    while (d = readdir(dir)){
      if(d->d_type == DT_REG){
        path = (char*)malloc((strlen(path)+strlen(d->d_name)+1)*sizeof(char));
        strcpy(path, "datos/");
        strcat(path, d->d_name);
        stat(path, &s);
        printf("%s --------> %lld Megas\n", d->d_name, (long long)(((s.st_size)/1024)/1024));
      }
    }
    closedir(dir);
  }
}
