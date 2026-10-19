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
	BufferCircolare* buf;

	key_t key_shm,key_sem;
	key_shm = IPC_PRIVATE; //TODO;
	key_sem = IPC_PRIVATE; //TODO;

	shmid = shmget(key_shm, sizeof(BufferCircolare), IPC_CREAT | 0664);//TODO
	semid = semget(key_sem, 6, IPC_CREAT | 0664);//TODO
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO
	// Inizializzare risorse
	buf = (BufferCircolare *)shmat(shmid, NULL, 0);
	
	for(int j = 0; j<SIZE; j++){
		
		buf->stati[j]=LIBERO;
	}
	
	semctl(semid, MUTEXP, SETVAL, 1);
	semctl(semid, MUTEXC, SETVAL, 1);
	semctl(semid, MESS_DISP_1, SETVAL, 0);
	semctl(semid, MESS_DISP_2, SETVAL, 0);
	semctl(semid, MESS_DISP_3, SETVAL, 0);
	semctl(semid, SPAZIO_DISP, SETVAL, SIZE);
	

	srand(time(NULL));
	int val;

	for(i = 0; i < NCONS+NPROD; i++){
		// TODO CREARE PROCESSI FIGLI (PRODUTTORI E CONSUMATORI)
		pid=fork();
		if(pid==0){
			//codice figli
			
			if(i<3){
				//figlio produttore
				printf("Sono il figlio produttore %d\n", getpid());
				val =  (1+rand()%3);
				sleep(val);
				produci(buf, i+1, semid);
				exit(0);
			
			} else {
				//figlio consumatore
				printf("Sono il figlio consumatore %d\n", getpid());
				val =  (1+rand()%3);
				sleep(val);
				consuma(buf, i-2, semid);
				exit(0);
			
			}
		}
	}
	
	sleep(7);
	
	for(i = 0; i < NCONS+NPROD ; i++){
		// TODO JOIN COMPLETAMENTO FIGLI
		pid_ex = wait(NULL);
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n",pid_ex);			
	}

	// RIMOZIONE RISORSE
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID);
	
	return 0;
}
