#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>

int i = 0;
int *numeros;

void control_alarm(int signal){
  printf("Dese prisa. Dato %d: \n", i);
  alarm(3);
}

int main(int argc, char *argv[]){
  struct sigaction gest;
  int err;
  if (argc != 2) {
    printf("Instrucciones:\n%s 5-9\n", argv[0]);
    exit(-1);
  }
  if(atoi(argv[1]) <= 4 || atoi(argv[1]) >=10){
    printf("Instrucciones:\n%s 5-9\n", argv[0]);
    exit(-1);
  }
  numeros = (int*)malloc(sizeof(int)*atoi(argv[1]));
  gest.sa_handler = control_alarm;
  gest.sa_flags = SA_RESTART;
  err = sigaction (SIGALRM, &gest, 0);
  signal(SIGINT, SIG_IGN); 
  alarm(3);
  for(i = 0 ; i < atoi(argv[1]); i++){
    printf("Dato %d:\n", i);
    scanf("%d", (numeros+i)); 
  }
  for(i = 0; i < atoi(argv[1]); i++)
    printf("Numero %d ---> %d\n", i, *(numeros+i));
  free(numeros);
  return 0;
}

