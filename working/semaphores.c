#include "globalvars.h"

void OS_InitSem(int s, int n) {
    int i, semcounter;
    
NIOS2_WRITE_STATUS(0); //disable interupts**********************************
    
    //check to make sure s doesn't already exist
    for(i=0;i<MAXSEM;i++) {
        if(semarray[i].s == s) {
            OS_Abort() //Error abort
        }
    }
           
    //add s and n to semarray struct
    semarray[semcounter].s = s;
    semarray[semcounter].n = n;
    
    //Init sempid array       
    for(i=0;i<n;i++) {
    semarray[semcounter].sempid[i] = EMPTY; 
    }
    
    //counter up
    semcounter++;
           
NIOS2_WRITE_STATUS(1); //enable interupts**********************************
return;
}

void OS_Wait(int s){
    int i=0;
    int j=0;
    int currentpid = getpid(); //make getpid() work**********************************
    
NIOS2_WRITE_STATUS(0); //disable interupts**********************************
    
    //check for s
   while(i<MAXSEM) {
        if(semarray[i].s == s) {
                while(semarray[i].n <= 0){
                    OS_Yield(); //Context switch while waiting
                }
            semarray[i].n--;
            while(j<semarray[i].n) {
                if(semarray[i].sempid[j] == EMPTY){ 
                    semarray[i].sempid[j] = currentpid;
                        break;
                }
                j++;
            }
           break;
        }
       i++;
    }

NIOS2_WRITE_STATUS(1); //enable interupts**********************************

return;
}

void OS_Signal(int s) {
int i=0; 
int j=0;
int currentpid = getpid(); //make getpid() work**********************************    
    
NIOS2_WRITE_STATUS(0); //disable interupts**********************************

    //Check to see if this PID is holding the Semaphore
   while(i<MAXSEM) {
        if(semarray[i].s == s) {
            semarray[i].n++;
            while(j<semarray[i].n) {
                if(semarray[i].sempid[j] == currentpid){ 
                    semarray[i].sempid[j] = EMPTY;
                        break;
                }
                j++;
            }
           break; 
        }
       i++;
    
          } 
    
NIOS2_WRITE_STATUS(1); //enable interupts**********************************
return;
}
