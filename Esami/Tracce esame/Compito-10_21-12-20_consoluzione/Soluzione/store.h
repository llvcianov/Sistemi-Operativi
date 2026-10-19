#ifndef HEADERM_H
#define HEADERM_H

#include "header.h"

#define SCORTA_INIZIALE 20

#define MUTEXL_1 0
#define SYNCH_1 1
#define MUTEXL_2 2
#define SYNCH_2 3
#define MUTEXL_3 4
#define SYNCH_3 5

typedef struct {
    // TODO aggiungere le variabili necessarie alla sincronizzazione
	int chiave_sem;
	//chiave_sem = ftok(".", 'd');
    int id_sem;
    //id_sem = semget(chiave_sem, 6, IPC_CREAT | 0664);
    
    int key_queue_request /*= ftok(".", 'a')*/;
    int key_queue_response /*= ftok(".", 'b')*/;
    //ds_queue_request = msgget(key_queue_request, IPC_CREAT | 0664);
    //ds_queue_response = msgget(key_queue_response, IPC_CREAT | 0664);
    
    int num_lettori_1;
    int num_lettori_2;
    int num_lettori_3;
    int scorta[MAX_PRODOTTI];
}Magazzino;


void init_magazzino(Magazzino *magazzino);
void destroy_magazzino(Magazzino *magazzino);

void lettore(Magazzino *magazzino);
void scrittore(Magazzino *magazzino);

void InizioLettura(Magazzino *magazzino, int id_prodotto);
void FineLettura(Magazzino *magazzino, int id_prodotto);
void InizioScrittura(Magazzino *magazzino, int id_prodotto);
void FineScrittura(Magazzino *magazzino, int id_prodotto);



#endif
