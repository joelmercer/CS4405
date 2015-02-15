#include "globalvars.h"

void OS_Start() {

    OS_Init();
}

void OS_Init() {
int i, j;
    
//init semaphores
    int semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        semarray[i].s = EMPTY;
        semarray[i].n = EMPTY;
    } 

}

void OS_Abort() {

}
