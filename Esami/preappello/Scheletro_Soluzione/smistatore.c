#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <pthread.h>

void * thread_lettore(void *);
void * thread_scrittore(void *);

// Variabile globale
int id_coda_sensore;

int lettura(MonitorLS * m) {

    /* 
        NOTA: C'è un unico scrittore
    */
     
    int val;

    // TODO: completare lettura
    
    return val;
}

void scrittura(MonitorLS * m, int valore) {
    
    /* 
        NOTA: C'è un unico scrittore
    */

    // TODO: completare scrittura
}

void main() {

	srand(time(NULL));

	int key_coda = // TODO
    id_coda_sensore = // TODO

    printf("Avvio processo smistatore...\n");

    pthread_t scrittore;
    pthread_t lettori[LETTORI];

    MonitorLS * m = // TODO

    // TODO: inizializzare variabili per la mutua esclusione

    // TODO: creare thread scrittore

    for(int i=0; i<3; i++) {
    	// TODO: creare thread lettori
    }

    // TODO: attendere la terminazione dei thread

	// TODO: deallocare la struttura

}

void * thread_lettore(void * x) {

    MonitorLS * ls = // TODO: recupero parametri

    for(int i=0; i<10; i++) {

        sleep(1);

        // TODO: leggere il valore, moltiplicarlo per un intero tra 1 e 100 e stamparlo a video

        printf("Lettore: Stampo valore originale = %d e valore finale = %d\n", valore_old, valore);
    }

    pthread_exit(NULL);
}

void * thread_scrittore(void * x) {

    MonitorLS * ls = // TODO: recupero parametri

    for(int i=0; i<10; i++) {

        printf("Smistatore: In attesa di messaggi...\n");

        // TODO: ricezione messaggio
        
        printf("Scrittore: Ricevuto valore = %d\n", msg.valore);

        // TODO: scrivere il messaggio nel monitor
    }

    pthread_exit(NULL);
}
