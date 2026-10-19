#include "stack.h"

#include <stdlib.h>

void StackInit(Stack * s, int dim) {
	
	pthread_mutex_init(&(s->mutex), NULL);
	pthread_cond_init(&(s->ok_inserimento_cv), NULL);
	pthread_cond_init(&(s->ok_prelievo_cv), NULL);
	
	s->dati=(Elem*)malloc(sizeof(Elem)*4);
	s->testa=0;
	s->dim=dim;
	
}


void StackRemove(Stack * s) {

	pthread_mutex_destroy(&(s->mutex));
	pthread_cond_destroy(&(s->ok_inserimento_cv));
	pthread_cond_destroy(&(s->ok_prelievo_cv));
	
	free(s->dati);
	
}

void StackPush(Stack * s, Elem e) {
	pthread_mutex_lock(&(s->mutex));
	while(s->testa==4)
		pthread_cond_wait(&(s->ok_inserimento_cv), &(s->mutex));
	s->dati[s->testa]=e;
	s->testa++;
	pthread_cond_signal(&(s->ok_prelievo_cv));
	pthread_mutex_unlock(&(s->mutex));
	
}


Elem StackPop(Stack * s) {

	int elemento;
	
	pthread_mutex_lock(&(s->mutex));
	while(s->testa==0)pthread_cond_wait(&(s->ok_prelievo_cv), &(s->mutex));
	elemento=s->dati[s->testa];
	s->testa--;
	pthread_cond_signal(&(s->ok_inserimento_cv));
	pthread_mutex_unlock(&(s->mutex));
	
	return elemento;
}

int StackSize(Stack * s) {
	int size;
	
	pthread_mutex_lock(&(s->mutex));
	size=s->testa;
	pthread_mutex_unlock(&(s->mutex));

	return size;
}
