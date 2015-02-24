#include "globalvars.h"

void OS_Init() {
int i, j;

sporadiccounter = 0;
terminate = 1;
crash = 0;
processcounter = 0; 
FIFO f = 0;
workingpid = EMPTY;

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
		int clearfifo;
		clearfifo = OS_InitFiFo();
		fifoarray[clearfifo].data=EMPTY;
		fifoarray[clearfifo].flag=0;
	}
    
//init processes
    processcounter = 1;
    for(i=0;i<MAXPROCESS;i++) {
        processarray[i].pid = EMPTY;
        processarray[i].arg = EMPTY;
        processarray[i].level = 0;
        processarray[i].n = 0;
    } 

for(i=0;i<MAXPROCESS;i++) {
sporadic[i] = EMPTY; 
}



    
j=0;    
for(i=0;i<MAXFIFO;i++) {
    
    fifopidarray[i][j] = EMPTY;

    for(j=0;j<MAXFIFO;j++) {
        
        fifopidarray[i][j] = EMPTY;
    }
}

//Future Timer setup
//OS_Set_Timer(timeq);

return;
}

void OS_Start() {
    int s;
    int p = 0;
  

while(1) {
    int i = 0;

    for(s=0;s<MAXPROCESS;s++) {
        
        processcounter = s;
		
        if(sporadic[s]!=EMPTY) {
        //future timer function call: OS_Set_Timer(timeq); //set and load timer to timeq
		workingpid = processarray[sporadic[s]].pid;
        Context_Switch(workingpid);
			
        if(terminate==0){
        OS_Terminate();
        terminate = 1;
        }
        if(crash==1) {
        goto crash;   
        }
        //Save context switch of os_start PC+1 & Load context switch for sporadic[s]
		workingpid = EMPTY;
        } 
 
    } //end of s loop
    
} //end of while
    
crash:

return;//Should only return on error
}


void OS_AddTo_Schedule(int pid, int level) {
int i = 0;

    //Check level
    //Levels
    //SPORADIC 2      /* first-come-first-served, aperiodic */
    //PERIODIC 1      /* cyclic, fixed-order, periodic */
    //DEVICE 0      /* time-driven cyclic device drivers */

    
    if(level == 0) {
     //add to device Q   
    }
	if(level == 1) {
    //add to Periodic Q
    } 
	if(level == 2) {
		
        for(i=0;i<MAXPROCESS;i++) {
            if(sporadic[i]==EMPTY) {
                sporadic[i] = pid;
				i=MAXPROCESS+1;
			}
        }
    }
    
return;    
}

void OS_Abort() {

//Disable Interrupts and never enable them
crash = 1;
return;
    
}
