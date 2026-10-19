#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>

#include "store.h"

extern int ds_queue_request, ds_queue_response;

void Wait_Sem(int ds_sem, int id_sem) {
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = id_sem;
    buf.sem_op = -1;
    semop(ds_sem,&buf,1);
}

void Signal_Sem(int ds_sem, int id_sem) {
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = id_sem;
    buf.sem_op = 1;
    semop(ds_sem,&buf,1);
}

void init_magazzino(Magazzino *magazzino){
    // TODO inizializzazione dei semafori , delle variabili necessarie alla sincronizzazione
    // e delle scorte di magazzino iniziali
    magazzino->chiave_sem = ftok(".", 'd');
    magazzino->id_sem = semget(magazzino->chiave_sem, 6, IPC_CREAT | 0664);
    magazzino->key_queue_request = ftok(".", 'a');
    magazzino->key_queue_response = ftok(".", 'b');
    ds_queue_request = msgget(magazzino->key_queue_request, IPC_CREAT | 0664);
    ds_queue_response = msgget(magazzino->key_queue_response, IPC_CREAT | 0664);
    
    semctl(magazzino->id_sem, MUTEXL_1, SETVAL, 1);
    semctl(magazzino->id_sem, SYNCH_1, SETVAL, 1);
    semctl(magazzino->id_sem, MUTEXL_2, SETVAL, 1);
    semctl(magazzino->id_sem, SYNCH_2, SETVAL, 1);
    semctl(magazzino->id_sem, MUTEXL_3, SETVAL, 1);
    semctl(magazzino->id_sem, SYNCH_3, SETVAL, 1);
    
    magazzino->num_lettori_1=0;
    magazzino->num_lettori_2=0;
    magazzino->num_lettori_3=0;
    
    for(int i = 0; i<3; i++){
    	magazzino->scorta[i]=SCORTA_INIZIALE;
    }
}

void destroy_magazzino(Magazzino *magazzino){
    // TODO rimozione dei semafori
    semctl(magazzino->id_sem, 0, IPC_RMID);
}

void lettore(Magazzino *magazzino) {
    int ret;
    Msg_Req m_req;
    Msg_Resp m_resp;
    int k;

    for (k=0; k<4; k++) {
        // TODO aggiungere codice per la ricezione comando
        msgrcv(ds_queue_request, (void*)&m_req, SIZE_REQ, READ, 0);
        
        // TODO Aggiungere codice per la lettura:
        // InizioLettura
        InizioLettura(magazzino, m_req.id_prodotto);
        
        // Lettura del livello di scorta del prodotto il cui id è indicato nella richiesta
 		m_resp.scorta=magazzino->scorta[m_req.id_prodotto];
        
        // FineLettura
        FineLettura(magazzino, m_req.id_prodotto);

        // TODO Costruire il messaggio di risposta m_resp
        m_resp.pid=m_req.mittente;
        m_resp.id_prodotto=m_req.id_prodotto;

        printf("[lettore] Ricevuta richiesta di lettura per prodotto %d con livello scorte%d\n",m_resp.id_prodotto,m_resp.scorta);

        // TODO aggiungere codice per l'invio del messaggio di risposta
        msgsnd(ds_queue_response, (void*)&m_resp, SIZE_RESP, 0);
    }
}

void scrittore(Magazzino *magazzino){
    int ret;
    Msg_Req m_req;
    int k;

    for (k = 0; k < 2; k++) {
        // TODO agiungere codice per la ricezione del comando
        msgrcv(ds_queue_request, (void*)&m_req, SIZE_REQ, WRITE, 0);
        
        // TODO aggiungere codice per la scrittura
        // InizioScrittura
        InizioScrittura(magazzino, m_req.id_prodotto);
        
        // Decremento del livello di scorta del prodotto indicato nella richiesta della quantità indicata nella richiesta
        magazzino->scorta[m_req.id_prodotto]=magazzino->scorta[m_req.id_prodotto]-1;
        
        // FineScrittura
        FineScrittura(magazzino, m_req.id_prodotto);
        

        printf("[scrittore] Ricevuta richiesta di decremento di %d per prodotto %d\n",m_req.value, m_req.id_prodotto);
    }
}

void InizioLettura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di inizio lettura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    switch(id_prodotto){
    	case 0:
    		Wait_Sem(magazzino->id_sem, MUTEXL_1);
    		magazzino->num_lettori_1++;
    		if(magazzino->num_lettori_1==1)Wait_Sem(magazzino->id_sem, SYNCH_1);
    		Signal_Sem(magazzino->id_sem, MUTEXL_1);
    		break;
    	case 1:
    		Wait_Sem(magazzino->id_sem, MUTEXL_2);
    		magazzino->num_lettori_2++;
    		if(magazzino->num_lettori_2==1)Wait_Sem(magazzino->id_sem, SYNCH_2);
    		Signal_Sem(magazzino->id_sem, MUTEXL_2);
    		break;
    	case 2:
    		Wait_Sem(magazzino->id_sem, MUTEXL_3);
    		magazzino->num_lettori_3++;
    		if(magazzino->num_lettori_3==1)Wait_Sem(magazzino->id_sem, SYNCH_3);
    		Signal_Sem(magazzino->id_sem, MUTEXL_3);
    		break;
    }
}

void FineLettura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di fine lettura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    switch(id_prodotto){
    	case 0:
    		Wait_Sem(magazzino->id_sem, MUTEXL_1);
    		magazzino->num_lettori_1--;
    		if(magazzino->num_lettori_1==0)Signal_Sem(magazzino->id_sem, SYNCH_1);
    		Signal_Sem(magazzino->id_sem, MUTEXL_1);
    		break;
    	case 1:
    		Wait_Sem(magazzino->id_sem, MUTEXL_2);
    		magazzino->num_lettori_2--;
    		if(magazzino->num_lettori_2==0)Signal_Sem(magazzino->id_sem, SYNCH_2);
    		Signal_Sem(magazzino->id_sem, MUTEXL_2);
    		break;
    	case 2:
    		Wait_Sem(magazzino->id_sem, MUTEXL_3);
    		magazzino->num_lettori_3--;
    		if(magazzino->num_lettori_3==0)Signal_Sem(magazzino->id_sem, SYNCH_3);
    		Signal_Sem(magazzino->id_sem, MUTEXL_3);
    		break;
    }
}

void InizioScrittura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di inizio scrittura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    int SYNCHSEM;
    switch(id_prodotto){
    	case 0:
    		SYNCHSEM=SYNCH_1;
    		break;
    	case 1:
    		SYNCHSEM=SYNCH_2;
    		break;
    	case 2:
    		SYNCHSEM=SYNCH_3;
    		break;
    }
    Wait_Sem(magazzino->id_sem, SYNCHSEM);
    
}
void FineScrittura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di fine scrittura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
    int SYNCHSEM;
    switch(id_prodotto){
    	case 0:
    		SYNCHSEM=SYNCH_1;
    		break;
    	case 1:
    		SYNCHSEM=SYNCH_2;
    		break;
    	case 2:
    		SYNCHSEM=SYNCH_3;
    		break;
    }
    Signal_Sem(magazzino->id_sem, SYNCHSEM);
    
}
