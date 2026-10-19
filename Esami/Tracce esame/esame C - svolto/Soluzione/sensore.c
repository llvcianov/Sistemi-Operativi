#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

void main() {

    printf("Avvio processo sensore... PID=%d\n", getpid());
    
    int key_coda = ftok(".", 'a');// TODO
    int id_coda_sensore = msgget(key_coda, 0);// TODO

    srand(time(NULL));
    
    Messaggio m;
    m.tipo = TIPO;

    for(int i=0; i<10; i++) {

        // TODO: inviare interi casuali sulla coda
        m.valore = rand()%10;
        msgsnd(id_coda_sensore, &m, SIZE, 0);
        //printf("Valore %d inviato alla coda\n", m.valore);
        
        sleep(1);
    }

}
