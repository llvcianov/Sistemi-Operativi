#ifndef HEADER_H
#define HEADER_H

#define MAX_PRODOTTI 3

//tipo messaggi
#define READ 1
#define WRITE 2

//size messaggi
#define SIZE_REQ sizeof(Msg_Req)-sizeof(long)
#define SIZE_RESP sizeof(Msg_Resp)-sizeof(long)

typedef struct {
    long tipo_richiesta;
    long mittente;
    int id_prodotto;
    int value;
} Msg_Req;

typedef struct {
    long pid;
    int id_prodotto;
    int scorta;
} Msg_Resp;

#endif
