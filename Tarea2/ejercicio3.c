#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 5

int main(int argc, const char * argv[]){

	time_t t;

	int n = 0;
	int estado;

	int temp = 0;

	printf("Cuantos procesos van a ser: ");
	scanf("%d",&n);

	pid_t pid;

	int i = 0;
	for(;i<n;i++){
		pid = fork();
		srand((unsigned) time(&t)+getpid());
		if(pid == -1){
			printf("Error al crear el hijo %d",i);
		}else if(pid == 0){
			temp = (rand() % 5)+1;
			sleep(temp);		

			exit(getpid());
		}
	}
	
	while((pid = wait(&estado))>0)
		printf("Ya acabo el hijo con el pid %d\n",pid);

	return 0;
}
