 #include "common.h"

void client(int msgq_guest)
{
	int i;

	/* Inizializzazione Messaggio del processo */
	//TODO

	messaggioClient m;

	m.PID = getpid();

	m.type = MESS_CLIENT;

	/* Invio dei 15 messaggi in ciclo, con sleep(1) tra un messaggio e l'altro */
	//TODO
	
	for(i=0;i<5;i++){

		msgsnd(msgq_guest, (void*)&m, SIZE_C, 0);
		printf("Messaggio %d inviato dal processo %d\n", i, getpid());

		sleep(1);

	}
}
