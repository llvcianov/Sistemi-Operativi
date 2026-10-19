#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define TIPO 1
#define LETTORI 3
#define SIZE sizeof(Messaggio)-sizeof(long)

typedef struct {

    // TODO: completare campi messaggio
    long tipo;
    int valore;

} Messaggio;

typedef struct {

    // TODO: completare inserendo i campi necessari a gestire il problema dei lettori-scrittori (unico scrittore)
    pthread_mutex_t mutex;
    pthread_cond_t lett;
    pthread_cond_t scritt;
    
    int num_lettori;
    //int ok_lettura;
    
    int buffer;
    

} MonitorLS;

#endif
