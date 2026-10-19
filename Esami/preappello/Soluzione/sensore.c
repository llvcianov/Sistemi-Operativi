#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

void main() {

    printf("Avvio processo sensore...\n");
    
    int key_coda = ftok(".", 'a');// TODO
    int id_coda_sensore = msgget(key_coda,IPC_CREAT | 0664);// TODO

    srand(time(NULL));

    for(int i=0; i<10; i++) {

        // TODO: inviare interi casuali sulla coda
        Messaggio * mess;
        int valore_generato = rand() % (10 + 1);
        mess->valore = valore_generato;
        mess->tipo= TIPO;

        msgsnd(id_coda_sensore, mess, sizeof(long)-sizeof(Messaggio), 0);
        
        sleep(1);
    }

}
