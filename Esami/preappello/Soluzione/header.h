#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define TIPO 1
#define LETTORI 3

typedef struct {

    // TODO: completare campi messaggio
    long tipo;
    int valore;

} Messaggio;

typedef struct {

    // TODO: completare inserendo i campi necessari a gestire il problema dei lettori-scrittori (unico scrittore)
    int num_lettori;
    int num_scrittori;
    int buffer;
    pthread_mutex_t mutex;
    pthread_cond_t cv_lett;
    pthread_cond_t cv_scritt;


} MonitorLS;

#endif
