#include "common.h"

void printer(int msgq_print)
{
	int counter = 1, i;
	
	//TODO definizione messaggio da ricevere
	messaggioServer m3;
	
	printf("[printer] Printer Ready...\n");

	while(1)
	{
		//TODO ricezione messaggio contenente il buffer
		msgrcv(msgq_print, (void*)&m3, SIZE_S, MESS_SERVER, 0);
		
		for(i=0; i<BUFFER_DIM; i++)
		{
			// TODO se in posizione i-ma del buffer c'è un pid -1 il printer deve terminare
			if(m3.buffer[i]==-1){

				printf("Messaggio fine letto\n");
				_exit(0);
			
			}

			printf("{printer}\t[%u] %u\n", counter++, m3.buffer[i]/*TODO stampa elemento i-mo del buffer*/);
		}
	}
}
