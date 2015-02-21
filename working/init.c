#include "globalvars.h"

void OS_Start() {

while(1) {
    
  /* PERIODIC process scheduling plan */
//extern int PPPLen;          /* length of PPP[] */
//extern int PPP[];           /* PERIODIC process scheduling plan */
//extern int PPPMax[];        /* max CPU in msec of each process in PPP */

While(pppcounter<PPPLen) {
    //Run one PPP then go to S ***
    //OS_Set_Timer(PPP[P]); ***
    //Finished running PPP go to S ***
    
    pppcounter++;
    
    if(pppcounter >= PPPLen)
        pppcounter = 0;
    
    OS_Set_Timer(timeq);
    
    While(1) {
    
    //Call process in sporadic[sporadiccounter] *****
    //Load it's saved context switch (if present?!?)
    
    sporadiccounter++;
        
    if(sporadiccounter >= MAXPROCESS)
        sporadiccounter = 0;
    
    }
    

}
//Should never return
}
}

void OS_AddTo_Schedule(int pid, int level) {
int temp;
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
        temp = sporadiccounter + 1;
        sporadic[temp] = pid;
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
	OS_InitFiFo();
	for(j=0;j<MAXFIFO;j++){
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
