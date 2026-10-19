#ifndef HEADER_H
#define HEADER_H
#define SYZE sizeof(Messaggio)-sizeof(long) 


typedef struct{
		
	long tipo;
	char testo_messaggio[50];
		
} Messaggio;


void produttore(int, char * );
void consumatore(int);
void SendSync(int, Messaggio);
void ReceiveSync(int, Messaggio*);

#endif




	
