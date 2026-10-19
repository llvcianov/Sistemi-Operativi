#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"

#define DIM 4

#define N_GENERATORI 3
#define N_FILTRI 3
#define N_STAMPA 3

#define PROD 0
#define CONS 1

#define SIZE_MESS sizeof(Messaggio)-sizeof(long)

#define TIPO_MESS 1

typedef struct {
	int buffer[DIM];
	
	// TODO: inserire i campi necessari alla gestione della coda circolare
	int contatore; //conta lo spazio disponibile nella coda circolare
	int testa;
	int coda;
	
	Monitor m;
} MonitorRisultati;


void inserisci_risultato(MonitorRisultati * ls, int valore);
int stampa_risultati(MonitorRisultati * ls);

typedef struct {
	
	// TODO: inserire i campi che costituiscono il messaggio da inviare
	long type;
	int valore;
	
} Messaggio;

void filtro(MonitorRisultati * ls, int coda);
void generazione(int coda);
void stampa(MonitorRisultati * ls);

#endif
