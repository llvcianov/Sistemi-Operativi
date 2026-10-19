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


int main(){
	
	int ID_coda, stato, j;
	pid_t PID;
	
	//CREAZIONE CODA
	ID_coda = msgget(IPC_PRIVATE, IPC_CREAT | 0664);

	//GENERAZIONE PROCESSI
	PID = fork();
	
	if(PID==0) {
	
			printf("Sono il figlio produttore, con PID = %d \n", getpid());
					
			sleep(2);
					
			produttore(ID_coda, "ciao");
				
			exit(0);
		
	} else {
		
			PID = fork();
				
			if(PID==0) {
					
					printf("Sono il figlio consumatore, con PID = %d \n", getpid());  
							
					sleep(1);
							
					consumatore(ID_coda);
							
					exit(0);
							
			}
					
	}
	
	
	//ATTESA DI TERMINAZIONE
	
	for (j = 0; j < 2; j++) {
	
			PID = wait(&stato);
			
			if (PID==-1) {
			
					perror("errore");
					
			} else {
			
					printf("Il figlio con PID %d e' morto con stato = %d \n", PID, stato);
					
			}
			
	}
	
	//DEALLOCAZIONE CODA
	
	msgctl(ID_coda, IPC_RMID, 0);
	
	return 1;
	
}
	
			
	
	
			
			
				
						
				
				
		
			
		
	
		
	
		
		
