#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "semafori.h"
#include "procedure.h"

int main(){

    key_t pid;
    int i;
    key_t chiaveSH, chiaveSEM;
    int ID_SH, ID_SEM;
    int*  Buffer;
    
    
    chiaveSH = IPC_PRIVATE;
    chiaveSEM = IPC_PRIVATE;

    ID_SH = shmget(chiaveSH, sizeof(int), IPC_CREAT | 0664); //ALLOCO LA SHARED MEMORY
    ID_SEM = semget(chiaveSEM, 2, IPC_CREAT | 0664); //ALLOCO IL SEMPHOR SET
    printf("Shared memory allocata con ID %d. SemaphorSet allocato con ID %d\n", ID_SH, ID_SEM);

    //collegamento alla shared memory
    Buffer = (int*) shmat(ID_SH, 0, 0);

    //SETTO IL SEMAPHOR SET
    semctl(ID_SEM, SPAZIO_DISPONIBILE, SETVAL, 1);
    semctl(ID_SEM, MESSAGGIO_DISPONIBILE, SETVAL, 0);

    pid = fork();

    if(pid==0){

        //codice figlio produttore
        
        printf("Sono il figlio produttore con pid = %d, mio padre ha pid %d\n", getpid(), getppid());

        produttore(Buffer, ID_SEM);

        exit(0);

    } else {

        pid = fork();

        if(pid==0){

            //codice figlio consumatore
            printf("Sono il figlio consumatore con pid = %d, mio padre ha pid %d\n", getpid(), getppid());

            consumatore(Buffer, ID_SEM);

        exit(0);
        
        }
    }



    for(i=0; i<2; i++){
        pid = wait(NULL);
        printf("Il figlio con pid %d è terminato\n", pid);
    }

    shmctl(ID_SH, IPC_RMID, NULL); //DEALLOCO LA SHARED MEMORY
    semctl(ID_SEM, 0, IPC_RMID); // DEALLOCO IL SEMAPHOR SET
    printf("Shared memory e semaphor set deallocati\n");

    return 0;
}
