#include "globalvars.h"

void OS_InitSem(int s, int n) {
NIOS2_WRITE_STATUS(0); //disable interupts
    int i, j;
    

    
    //check to make sure s doesn't already exist
    for(i=0;i<MAXSEM;i++) {
        if(semarray[i].s == s) {
            OS_Abort() //Error abort
        }
    }
           
    //add s and n to semarray struct
    for(i=0;i<MAXSEM;i++) {
        if(semarray[i].s == EMPTY) {
        
            semarray[i].s = s;
            semarray[i].n = n; 
           
            //Init sempid array
            semarray[i].sempid[n];
            for(j=0;j<n;j++) {
                semarray[i].sempid[j] = EMPTY; 
            }
        i=MAXSEM+2;    
        }
    }
    
    if(i!=(MAXSEM+2))
        OS_Abort(); //Error abort
           
NIOS2_WRITE_STATUS(1); //enable interupts
return;
}

void OS_Wait(int s){
    int i=0;
    int j=0;
    int currentpid = getpid(); //make getpid() work**********************************
    
NIOS2_WRITE_STATUS(0); //disable interupts
    
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
int currentpid = getpid(); //make getpid() work    
    
NIOS2_WRITE_STATUS(0); //disable interupts

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
