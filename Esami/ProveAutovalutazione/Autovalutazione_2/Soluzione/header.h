#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"

#define N_GENERATORI 3
#define N_CALCOLATORI 3
#define N_PRINTERS 3

// TODO DEFINIRE MACRO DI SUPPORTO
#define SOMMA 1
#define PRODOTTO 2
#define DIVISIONE 3

#define COND_SCRITT 1
#define COND_LETT 0

struct MonitorRisultati {
	//TODO riempire struttura
	int num_scrittori;
	int num_lettori;
	float risultati[3];
	Monitor m;
};


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione);
float* leggi_risultati(struct MonitorRisultati * ls);

typedef struct {
	// TODO DEFINIRE TIPO MESSAGGIO
	long type;
	float valore;
} Messaggio;

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox);
void generazione(int operazione, int mailbox);
void printer(struct MonitorRisultati * ls);

#endif
