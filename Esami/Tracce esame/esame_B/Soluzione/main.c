#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "header.h"


int main() {

	int id_queue, id_shm;
	key_t chiave_shm = IPC_PRIVATE;
	key_t chiave_mbx = IPC_PRIVATE;

	id_shm = shmget(chiave_shm, sizeof(MonitorRisultati), IPC_CREAT|0664);
	id_queue = msgget (chiave_mbx, IPC_CREAT|0664);
	if (id_shm<0||id_queue<0) {
		perror("Errore\n");
		exit(-1);
	}


	MonitorRisultati * ls = (MonitorRisultati *) shmat (id_shm, NULL,0);
	if (ls == (void*)-1) {
		perror ("Errore shmat\n");
		exit(-1);
	}

	// TODO: inizializzare struttura
	init_monitor (&ls->m,2);
	ls->testa=0;
	ls->coda =0;
	ls->elem =0;

	pid_t pid;

	int j;
	for(j=0; j < N_STAMPA ; j++) {
		pid = fork();
		// TODO
		if (pid==0) {
			printf ("Creazione processo stampa con pid°%d\n", getpid());
			stampa (ls);
			exit(0);
		} else if (pid<0) {
			printf ("Creazione stampa n%d fallita\n", j);
			exit(-1);
		}
	}

	
	for(j=0; j < N_FILTRI ; j++) {
		pid = fork();
		// TODO
		if (pid==0) {
			printf ("Creazione processo filtro con pid°%d\n", getpid());
			filtro (ls, id_queue);
			exit(0);
		} else if (pid<0) {
			printf ("Creazione filtro n%d fallita\n", j);
			exit(-1);
		}
	}

	for(j=0; j < N_GENERATORI ; j++) {
		pid = fork();
		// TODO
		if (pid==0) {
			printf ("Creazione processo generatore con pid°%d\n", getpid());
			generazione (id_queue);
			exit(0);
		} else if (pid<0) {
			printf ("Creazione generatore n%d fallita\n", j);
			exit(-1);
		}
	}
	int pid_ex, st;
	int num_processi = N_GENERATORI + N_FILTRI + N_STAMPA;
	// TODO: attendere terminazione processi figli
	for (j=0; j<num_processi; j++) {
		pid_ex = wait(&st);
		if (pid_ex==-1) perror("errore");
    	else printf ("Figlio n° %d terminato con stato %d\n", pid_ex, st); 
	} 

	// TODO: deallocazione strutture
	remove_monitor(&ls->m);
	shmctl (id_shm, IPC_RMID, 0);
	msgctl (id_queue, IPC_RMID, 0);
}





