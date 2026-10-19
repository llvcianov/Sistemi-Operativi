			/*----IMPLEMENTAZIONE DELLE PROCEDURE----*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <math.h>

//Procedure per la sincronizzazione sui semafori

void Wait_Sem(int id_sem, int numsem)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);
}


void Signal_Sem (int id_sem,int numsem)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);

}

// Consumo
void consuma(BufferCircolare* buf, int chiave, int semid){
	printf("[Consumatore %d] iniziato con chiave %d \n",getpid(), chiave);
	int sem;
	int value;
	int index;

	for(int i=0; i<3; i++){
		// TODO completare consumazione
		index=0;
		Wait_Sem(semid, chiave+1);
		Wait_Sem(semid, MUTEXC);
		while((buf->stati[index] != OCCUPATO || buf->elementi[index].chiave != chiave) && index<SIZE){
			index++;
		}
		printf("[Consumatore %d] consumo elemento in posizione %d\n",getpid(), index);
		buf->stati[index]=IN_USO;
		Signal_Sem(semid, MUTEXC);
		value=buf->elementi[index].valore;
		printf("[Consumatore %d] valore letto: %d\n",getpid(), value);
		buf->stati[index]=LIBERO;
		Signal_Sem(semid, SPAZIO_DISP);
	}
}

//Produzione
void produci(BufferCircolare* buf, int chiave, int semid){
	printf("[Produttore %d] iniziato con chiave %d\n",getpid(), chiave);
	int val_sleep;
	int value;
	int sem;
	int index;

	for(int i=0; i<3; i++){
		// TODO COMPLETARE PRODUZIONE
		
		index=0;
		value=1+rand()%100;
		val_sleep=(1+rand()%3);
		Wait_Sem(semid, SPAZIO_DISP);
		Wait_Sem(semid, MUTEXP);
		while(buf->stati[index] != LIBERO && index<SIZE){
			index++;
		}
		printf("[Produttore %d] entrato con chiave %d \n",getpid(), chiave);
		buf->stati[index]=IN_USO;
		Signal_Sem(semid, MUTEXP);
		buf->elementi[index].chiave=chiave;
		buf->elementi[index].valore=value;
		printf("[Produttore %d] ho prodotto %d, con chiave %d, in posizione %d\n",getpid(),value, chiave, index);
		buf->stati[index]=OCCUPATO;
		switch(chiave){
			case 1:
				Signal_Sem(semid, MESS_DISP_1);
				break;
			case 2:
				Signal_Sem(semid, MESS_DISP_2);
				break;
			case 3:
				Signal_Sem(semid, MESS_DISP_3);
				break;
		sleep(val_sleep);
		}
	}
}
