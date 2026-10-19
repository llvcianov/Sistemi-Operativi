#ifndef _COMMON_
#define _COMMON_

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_DIM 10
#define SIZE_C sizeof(messaggioClient)-sizeof(long)
#define SIZE_S sizeof(messaggioServer)-sizeof(long)

/* Definizione Tipi di Messaggi*/
//TODO

#define MESS_CLIENT 1
#define MESS_SERVER 2
#define MESS_FINE 3


/* Definizione Messaggio Richiesta del Client */
//TODO

typedef struct{

	long type;
	pid_t PID;
	
}messaggioClient;
	

/* Definizione Messaggio Richiesta del Server, contenente il buffer */
//TODO

typedef struct{

	long type;
	int PID;
	pid_t buffer[BUFFER_DIM];
	
}messaggioServer;


/* Prototipi delle funzioni dei processi */
void printer(int msgq_print);
void server(int msgq_guest, int msgq_print);
void client(int msgq_guest);

#endif
