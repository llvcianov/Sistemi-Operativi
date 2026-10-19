			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define SIZE 4

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define NPROD 3
#define NCONS 3

typedef struct{
	int chiave;
	int valore;
} ElemBuffer;

typedef struct{
	ElemBuffer elementi[SIZE];
	int stati[SIZE];
} BufferCircolare;

//INSERIRE IDENTIFICATIVI SEMAFORI
#define MUTEXP 0
#define MUTEXC 1
#define MESS_DISP_1 2
#define MESS_DISP_2 3
#define MESS_DISP_3 4
#define SPAZIO_DISP 5


void Wait_Sem(int, int);
void Signal_Sem (int, int);

void produci(BufferCircolare* buf, int chiave, int semid);
void consuma(BufferCircolare* buf, int chiave, int semid);

#endif
