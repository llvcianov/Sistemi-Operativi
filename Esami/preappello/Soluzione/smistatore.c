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

    pthread_mutex_lock(&(m->mutex));
    while(m->num_scrittori==1)wait(m->cv_lett);
    m->num_lettori=m->num_lettori+1;
    pthread_mutex_unlock(&(m->mutex));
    val = m->buffer;
    pthread_mutex_lock(&(m->mutex));
    m->num_lettori=m->num_lettori+1;
    pthread_mutex_unlock(&(m->mutex));
    
    return val;
}

void scrittura(MonitorLS * m, int valore) {
    
    /* 
        NOTA: C'è un unico scrittore
    */

   pthread_mutex_lock(&(m->mutex));
    while(m->num_lettori>0)wait(m->cv_scritt);
    m->num_scrittori=m->num_scrittori+1;
    pthread_mutex_unlock(&(m->mutex));
    m->buffer = valore;
    pthread_mutex_lock(&(m->mutex));
    m->num_scrittori=m->num_scrittori+1;
    pthread_mutex_unlock(&(m->mutex));

     // TODO: completare scrittura
}

void main() {

	srand(time(NULL));

	int key_coda = ftok(".", 'a');// TODO
    id_coda_sensore = msgget(key_coda,IPC_CREAT | 0664);// TODO

    printf("Avvio processo smistatore...\n");

    pthread_t scrittore;
    pthread_t lettori[LETTORI];

    MonitorLS * m = malloc(sizeof(MonitorLS));// TODO

    // TODO: inizializzare variabili per la mutua esclusione
    pthread_mutex_init(&(m->mutex), NULL);
    pthread_cond_init(&(m->cv_lett), NULL);
    pthread_cond_init(&(m->cv_scritt), NULL);
    m->num_lettori=0;
    m->num_scrittori=0;

    // TODO: creare thread scrittore
    pthread_create(&scrittore, NULL, thread_scrittore, m);

    for(int i=0; i<3; i++) {
    	// TODO: creare thread lettori
        pthread_create(&(lettori[i]), NULL, thread_lettore, m);
    
    }

    // TODO: attendere la terminazione dei thread
    pthread_join(scrittore, NULL);
    
    for(int i = 0; i<3; i++){
        pthread_join(lettori[i], NULL);
    }

	// TODO: deallocare la struttura
    pthread_mutex_destroy(&(m->mutex));
    pthread_cond_destroy(&(m->cv_lett));
    pthread_cond_destroy(&(m->cv_scritt));
    
    free(m);

}

void * thread_lettore(void * x) {

    MonitorLS * ls = x;// TODO: recupero parametri

    for(int i=0; i<10; i++) {

        sleep(1);

        // TODO: leggere il valore, moltiplicarlo per un intero tra 1 e 100 e stamparlo a video
        int valore_old = lettura(ls);
        int valore = valore_old*(rand() % (100) + 1 );

        printf("Lettore: Stampo valore originale = %d e valore finale = %d\n", valore_old, valore);
    }

    pthread_exit(NULL);
}

void * thread_scrittore(void * x) {

    MonitorLS * ls = x; // TODO: recupero parametri

    for(int i=0; i<10; i++) {

        printf("Smistatore: In attesa di messaggi...\n");

        // TODO: ricezione messaggio
        Messaggio  msg;
        msgrcv(id_coda_sensore, &msg, sizeof(long)-sizeof(Messaggio), TIPO, 0);
        
        printf("Scrittore: Ricevuto valore = %d\n", msg.valore);

        // TODO: scrivere il messaggio nel monitor
        scrittura(ls, &(msg.valore));
    }

    pthread_exit(NULL);
}
