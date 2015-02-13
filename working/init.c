#include "globalvars.h"

void OS_Start() {

    OS_Init();
}

void OS_Init() {
int i, j;
    
//init semaphores
    int semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        semarray[i].s = -1;
        semarray[i].n = -1;
    } 

}

void OS_Abort() {

}
