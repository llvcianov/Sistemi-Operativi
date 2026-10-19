#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *Inserisci(void * s)
{

	int i;
	Elem v;
    
    Stack * stack = (Stack *) s;

	for(i=0; i<4; i++) {
		v = rand() % 11;
		StackPush(stack, v);
		printf("Inserimento: %d\n", v);
		sleep(1);
	}

	// Terminazione thread
	pthread_exit(NULL);
}


void *Preleva(void * s)
{

	int i;
	Elem v1, v2;

    Stack * stack = (Stack *) s;
    
	for(i=0; i<10; i++) {
		v1=StackPop(stack);
		printf("Prelievo: %d\n", v1);

		v2=StackPop(stack);
		printf("Prelievo: %d\n", v2);

		printf("Somma: %d\n", v1+v2);

		sleep(3);
	}

	// Terminazione thread
	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{
	// Istanziamo i thread
	pthread_t threads[6];
	pthread_attr_t attr;

	int i;

	srand(time(NULL));

	// Istanziamo lo stack
	Stack* s = (Stack*)malloc(sizeof(Stack));
	StackInit(s, 4);

	// Attributi thread
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(i=0; i<5; i++) {
		// Creazione thread per l'inserimento
		pthread_create(&threads[i], &attr, Inserisci, (void*)s);
		printf("Thread inserimento numero %d creato\n", i);
	}

	// Creazione thread per il prelievo
	pthread_create(&threads[5], &attr, Preleva, (void*)s);
	printf("Thread prelievo creato\n");


	for(i=0; i<6; i++) {
		// Attesa terminazione thread
		pthread_join(threads[i], NULL);
		printf("Thread terminato\n");
	}
	
		
	// Rimozione stack
	StackRemove(s);
	pthread_attr_destroy(&attr);
	free(s);

	pthread_exit(0);
}

