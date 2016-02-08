#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,const char * argv[]){
	
	char * cvalue = NULL;
	char numero[256];
	int c;
	
	c = getopt (argc, argv, "n:");

	if(c=='n'){
		pid_t pid, wpid;

		cvalue = optarg;

		int num = atoi(cvalue);
		int status = 0;

		int i = 0;
		for(;i<num;i++){
			pid = fork();
			if(pid == -1){
				printf("Error al crear el hijo\nSe crearon %d hijos",i);
				break;
			}else if(pid == 0){
				double promedio = (getpid() + getppid())/2.0;
				printf("Hijo: %i\t Pid: %i\t PPid: %i\t Promedio: %f\n",i,getpid(),getppid(),promedio);//(getpid()+getppid())/2);
				exit(promedio);
			}else{						
				waitpid(pid,&status,0);
				//if(waitpid(pid,&status,0) != 0){
					//if(WIFEXITED(status)){
						//printf("Ya acabo el hijo %d con promedio %d\n",i,WEXITSTATUS(status));
					//}
				//}
			}
		}
		i = 0;
		//for(;i<num;i++){
		//	waitpid(pid,&status,0);
		//}
			
		printf("Ya acabaron todos los hijos y va a acabar de manera satisfactoria\n");

	}else{
		printf("Use el parametro -n 'x' para indicar cuantos hijos quiere\n");
	}

	return 0;
}
