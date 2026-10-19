#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>


void produttore(int coda, char testo[]) {

	Messaggio m;
	m.tipo = 1;
	strcpy(m.testo_messaggio, testo);
	SendSync(coda, m);
	printf("Messaggio inviato: %s \n", m.testo_messaggio);
	
}
	
	
void consumatore(int coda){

	Messaggio m;
	ReceiveSync(coda, &m);
	printf("Messaggio ricevuto: %s \n", m.testo_messaggio);
}
 

void SendSync(int coda, Messaggio m) {
 	
	Messaggio prova;
	prova.tipo = 2;
	msgsnd(coda, (void*)&prova, SYZE, IPC_NOWAIT);
	msgrcv(coda, NULL, SYZE, 2 , 0);
	msgsnd(coda, (void*)&m, SYZE, IPC_NOWAIT);
	
}


void ReceiveSync(int coda, Messaggio* m) {

	Messaggio prova;
	prova.tipo = 2;
	msgrcv(coda, NULL, SYZE, 2 , 0);
	msgsnd(coda, (void*)&prova, SYZE, IPC_NOWAIT);
	msgrcv(coda, (void*)m, SYZE, 1 , 0);
	
	 
}
 
 
	

