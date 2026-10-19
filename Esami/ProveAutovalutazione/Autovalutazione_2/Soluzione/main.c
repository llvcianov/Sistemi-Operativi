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
	key_t chiave_shm = IPC_PRIVATE;// TODO definire chiavi;
	key_t chiave_mbx = IPC_PRIVATE;//

	id_shm = shmget(chiave_shm, sizeof(struct MonitorRisultati), IPC_CREAT | 0664);// TODO OTTENERE RISORSE
	id_queue = msgget(chiave_mbx, IPC_CREAT | 0664);//

	if( id_shm < 0 || id_queue < 0) {
		perror("errore creazione risorse");
		exit(1);
	}

	struct MonitorRisultati * ls = shmat(id_shm, NULL, 0);//TODO ottenere riferimento al monitor

	init_monitor( &(ls->m), 2 );

	// TODO inizializzare risorse
	ls -> num_scrittori = 0;
	ls -> num_lettori = 0;
	for(int i = 0; i<3; i++){
		ls->risultati[i]=-1;
	}

	pid_t pid;

	int j;
	for(j=0; j < N_PRINTERS ; j++) {
		// TODO creare processi printer
		pid = fork();
		if (pid == 0){
		
			printf("Sono il processo printer %d\n", getpid());
			printer(ls);
			exit(0);
		}
	}
	
	sleep(1);
	
	for(j=0; j < N_CALCOLATORI ; j++) {
		// TDO creare processi calcolatori
		pid = fork();
		if (pid == 0){
		
			printf("Sono il processo calcolo %d\n", getpid());
			sleep(3);
			calcolo(ls,j+1,id_queue);
			exit(0);
		}
	}
	
	sleep(1);

	for(j=0; j < N_GENERATORI ; j++) {
		// TODO creare processi generatori
		pid = fork();
		if (pid == 0){
			
			printf("Sono il processo generatore %d\n", getpid());
			generazione(j+1, id_queue);
			exit(0);
		}
	}

	sleep(8);

	for(j=0; j<N_CALCOLATORI+N_GENERATORI+N_PRINTERS; j++) {
		// TODO JOIN
		pid = wait(NULL);
		printf("Processo %d terminato\n", pid);
	}
	
	
	// TODO REMOVE RESOUCES
	remove_monitor(&(ls->m));
	
	shmctl(id_shm, IPC_RMID, 0);
	msgctl(id_queue, IPC_RMID, 0);
	
	return 0;
}





