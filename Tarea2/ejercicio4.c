#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>

void creaHijo(int niveles,int procesos, int n){
	int j = 0;		
	for(;j<procesos;j++){
		pid_t pid;
		pid = fork();
		if(pid == -1){
			printf("Error creando hijo");
		}else if(pid == 0){
			int k = 0;
			for(;k<n;k++)
				printf("\t");
			if(n<niveles-1){
				printf("%d-%d\n",getpid(),getppid());
				creaHijo(niveles,procesos,n+1);
			}else{			
				printf("%d-%d\n",getpid(),getppid());
			}	
			exit(0);		
		}else{
			wait(NULL);
		}
	}

}
int main(int argc,const char * argv[]){

	int c;
	int niveles = 0;
	int procesos = 0;
	int status;

	opterr = 0;

	while ((c = getopt (argc, argv, "n:p:")) != -1){
		switch (c){
			case 'n':
				niveles = atoi(optarg);
			break;
			case 'p':
				procesos = atoi(optarg);
			break;
			default:
			abort ();
			
		}
	}

	creaHijo(niveles,procesos,0);


	return 0;
}
