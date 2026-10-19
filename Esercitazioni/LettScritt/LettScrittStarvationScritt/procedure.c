#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "procedure.h"
#include "semafori.h"


void Lettore(int ID_SEM, Buffer* buf){

    msg valore;

    //inizio lettura

    Wait_Sem(ID_SEM, MUTEXL);
    
    (buf -> numlettori) = (buf -> numlettori+1);

    if(buf -> numlettori == 1) Wait_Sem(ID_SEM, SYNCH);

    valore = (buf -> messaggio);

    printf("Valore letto dal lettore %d = %ld\n", getpid(), valore);
    
    Signal_Sem(ID_SEM, MUTEXL);

    //fine lettura

    Wait_Sem(ID_SEM, MUTEXL);

    (buf -> numlettori) = (buf -> numlettori-1);

    if(buf -> numlettori == 0) Signal_Sem(ID_SEM, SYNCH);

    Signal_Sem (ID_SEM, MUTEXL);

}


void Scrittore(int ID_SEM,Buffer* buf){

    msg valore;

    valore = rand()%100;

    Wait_Sem(ID_SEM, SYNCH);

    buf -> messaggio = valore;

    printf("Valore scritto dallo scrittore %d = %ld\n", getpid(), valore);
    
    Signal_Sem(ID_SEM, SYNCH);

}
