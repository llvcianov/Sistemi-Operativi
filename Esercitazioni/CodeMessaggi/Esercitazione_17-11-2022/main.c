#include "common.h"
#include <sys/wait.h>

#define NR_CLIENT  5

/* ID - Code di Messaggi */
int msgq_guest;
int msgq_print;

int main(int argc,char*argv[])
{
	int i, j;
	pid_t pid1, pid2, pid3[5], pidex1, pidex2, pidex3;
	messaggioClient mess_finale;

	mess_finale.type = MESS_CLIENT;
	mess_finale.PID = -1;


	/*Richiesta code di messaggi IPC*/
	msgq_guest = msgget(IPC_PRIVATE, IPC_CREAT | 0664);/*TODO*/
	msgq_print = msgget(IPC_PRIVATE, IPC_CREAT | 0664);/*TODO*/

	/*Creazione processo 'printer'*/
	//TODO
	pid1=fork();
	if(pid1 == 0){

		pid1 = getpid();
		printf("Figlio printer creato con pid %d\n", pid1);
		printer(msgq_print);
		_exit(0);
	}

	/*Creazione processo 'server'*/
	//TODO
	pid2=fork();
	if(pid2 == 0){

		pid2= getpid();
		printf("Figlio server creato con pid %d\n", pid2);
		server(msgq_guest, msgq_print);
		_exit(0);
	}

	/*Creazione processi 'client'*/
	//TODO
	for(i=0; i<5; i++){

		pid3[i]=fork();
		if(pid3[i] == 0){

			printf("Figlio client %d creato con pid %d\n",i, getpid());
			sleep(4);
			client(msgq_guest);
			_exit(0);
		}
	}

	
	/*Attesa terminazione dei client*/
	//TODO
	for(j=0; j<5; j++){

		sleep(3);
		pidex3 = waitpid(pid3[j], NULL, 0);
		printf("Figlio client terminato con pid %d\n", pid3[j]);
	}

	/*Invio messaggio di terminazione al server*/
	//TODO
	msgsnd(msgq_guest, (void*)&mess_finale, SIZE_C, 0);
	printf("Messaggio fine inviato al server\n");
	
	/*Attesa terminazione processi 'server' e 'printer'*/
	//for(i=0; i<2; i++){
		
		pidex1 = waitpid(pid1, NULL, 0);
		pidex2 = waitpid(pid2, NULL, 0);
		printf("Figlio printer e server terminati con pid %d e %d\n", pid1, pid2);
	//}
	
	/*Rimozione code IPC e uscita*/
	//TODO
	msgctl(msgq_guest, IPC_RMID, NULL);
	msgctl(msgq_print, IPC_RMID, NULL);

	return 0;
}
