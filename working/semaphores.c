#include "globalvars.h"


void OS_InitSem(int s, int n) {
	NIOS2_WRITE_STATUS( 0 );
    int i, j;
    
    //check to make sure s doesn't already exist
    for(i=0;i<MAXSEM;i++) {
        if(semarray[i].s == s) {
            OS_Abort(); //Error abort
        }
    }
           
	int crashtest = 0;	   
    //add s and n to semarray struct
    for(i=0;i<MAXSEM;i++) {
        if(semarray[i].s == EMPTY) {
        
            semarray[i].s = s;
            semarray[i].n = n; 
			
			for(j=0;j<MAXSEM;j++) {
				semarray[i].waitpid[j] = EMPTY;
			}
           
            //Init sempid array
            semarray[i].sempid[n];
            for(j=0;j<n;j++) {
                semarray[i].sempid[j] = EMPTY; 
            }
        //If this doesn't happen then there aren't enough semaphores, this is an abort error.
        crashtest = 1;
        i = MAXSEM; //Breaks loop
        }
    }

//OS_Abort if this doesn't happen.
    if(crashtest!=1) {
        OS_Abort(); //Error abort
	}
	
NIOS2_WRITE_STATUS( 1 );
return;
}

void OS_Wait(int s){
	NIOS2_WRITE_STATUS( 0 );			// disable Nios II interrupts
    int i=0;
    int j=0;
	int k=0;
    int currentpid = getpid(); 
    
    //check for s
   while(i<MAXSEM) {
        if(semarray[i].s == s) {
                if(semarray[i].n <= 0){
					
					for(k=0;k<MAXSEM;k++) {
						if(semarray[i].waitpid[k] == EMPTY) {
							semarray[i].waitpid[k] = workingpid;
							break;
						}
					}
							
                    processarray[workingpid].state = 3;
					
					asm (	"ldw	r12,  4(sp)" );
					unsigned int ra;
					asm (	"mov	%0, r12":"=r"(ra));
					ra-=8;
					asm (	"mov	r12, %0" ::"r"(ra));
					asm (	"stw	r12,  4(sp)" );
					//get 24(sp)
					//sub 8 addresses from it
					//put it back into 24(sp)
					OS_StartTimer(0x10);
					return;
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

	NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
return;
}

void OS_Signal(int s) {
	NIOS2_WRITE_STATUS( 0 );			// disable Nios II interrupts
	int i=0; 
	int j=0;
	int k=0;
	int currentpid = getpid(); 
    
    //Check to see if this PID is holding the Semaphore
   while(i<MAXSEM) {
        if(semarray[i].s == s) {
            semarray[i].n++;
            while(j<semarray[i].n) {
                if(semarray[i].sempid[j] == currentpid){ 
                    semarray[i].sempid[j] = EMPTY;
					//clear next out of wait queue
					for(k=0;k<MAXSEM;k++) {
						if(semarray[i].waitpid[k] != EMPTY) {
							int release = semarray[i].waitpid[k];
							processarray[release].state = 2;
							//Needs to shift values to the left
							semarray[i].waitpid[k] = EMPTY;
						}
					}
                        break;
                }
                j++;
            }
           break; 
        }
       i++;
          } 
    	NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts

	return;
}
