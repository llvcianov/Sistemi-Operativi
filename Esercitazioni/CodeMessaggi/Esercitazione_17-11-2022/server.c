#include "common.h"
#include <stdio.h>

void server(int msgq_guest, int msgq_print)
{
	int i;
	
	/* TODO Definizione Messaggio da ricevere dal proc. client */
	messaggioClient m1;

	/* TODO Definizione Messaggio da inviare al proc. printer */
	messaggioServer m2;
	m2.type = MESS_SERVER;

	printf("[server ] Server ready...\n");
	while(1)
	{
		for(i=0; i<BUFFER_DIM; i++)
		{
			/*TODO Ricezione del messaggio di richiesta*/
			msgrcv(msgq_guest, (void *)&m1, SIZE_C, MESS_CLIENT, 0);
			//msgrcv(msgq_guest, (void *)&m1, SIZE_C, MESS_FINE, IPC_NOWAIT);

			/*TODO se il messaggio è di tipo fine, inserisce -1 in posizione i-ma e termina */
			if( m1.PID == -1){
				
				//m1.PID = -1;
				m2.buffer[i] = m1.PID;
				msgsnd(msgq_print, (void*)&m2, SIZE_S, 0);
				printf("Messaggio fine inviato al printer\n");
				_exit(0);

			}

			/*TODO Accodamento della richiesta nel buffer */
			m2.buffer[i] = m1.PID;
			printf("Copia messaggi nel buffer...\n");
			
		}
		
	/*TODO Invio del messaggio con il buffer completo al proc. printer */
	msgsnd(msgq_print, (void*)&m2, SIZE_S, 0);
	printf("Buffer inviato al printer\n");
		
	}
}
