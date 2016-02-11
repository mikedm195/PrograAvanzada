#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
	int n;
	char * p = NULL;
	int c;
	pid_t pid;
	while ((c = getopt (argc, argv, "n:p:")) != -1){
		switch (c)
		{
			case 'n':
				n = atoi(optarg);
			break;
			case 'p':
				p = optarg;
			break;
			default:
				abort ();
		}
	}
	int i = 0;
	for(;i<n;i++)
		system(p);
}
