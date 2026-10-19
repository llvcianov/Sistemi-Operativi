#include "header.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


int stampa_risultati(MonitorRisultati * ls) {

	int risultato;

	// TODO: consumo il valore
	enter_monitor(&(ls->m));
	if(ls->contatore==DIM)wait_condition(&(ls->m), CONS);
	risultato = ls->buffer[ls->coda];
	ls->coda = (ls->coda+1)%DIM;
	ls->contatore = ls->contatore + 1;
	signal_condition(&(ls->m), PROD);
	leave_monitor(&(ls->m));
	

	return risultato;
	

}


void inserisci_risultato(MonitorRisultati * ls, int valore) {

	// TODO: produco il valore
	enter_monitor(&(ls->m));
	if(ls->contatore==0)wait_condition(&(ls->m), PROD);
	ls->buffer[ls->testa] = valore;
	ls->testa = (ls->testa+1)%DIM;
	ls->contatore = ls->contatore - 1;
	signal_condition(&(ls->m), CONS);
	leave_monitor(&(ls->m));
}

void filtro(MonitorRisultati * ls, int coda){
	Messaggio m;
	int valore = 0;
	for (int i = 0 ; i < 4; i++){
	
		
		// TODO: filtro i valori prelevati dalla mailbox: se sono pari, li inserisco, altrimenti inserisco 0
		msgrcv(coda, &m, SIZE_MESS, TIPO_MESS, 0);
		valore = m.valore;
		printf("Processo %d ha prelevato valore %d dalla mailbox\n", getpid(), valore);
		if(valore%2 == 0){
			inserisci_risultato(ls, valore);
			printf("Valore %d inserito nel monitor\n", valore);
		} else {
			valore = 0;
			printf("Valore %d inserito nel monitor\n", valore);
			inserisci_risultato(ls, valore);
		}
	}
}

void generazione(int coda) {
	srand(time(NULL));
	Messaggio m;
	
	m.type = TIPO_MESS;
	sleep(2);
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: genero dei numeri casuali tra 1 e 20 e li invio alla mailbox
		m.valore = rand()%(20+1);
		msgsnd(coda, &m, SIZE_MESS, 0);
		printf("Processo %d ha inviato valore %d alla mailbox\n", getpid(), m.valore);
	}
}
void stampa(MonitorRisultati * ls) {
	int val;
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: stampo il valore appena consumato
		sleep(1);
		val = stampa_risultati(ls);
		
		printf("[%d] Ho letto il valore: %d \n", getpid(), val);
	}
}
