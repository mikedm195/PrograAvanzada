#include <stdio.h>
#include <unistd.h>

void leer(int * fd);
void escribir(int * fd);

int main(int argc, const char * argv[]){
	int tuberia[2];
	pid_t pid;
	
	int n = atoi(argv[1]);
	int i = 0;
	for(;i<n;i++){
		
		pid = fork();
		pipe(tuberia);

		if (pid == -1){
			printf("Error al crear el proceso hijo");
			//exit(-1);
		}else if (pid == 0){
			leer(tuberia);
		}else {	
			escribir(tuberia);
		}
	}
	return 0;
}

void leer(int * fd){
	printf("leyendo\n");
	int c;
	close(fd[1]);
	read(fd[0],&c,sizeof(int));
	printf("Soy el proceso con PID %d  y recibí el testigo %d, el cual tendré por 3 segundos\n",getpid(),c);
	
}

void escribir(int * fd){
	printf("escribiendo\n");
	int n = 0;
	sleep(3);
	close(fd[0]);
	write(fd[1],&n, sizeof(int));
}


