#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#include "header.h"


int main(){
	pid_t pid_ex,pid;
	int st,i;
	int shmid,semid;
	BufferMutuaEx* buf;

	key_t key_shm,key_sem;
	key_shm = IPC_PRIVATE; // TODO 
	key_sem = IPC_PRIVATE;// TODO 

	shmid = shmget(key_shm, sizeof(BufferMutuaEx), IPC_CREAT | 0664);// TODO 
	semid = semget(key_sem, 4, IPC_CREAT | 0664);// TODO 
	
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO: inizializzare semafori
	semctl(semid, SPAZIO_DISPONIBILE, SETVAL, DIM);
	semctl(semid, MESS_DISPONIBILE_1, SETVAL, 0);
	semctl(semid, MESS_DISPONIBILE_2, SETVAL, 0);
	semctl(semid, MUTEXP, SETVAL, 1);
	

	buf = (BufferMutuaEx *)shmat(shmid, NULL, 0);// TODO 
	
	// TODO: inizializzazione della struttura
	for(i = 0; i < DIM; i++){
		buf->stato[i] = LIBERO;
	}
	
	srand(time(NULL));

	for(i = 0; i < NPROD; i++){
		pid = fork();
		
		// TODO: ogni figlio produttore (1 e 2) fa PRODS produzioni
		int value;
		
		if(pid == 0){
			if(i % 2 == 0){
				//figli produttori tipo 1
				printf("Sono il figlio produttore %d (Tipo 1)\n", getpid());
				for(int j = 0; j < PRODS; j++){
					value = rand()%(100+1);
					produci_tipo_1(buf, semid, value);
				}
				exit(0);
			} else {
				//figli produttori tipo 2
				printf("Sono il figlio produttore %d (Tipo 2)\n", getpid());
				for(int k = 0; k < PRODS; k++){
					value = rand()%(100+1);
					produci_tipo_2(buf, semid, value);
				}
				exit(0);
			}
		}
	}

	for(i = 0; i < NCONS; i++){
		pid = fork();

		// TODO: ogni figlio consumatore (1 e 2) fa CONS consumi
		if(pid == 0){
			if(i == 0){
				//figlio consumatore tipo 1
				printf("Sono il figlio consumatore %d (Tipo 1)\n", getpid());
				for(int h = 0; h < CONS; h++){
					consuma_tipo_1(buf, semid);
				}
				exit(0);
			} else {
				//figlio consumatore tipo 2
				printf("Sono il figlio consumatore %d (Tipo 2)\n", getpid());
				for(int y = 0; y < CONS; y++){
					consuma_tipo_2(buf, semid);
				}
				exit(0);
			}
		}
	}
	
	// TODO: attesa completamento figli
	for(i = 0; i < NCONS + NPROD; i++){
		pid_ex = wait(NULL);
		printf("Figlio %d terminato\n", pid_ex);
	}

	// TODO: rimozione strutture 
	semctl(semid, 0, IPC_RMID); 
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}

