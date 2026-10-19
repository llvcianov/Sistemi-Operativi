#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "procedure.h"


int main(){

    key_t chiave_sem, chiave_sh, pid;
    int ID_SH, ID_SEM, i;
    Buffer* buf;

    chiave_sem = IPC_PRIVATE;
    chiave_sem = IPC_PRIVATE;


    ID_SH = shmget(chiave_sh, sizeof(Buffer), IPC_CREAT | 0664);
    buf = (Buffer*)shmat(ID_SH, 0, 0);

    ID_SEM = semget(chiave_sem, 2, IPC_CREAT | 0664);
    semctl(ID_SEM, MUTEXL, SETVAL, 1);
    semctl(ID_SEM, SYNCH, SETVAL ,1);

    buf -> numlettori = 0;
    buf -> messaggio = 0;

    for(i=0; i<10; i++){

        pid=fork();

        if(pid == 0){

            if((i%2) == 0){

                //codice scrittori
                printf("Sono lo scrittore con pid = %d, mio padre ha pid %d\n", getpid(), getppid());

                Scrittore(ID_SEM, buf);

            } else {

                //codice lettori
                printf("Sono il lettore con pid = %d, mio padre ha pid %d\n", getpid(), getppid());

                Lettore(ID_SEM, buf);

            }

            exit(0);
        }
    }


    for(i=0; i<(10); i++){
        pid = wait(NULL);
        printf("Figlio con pid = %d terminato\n", pid);
    }

    
    
    shmctl(ID_SH, IPC_RMID, NULL);
    semctl(ID_SEM, 0, IPC_RMID);
    
    
    return 0;
}

