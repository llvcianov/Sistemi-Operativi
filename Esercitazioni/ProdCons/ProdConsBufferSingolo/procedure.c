#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void produttore(int * Buffer, int ID_SEM){

    printf("Produttore con pid %d e' in attesa...\n", getpid());
    
    Wait_Sem(ID_SEM, SPAZIO_DISPONIBILE);

    printf("Produttore con pid %d sbloccato...\n", getpid());

    *Buffer = 5;

    printf("Produttore ha prodotto 5\n");

    Signal_Sem(ID_SEM, MESSAGGIO_DISPONIBILE);

}


void consumatore(int * Buffer, int ID_SEM){

    int valore = 5;

    printf("Consumatore con pid %d e' in attesa...\n", getpid());
    
    Wait_Sem(ID_SEM, MESSAGGIO_DISPONIBILE);

    printf("Consumatore con pid %d sbloccato...\n", getpid());

    valore = * Buffer;

    printf("Consumatore ha consumato 5\n");

    Signal_Sem(ID_SEM, SPAZIO_DISPONIBILE);

}

