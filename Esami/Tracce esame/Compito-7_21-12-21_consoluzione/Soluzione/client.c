#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"


int main(int argc, char *argv[]){
	int coda;
	pid_t pid;
	long id_sensore;
        
	if (argc < 2 ) {
		printf("ERRORE: il client deve ricevere il proprio ID\n");
		return -1;
	}
        
	id_sensore = atol(argv[1]);
       
	key_t key;
	key = ftok(".", 'a');//TODO:inserire la chiave
    
	coda = msgget(key, 0);//TODO:inizializzare la coda

	printf("[DEBUG] - sensore id coda %d\n",coda);	
	printf("[Client %d] - invio richieste...\n",getpid());


	int i = 0;
	Misura misura;	

	srand(time(NULL));
	
	// TODO: inviare in cilco NUM_REQ misure da inviare al server tramite coda
	misura.id_client = id_sensore;
	
	for(i=0; i<NUM_REQ; i++){
	
		misura.misura=rand()%100;
		msgsnd(coda, &misura, SIZE_MESS, 0);
	}

	printf("[Client %d] - Fine processo\n",getpid());

	return 0;
}
