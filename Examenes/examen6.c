#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>

int t = 3, loop = 1;
int numc;
int numz;
pid_t pid;

void control_alarm(int signal){
  printf("Aparezco cada %d segundos\n", t);
  int res = alarm(t);
}

void control_ctrlc(int signal){
  ++t;
  ++numc;
  int res = alarm(t);
}

void control_ctrlz(int signal){
  if(t > 1)
  --t;
  ++numz;
  int res = alarm(t);
}

void control_sigusr(int signal){
  loop = 0;
  printf("\nSe ha pulsado %d Ctrl+C y se ha pulsado %d veces Ctrl+Z\n", numc, numz);
  kill(pid, SIGKILL);
  raise(SIGKILL);
}

int main(int argc, char *argv[]){
  struct sigaction gest;
  int err;
  
  pid = fork();

  if(pid == 0){
    printf("Pid: %d\nPpid it's %d\n", getpid(), getppid());
    printf("Durmiendo 10 segundos\n");
    
    gest.sa_handler = SIG_IGN;
    gest.sa_flags = SA_RESTART;
    err = sigaction(SIGINT, &gest, 0);
    
    gest.sa_handler = SIG_IGN;
    gest.sa_flags = SA_RESTART;
    err = sigaction(SIGTSTP, &gest, 0);

    sleep(10);
    kill(getppid(), SIGUSR1);
  }else{
    gest.sa_handler = control_alarm;
    gest.sa_flags = SA_RESTART;
    err = sigaction(SIGALRM, &gest, 0);
    alarm(t);
    
    gest.sa_handler = control_ctrlc;
    gest.sa_flags = SA_RESTART;
    err = sigaction(SIGINT, &gest, 0);
    
    gest.sa_handler = control_ctrlz;
    gest.sa_flags = SA_RESTART;
    err = sigaction(SIGTSTP, &gest, 0);
    
    gest.sa_handler = control_sigusr;
    gest.sa_flags = SA_ONESHOT;
    err = sigaction(SIGUSR1, &gest, 0);
    
    while(loop);
    wait(NULL);
  }

  return 0;
}
