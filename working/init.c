#include "globalvars.h"

void OS_Start() {
    int s;
    int p = 0;

while(1) {
    
  /* PERIODIC process scheduling plan */
//extern int PPPLen;          /* length of PPP[] */
//extern int PPP[];           /* PERIODIC process scheduling plan */
//extern int PPPMax[];        /* max CPU in msec of each process in PPP */

    for(s=0;s<MAXPROCESS;s++) {
        next:
        processcounter = s;
        if(sporadic[s]!=EMPTY) {
        OS_Set_Timer(timeq); //set and load timer to timeq
        //Save context switch of os_start PC+1 & Load context switch for sporadic[s]
        } else {
            s++;
            goto next;
        }
        
        for(p=p;p<PPPLen;p++) {
        
            OS_Set_Timer(PPPMax[p]);
            if(PPP[p] != ILDE) {
                //save context switch of os_start
                //load context switch to PPP
            }
        } //end of p loop

        if(p >= PPPLen) {
        pppcounter = 0; }
    
    } //end of s loop
    
} //end of while
    
return;//Should only return on error never return
}


void OS_AddTo_Schedule(int pid, int level) {
int temp, i; 
int pid = OS_GetPID();
    //Check level
    //Levels
    //SPORADIC 2      /* first-come-first-served, aperiodic */
    //PERIODIC 1      /* cyclic, fixed-order, periodic */
    //DEVICE 0      /* time-driven cyclic device drivers */

    
    if(level == 0) {
     //add to device Q   
    } else if(level == 1) {
    //add to Periodic Q
    } else {
        for(i=0;i<MAXPROCESS;i++) {
            if(sporadic[i]==EMPTY)
                sporadic[i] = pid;
        }
    }
    
return;    
}

void OS_Init() {
int i, j;

//Schedule setup
for(i=0;i<MAXPROCESS;i++) {
    sporadic[i] = EMPTY;
}
    
//init semaphores
    int semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        semarray[i].s = EMPTY;
        semarray[i].n = EMPTY;
    } 
	
//init FIFOs
	for(j=0;j<MAXFIFO;j++){
		OS_InitFiFo();
		fifoarray[j].data=EMPTY;
	}
    
//init processes
    int processcounter = 1;
    for(i=0;i<MAXPROCESS;i++) {
        processarray[i].pid = EMPTY;
        processarray[i].arg = EMPTY;
        processarray[i].level = 0;
        processarray[i].n = 0;
    } 


OS_Set_Timer(timeq);

return;
}

void OS_Set_Timer(int timer) {

//Timer setup
*(timebase + 0x2 = (timer & 0xFFFF);
*(timebase + 0x3 = (timer >> 16) & 0xFFFF;    

  //Start Timer
*(timebase + 1) = 0x7;  
  
  return;
}

void OS_Abort() {
//Disable Interrupts and never enable them
crash = 1; //abort is a global var**************

main();
    
}
