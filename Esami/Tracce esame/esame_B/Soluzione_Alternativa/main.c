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
	key_t chiave_shm = IPC_PRIVATE;// TODO
	key_t chiave_mbx = IPC_PRIVATE;// TODO

	id_shm = shmget(chiave_shm, sizeof(MonitorRisultati), IPC_CREAT | 0664);// TODO
	id_queue = msgget(chiave_mbx, IPC_CREAT | 0664);// TODO
	printf("Strutture allocate\n");


	MonitorRisultati * ls = shmat(id_shm, NULL ,0);// TODO

	// TODO: inizializzare struttura
	init_monitor(&(ls->m), 2);
	ls->contatore = DIM;
	ls->testa = 0;
	ls-> coda = 0;
	printf("Monitor inizializzato\n");
	
	pid_t pid;

	int j;
	for(j=0; j < N_STAMPA ; j++) {
		
		// TODO
		pid = fork();
		if(pid==0){
			printf("Sono il processo STAMPA %d\n", getpid());
			stampa(ls);
			exit(0);
		}
	}
	

	
	for(j=0; j < N_FILTRI ; j++) {
		
		// TODO
		pid=fork();
		if(pid==0){
			printf("Sono il processo FILTRO %d\n", getpid());
			filtro(ls, id_queue);
			exit(0);
		}
	}
	

	for(j=0; j < N_GENERATORI ; j++) {
	
		// TODO
		pid=fork();
		if(pid==0){
			printf("Sono il processo GENERATORE %d\n", getpid());
			generazione(id_queue);
			exit(0);
		}
	}
	
	sleep(2);

	// TODO: attendere terminazione processi figli
	for(j=0; j < N_GENERATORI + N_FILTRI + N_STAMPA; j++){
		pid=wait(NULL);
		printf("Processo %d terminato\n", pid);
	}

	// TODO: deallocazione strutture
	remove_monitor(&(ls->m));
	printf("Monitor rimosso\n");
	
	shmctl(id_shm, IPC_RMID, 0);
	msgctl(id_queue, IPC_RMID, 0);
	printf("Strutture deallocate\n");
	
	return(0);

}





