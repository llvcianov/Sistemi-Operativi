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
#include "semafori.h"
#include <math.h>

void produci_tipo_1(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 1
	int index = 0;
	
	Wait_Sem(semid, SPAZIO_DISPONIBILE);
	Wait_Sem(semid, MUTEXP);
	while(index < DIM && buf->stato[index] != LIBERO){
		index++;
	}
	buf->stato[index] = IN_USO;
	Signal_Sem(semid, MUTEXP);
	
	buf->Buffer[index] = value;
	
	buf->stato[index] = OCC_TIPO1;
	Signal_Sem(semid, MESS_DISPONIBILE_1);

	printf("[Produttore %d] ho prodotto %d di tipo 1, in posizione %d\n", getpid(), value, index);
	

}

void produci_tipo_2(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 2 
	int index = 0;
	
	Wait_Sem(semid, SPAZIO_DISPONIBILE);
	Wait_Sem(semid, MUTEXP);
	while(index < DIM && buf->stato[index] != LIBERO){
		index++;
	}
	buf->stato[index] = IN_USO;
	Signal_Sem(semid, MUTEXP);
	
	buf->Buffer[index] = value;
	
	buf->stato[index] = OCC_TIPO2;
	Signal_Sem(semid, MESS_DISPONIBILE_2);

	printf("[Produttore %d] ho prodotto %d di tipo 2, in posizione %d\n", getpid(), value, index);

}

void consuma_tipo_1(BufferMutuaEx * buf, int semid) {

	// TODO: completare consumo 1
	int index = 0;
	int value;
	
	Wait_Sem(semid, MESS_DISPONIBILE_1);
	while(index < DIM && buf->stato[index] != OCC_TIPO1 ){
		index++;
	}
	buf->stato[index] = IN_USO;
	value = buf->Buffer[index];
	buf->stato[index] = LIBERO;
	Signal_Sem(semid, SPAZIO_DISPONIBILE);
	
	printf("[Consumatore %d] consumo elemento %d di tipo 1 in posizione %d\n",getpid(), value, index);	

}

void consuma_tipo_2(BufferMutuaEx * buf, int semid) {
	
	// TODO: completare consumo 2
	int index = 0;
	int value;
	
	Wait_Sem(semid, MESS_DISPONIBILE_2);
	while(index < DIM && buf->stato[index] != OCC_TIPO2 ){
		index++;
	}
	buf->stato[index] = IN_USO;
	value = buf->Buffer[index];
	buf->stato[index] = LIBERO;
	Signal_Sem(semid, SPAZIO_DISPONIBILE);

	printf("[Consumatore %d] consumo elemento %d di tipo 2 in posizione %d\n",getpid(), value, index);	

}
