#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1

#ifndef __HEADER
#define __HEADER

void produttore(int * Buffer, int ID_SEM);
void consumatore(int * Buffer, int ID_SEM); 

#endif
