#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TCP_PORT 8000

int recompilacion();
void intervalos();
int enviar(int * datos,int n);

int cliente;
int leidos, escritos;
char buffer[1000];

int main(int argc, const char * argv[]) {
	struct sockaddr_in direccion;

	if (argc != 2) {
		printf("Error. Use: %s A.B.C.D \n", argv[0]);
		exit(-1);
	}
	
	//Crear el socket
	cliente = socket(PF_INET, SOCK_STREAM, 0);
	
	// Establecer conexión
	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family = AF_INET;
	inet_aton(argv[1], &direccion.sin_addr);
	int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
	
	// Comunicación
	if (estado == 0) {
		printf("Conectado a %s:%d \n",
		inet_ntoa(direccion.sin_addr),
		ntohs(direccion.sin_port));
		// Leer de teclado y escribir en socket
		int acaba = 1;
		while(acaba){
			acaba = recompilacion();
		}
	}

	// Cerrar el socket
	close(cliente);
	return 0;
}

int recompilacion(){
	int acaba=0;

	srand(time(NULL));
	int * datos = (int *) malloc(sizeof(int));
	int r = (rand() % 6) + 3;
	int i = 0;
	for(;i<r;i++){
		sleep(1);
		datos = (int *)realloc(datos,(i+5));
		int d = rand() % 5;
		*(datos+i) = d;	
		if(d != 0)
			acaba=1;
	}
	enviar(datos,r);	
	free(datos);

	return acaba;
}
void intervalos(){

}
int enviar(int * datos,int n){
	int i = 0;
	for(;i<n;i++){
		int num;
		//leidos = read(fileno(stdin), &buffer, sizeof(buffer));
		num = *(datos+i);
		write(cliente, &buffer, *(datos+i));
		printf("Enviando %d\n",num);
		leidos = read(cliente, &buffer, sizeof(buffer));
	}

}
