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


void produttore(struct prodcons * buf, int ID_SEM){

    int value;

    printf("Produttore con pid %d in attesa, un consumatore sta consumando...\n", getpid());
    
    Wait_Sem(ID_SEM, SPAZIO_DISPONIBILE);

    printf("Spazio disponibile...\n");
    
    printf("Produttore con pid %d in attesa, un altro produttore sta producendo...\n", getpid());
    
    Wait_Sem(ID_SEM, MUTEX_P);

    sleep(2);
    
    value =  (1+rand()%100); //genero valore random
    
    printf("Produttore con pid %d sbloccato...\n", getpid());

    buf -> buffer[buf -> testa] = value;

    printf("valore prodotto = %d\n", value);

    buf -> testa = (buf -> testa + 1) % DIM_BUFFER;

    Signal_Sem(ID_SEM, MUTEX_P);

    Signal_Sem(ID_SEM, MESSAGGIO_DISPONIBILE);

}


void consumatore(struct prodcons * buf, int ID_SEM){

    int value;

    printf("Consumatore con pid %d in attesa, un produttore sta producendo...\n", getpid());
    
    Wait_Sem(ID_SEM, MESSAGGIO_DISPONIBILE);

    printf("Messaggio disponibile...\n");
    
    printf("Consumatore con pid %d in attesa, un altro consumatore sta consumando...\n", getpid());
    
    Wait_Sem(ID_SEM, MUTEX_C);

    sleep(2);

    printf("Consumatore con pid %d sbloccato...\n", getpid());

    value = buf -> buffer[buf -> coda];

    printf("valore consumato = %d\n", value);

    buf -> coda = (buf -> coda + 1) % DIM_BUFFER;

    Signal_Sem(ID_SEM, MUTEX_C);

    Signal_Sem(ID_SEM, SPAZIO_DISPONIBILE);




}