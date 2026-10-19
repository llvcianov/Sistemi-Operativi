#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

void main() {

    printf("Avvio processo sensore...\n");
    
    int key_coda = // TODO
    int id_coda_sensore = // TODO

    srand(time(NULL));

    for(int i=0; i<10; i++) {

        // TODO: inviare interi casuali sulla coda
        
        sleep(1);
    }

}
