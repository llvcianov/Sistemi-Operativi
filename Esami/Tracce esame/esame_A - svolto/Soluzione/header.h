			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#include "semafori.h"

#define DIM 4

// TODO: definire semafori
#define SPAZIO_DISPONIBILE 0
#define MESS_DISPONIBILE_1 1
#define MESS_DISPONIBILE_2 2
#define MUTEXP 3

#define LIBERO 0
#define IN_USO 1
#define OCC_TIPO1 2
#define OCC_TIPO2 3

#define NPROD 4
#define NCONS 2

#define PRODS 4
#define CONS 8

typedef struct {
	
	// TODO: completare campi struct
	int Buffer[DIM];
	int stato[DIM];

} BufferMutuaEx;

void produci_tipo_1(BufferMutuaEx * buf, int semid, int val);
void produci_tipo_2(BufferMutuaEx * buf, int semid, int val);
void consuma_tipo_1(BufferMutuaEx * buf, int semid);
void consuma_tipo_2(BufferMutuaEx * buf, int semid);



#endif
