#include "header.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


float* leggi_risultati(struct MonitorRisultati * ls) {

	float* risultati = (float*)malloc(sizeof(float)*3);//TODO completare 


	printf("[%d] Lettura - ingresso monitor\n", getpid());
	enter_monitor(&(ls->m));
	if(ls->num_scrittori > 0)wait_condition(&(ls->m), COND_LETT);
	ls->num_lettori++;
	signal_condition(&(ls->m), COND_LETT);
	leave_monitor(&(ls->m));

	// TODO lettura
	for(int i = 0; i<3; i++){
		risultati[i]=ls->risultati[i];
	}

	printf("[%d] Lettura - uscita monitor\n", getpid());
	enter_monitor(&(ls->m));
	ls->num_lettori--;
	if(ls->num_lettori == 0)signal_condition(&(ls->m), COND_SCRITT);
	leave_monitor(&(ls->m));
	
	return risultati;
	
}


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione) {

	// TODO scrittura
	
	printf("[%d] Scrittura - ingresso monitor\n", getpid());
	enter_monitor(&(ls->m));
	if(ls->num_scrittori > 0 || ls->num_lettori > 0)wait_condition(&(ls->m), COND_SCRITT);
	ls->num_scrittori++;
	leave_monitor(&(ls->m));
	
	printf("[%d] Scrittura - valore [%f] operazione %d\n", getpid(),valore, operazione);
	switch(operazione){
		case 1:
			ls->risultati[0] = valore;
			break;
		case 2:
			ls->risultati[1] = valore;
			break;
		case 3:
			ls->risultati[2] = valore;
			break;
	}

	printf("[%d] Scrittura - uscita monitor\n", getpid());
	enter_monitor(&(ls->m));
	ls->num_scrittori--;
	if(queue_condition(&(ls->m),COND_SCRITT)){
	
		signal_condition(&(ls->m), COND_SCRITT);
	} else {
	
		signal_condition(&(ls->m), COND_LETT);
	}
	
	leave_monitor(&(ls->m));
	
}

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox){
	// TODO completa
	Messaggio msg;
	float buffer[4];
	float risultato = 0;
	
	for(int i = 0; i<4; i++){
	
		msgrcv(mailbox, (void*)&msg, sizeof(Messaggio)-sizeof(long), operazione, 0);
		printf("Processo %d (%d) ha prelevato valore: %f dalla mailbox\n", getpid(), operazione, msg.valore);
		buffer[i]=msg.valore;
		
		
		if(i==1 || i==3){
		
			switch(operazione){
			
				case 1:
					risultato = buffer[i-1]+buffer[i];
					printf("Operazione somma completata dal processo calcolo %d (%d)\n", getpid(), operazione);
					printf("Risultato: %f\n", risultato);
					sleep(1);
					inserisci_risultato(ls, risultato, operazione);
					
					break;
				
				case 2:
					sleep(1);
					risultato = buffer[i-1]*buffer[i];
					printf("Operazione prodotto completata dal processo calcolo %d (%d)\n", getpid(), operazione);
					inserisci_risultato(ls, risultato, operazione);
					printf("Risultato: %f\n", risultato);
					break;
					
				case 3:
					sleep(2);
					risultato = buffer[i-1]/buffer[i];
					printf("Operazione divisione completata dal processo calcolo %d (%d)\n", getpid(),operazione);
					inserisci_risultato(ls, risultato, operazione);
					printf("Risultato: %f\n", risultato);
					break;
				
					
			}
		}
	}
}

void generazione(int operazione, int mailbox) {
	srand(time(NULL));
	// TODO completa
	Messaggio msg;

	for(int i = 0; i<4; i++){

		float operando = (float)rand()/(float)(RAND_MAX) * 20;
		msg.valore = operando;
		msg.type = operazione;
		msgsnd(mailbox, (void*)&msg, sizeof(Messaggio)-sizeof(long), 0);
		printf("Processo %d (%d) ha inviato valore: %f alla mailbox\n", getpid(), operazione, msg.valore);
	}
}
void printer(struct MonitorRisultati * ls) {
	float* risultati;
	for (int i = 0 ; i < 6; i++) {
		sleep(2);
		risultati = leggi_risultati(ls);
		printf("[%d] Risultati 1: %f, 2: %f, 3: %f\n",getpid(), risultati[0], risultati[1], risultati[2]);
		//TODO COMPLETA DEALLOCAZIONE risultati
		free(risultati);
	}
}
