#include "globalvars.h"

void OS_Start() {

if(terminate == 0) {
    
 While(terminate == 0) {
     //Scheduling an array of procceses ***********
 }
    
} else {
    //terminate everything
}
    
    
return; //return to main to terminate OS
}

void OS_Init() {
int i, j;
    
//init semaphores
    int semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        semarray[i].s = EMPTY;
        semarray[i].n = EMPTY;
    } 

return;
}

void OS_Abort() {
abort = 1; //abort is a global var**************
main();
}
