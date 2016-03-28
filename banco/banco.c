#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define G 20
#define E 10

typedef struct{
    int gen_emp;
    int num;
    int id;
}cajero;

pthread_mutex_t * Gen;
pthread_mutex_t * Emp;

int numGen[G];
int numEmp[E];

int iniEmp,finEmp,iniGen,finGen;

void * operaG(void*p){
    cajero * c;
    c = (cajero*)p;
    int id = (int)p;
    int t = ((rand() % 6)+9);

    if(c->gen_emp == 0)
        printf("cliente general %d\tcajero general %d\t%d segundos\n", c->id, c->num, t);
    else
        printf("cliente general %d\tcajero empresarial %d\t%d segundos\n", c->id, c->num, t);

    sleep(t);
    if(++numGen[c->num]==5){
        printf("Soy el cajero general %d voy a descansar\n",c->num);
        sleep(9);
        numGen[c->num]=0;
    }
    printf("\n");
    if(c->gen_emp == 0){
        printf("Se libero cajero general %d\n\n",c->num);
        pthread_mutex_unlock((Gen+c->num));
    }else{
        printf("Se libero cajero empresarial %d\n\n",c->num);
        pthread_mutex_unlock((Emp+c->num));
    }
}

void * operaE(void*p){
    cajero * c;
    c = (cajero*)p;
    int id = (int)p;
    int t = ((rand() % 6)+9);

    printf("cliente empresarial %d\tcajero empresarial %d\t%d segundos\n", c->id, c->num, t);

    sleep(t);
    if(++numEmp[c->num]==5){
        printf("Soy el cajero empresarial %d voy a descansar\n",c->num);
        sleep(9);
        numEmp[c->num]=0;
    }

    printf("\nSe libero cajero empresarial %d\n\n",c->num);
    pthread_mutex_unlock((Emp+c->num));

}

void atGen(void * p){
    pthread_t* generalesT = (pthread_t*) malloc(G * sizeof(pthread_t));
    pthread_t* aux;
    int llega;
    int lock = -1;
    cajero c[8];
    for(aux = generalesT;aux<(generalesT+G);aux++){  
        lock = -1;
        llega = (rand()%8)+2;
        sleep(llega);
        printf("Llego cliente general %d\n",finGen++);
        while(lock){
            int i=0;
            for(;i<3;i++){
                if(iniEmp == finEmp){
                    if(pthread_mutex_trylock((Emp+i))==0){
                        c[i+5].gen_emp = 1;
                        c[i+5].num = i;
                        c[i+5].id = iniGen++;
                        pthread_create(aux,NULL,operaG, &c[i]);
                        lock = 0;
                        break;
                    }
                }
            }
            i=0;
            if(lock !=0){
                for(;i<5;i++){
                    if(pthread_mutex_trylock((Gen+i))==0){
                        c[i].gen_emp = 0;
                        c[i].num = i;
                        c[i].id = iniGen++;
                        pthread_create(aux,NULL,operaG, &c[i]);
                        lock = 0;
                        break;
                    }
                }
            }
        }
    }
    for(aux = generalesT;aux<(generalesT+G);aux++){
        pthread_join(*aux,NULL);
    }

    free(generalesT);
}

void atEmp(void * p){
    pthread_t* empresarialesT = (pthread_t*) malloc(E * sizeof(pthread_t));
    pthread_t* aux;
    int llega;
    int lock = -1;
    cajero c[3];
    for(aux = empresarialesT;aux<(empresarialesT+E);aux++){  
        lock = -1;
        llega = (rand()%12)+5;
        sleep(llega);
        printf("Llego cliente empresarial %d\n",finEmp++);
        while(lock){
            int i=0;
            for(;i<3;i++){
                if(pthread_mutex_trylock((Emp+i))==0){
                    c[i].gen_emp = 1;
                    c[i].num = i;
                    c[i].id = iniEmp++;
                    pthread_create(aux,NULL,operaE, &c[i]);
                    lock = 0;
                    break;
                }
            }
        }
    }
    for(aux = empresarialesT;aux<(empresarialesT+E);aux++){
        pthread_join(*aux,NULL);
    }

    free(empresarialesT);

}

int main(){
    srand((unsigned)time(NULL));

    Gen = (pthread_mutex_t*)malloc(5*sizeof(pthread_mutex_t));
    Emp = (pthread_mutex_t*)malloc(3*sizeof(pthread_mutex_t));

    pthread_t atiendeGen;
    pthread_t atiendeEmp;

    //pthread_t* generalesT = (pthread_t*) malloc(G * sizeof(pthread_t));
    //pthread_t* empresarialesT = (pthread_t*) malloc(E * sizeof(pthread_t));
    
    //pthread_t* aux;
    pthread_create(&atiendeGen,NULL,atGen,(void*)1);
    pthread_create(&atiendeEmp,NULL,atEmp,(void*)1);
    /*
    int id = 1;
    for(aux = empresarialesT;aux<(empresarialesT+E);aux++,id++){
        pthread_create(aux,NULL,operaE,(void*)id);
    }
    id = 0;
    for(aux = generalesT;aux<(generalesT+G);aux++,id++){
        pthread_create(aux,NULL,operaG,(void*)id);
    }
      
    for(aux = generalesT;aux<(generalesT+G);aux++){
        pthread_join(*aux,NULL);
    }
    for(aux = empresarialesT;aux<(empresarialesT+E);aux++){
        pthread_join(*aux,NULL);
    }
*/
    //free(generalesT);
    //free(empresarialesT);
    pthread_join(atiendeGen, NULL);
    pthread_join(atiendeEmp, NULL);
    free(Gen);
    free(Emp);

    return 0;
}
