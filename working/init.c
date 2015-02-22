#include "globalvars.h"

int sporadiccounter, terminate, crash, processcounter, sporadic[], terminate, crash;


void OS_Start() {
    int s;
    int p = 0;
   

while(1) {
    

    for(s=0;s<MAXPROCESS;s++) {
        next:
        processcounter = s;
        if(sporadic[s]!=EMPTY) {
        
        //future timer function call: OS_Set_Timer(timeq); //set and load timer to timeq
        Context_Switch(processarray[sporadic[s]].pid);
            
        if(terminate==0){
        OS_Terminate();
        terminate = 1;
        }
            
        if(crash==1) {
        goto crash;   
        }
            
        //Save context switch of os_start PC+1 & Load context switch for sporadic[s]
        } else {
            s++;
            goto next;
        }
      
/*  Future PPP      
        for(p=p;p<PPPLen;p++) {
        
            OS_Set_Timer(PPPMax[p]);
            if(PPP[p] != IDLE) {
                //save context switch of os_start
                //load context switch to PPP
            }
        } //end of p loop

        if(p >= PPPLen) {
        pppcounter = 0; }
*/
        
    } //end of s loop
    
} //end of while
    
crash: 
return;//Should only return on error
}


void OS_AddTo_Schedule(int pid, int level) {
int temp, i, sporadic[MAXPROCESS]; 
    
pid = OS_GetPID();
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

int sporadiccounter = 0;
int terminate = 1;
int crash = 0;
processcounter = 0; 

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

/* Future timer
void OS_Set_Timer(int timer) {

//Timer setup
*(timebase + 0x2 = (timer & 0xFFFF));
*(timebase + 0x3 = (timer >> 16) & 0xFFFF);    

  //Start Timer
*(timebase + 1) = 0x7;  
  
  return;
}
*/

void OS_Abort() {

//Disable Interrupts and never enable them
crash = 1;
return;
    
}
