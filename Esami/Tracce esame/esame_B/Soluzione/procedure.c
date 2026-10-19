#include "header.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


int stampa_risultati(MonitorRisultati * ls) {

	int risultato;

	// TODO: consumo il valore
	enter_monitor (&ls->m);
	if (ls->elem == 0) wait_condition  (&ls->m, CONS);
	printf ("Consumo dal buffer in posizione %d\n", ls->coda);
	risultato = ls->buffer[ls->coda];
	ls->coda=(ls->coda+1)%DIM;
	ls->elem--;
	signal_condition(&ls->m, PROD);
	leave_monitor (&ls->m);

	return risultato;

}


void inserisci_risultato(MonitorRisultati * ls, int valore) {

	// TODO: produco il valore
	enter_monitor (&ls->m);
	if (ls->elem == DIM) wait_condition  (&ls->m, PROD);
	printf ("Scrittura nel buffer in posizione %d\n", ls->testa);
	ls->buffer[ls->testa] = valore;
	ls->testa=(ls->testa+1)%DIM;
	ls->elem++;
	signal_condition(&ls->m, CONS);
	leave_monitor (&ls->m);
}

void filtro(MonitorRisultati * ls, int coda){
	Messaggio m;
	int valore = 0;
	for (int i = 0 ; i < 4; i++){
		int ret = msgrcv (coda, (void *)&m, sizeof(Messaggio)-sizeof(long), 0, 0);
		if (ret<0) {
			perror ("Errore invio messaggio\n");
			exit(-1);
		}
		
		// TODO: filtro i valori prelevati dalla mailbox: se sono pari, li inserisco, altrimenti inserisco 0
		if (m.valore%2 == 0) {
			printf ("Messaggio ricevuto pari ... scrivo nel buffer %d\n", m.valore);
			inserisci_risultato (ls,m.valore);
		} else {
			printf ("Messaggio (%d) è dispari ... scrivo nel buffer 0\n", m.valore);
			inserisci_risultato (ls,0);
		}
		sleep(2);
	}
}
void generazione(int coda) {
	srand(time(NULL));
	Messaggio m;
	sleep(2);
	for (int i = 0 ; i < 4; i++) {
		// TODO: genero dei numeri casuali tra 1 e 20 e li invio alla mailbox
		m.tipo = MESSAGGIO;
		m.valore = rand()%20 +1;
		int ret = msgsnd (coda, (void *)&m, sizeof(Messaggio)-sizeof(long), 0);
		if (ret<0) {
			perror ("Errore invio messaggio\n");
			exit(-1);
		}
		printf ("Messaggio di valore %d inviato...\n", m.valore);
		sleep(2);
	}
}
void stampa(MonitorRisultati * ls) {
	int val;
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: stampo il valore appena consumato
		val = stampa_risultati (ls);
		printf("[%d] Ho letto il valore: %d \n", getpid(), val);
	}
}
