#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"

int main(){

    key_t chiave_sem, chiave_sh;
    int pid, ID_SEM, ID_SH, j;
    struct prodcons * buf;
    
    //ALLOCAZIONE RISORSE
    chiave_sem = IPC_PRIVATE;
    chiave_sh = IPC_PRIVATE;

    ID_SEM = semget(chiave_sem, 4, IPC_CREAT | 0664);
    ID_SH = shmget(chiave_sh, sizeof(struct prodcons), IPC_CREAT | 0664);

    //INIZIALIZZAZIONE RISORSE
    buf = (struct prodcons *) shmat(ID_SH, NULL, 0); //ATTACH ALLA SHARED MEMORY

    buf -> testa = 0; //setto i valori di testa e coda a zero
    buf -> coda = 0;

    semctl(ID_SEM, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
    semctl(ID_SEM, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    semctl(ID_SEM, MUTEX_C, SETVAL, 1);
    semctl(ID_SEM, MUTEX_P, SETVAL, 1);

    srand(time(NULL));


    for(j=0; j<2; j++){

        pid = fork();

        if(pid == 0){

            //figlio produttore
            
            printf("Sono il figlio produttore %d con pid = %d, mio padre ha pid = %d\n", j, getpid(), getppid());

            produttore(buf, ID_SEM);

        exit(0);
        }
    }

    for(j=0; j<2; j++){

        pid = fork();

        if(pid == 0){

            //figlio consumatore
            
            printf("Sono il figlio consumatore %d con pid = %d, mio padre ha pid = %d\n", j, getpid(), getppid());

            consumatore(buf, ID_SEM);

        exit(0);
        }
        
    }

    //JOIN FIGLI-PADRE
    for(j=0; j<(4); j++){
        pid=wait(NULL);
        printf("Figlio con pid = %d terminato\n", pid);
    }

    //DEALLOCAZIONE RISORSE
    shmctl(ID_SH, IPC_RMID, NULL);
    semctl(ID_SEM, 0, IPC_RMID);
    
    
    return 0;
}