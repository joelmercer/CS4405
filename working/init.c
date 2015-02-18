#include "globalvars.h"

void OS_Start() {

  /* PERIODIC process scheduling plan */
//extern int PPPLen;          /* length of PPP[] */
//extern int PPP[];           /* PERIODIC process scheduling plan */
//extern int PPPMax[];        /* max CPU in msec of each process in PPP */

    //SPORADIC Array
    //set timer to TimeQ
    
}

void OS_AddTo_Schedule(int pid) {

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
abort = 1; //abort is a global var**************

main();
    
}
  
void OS_Interrupt_Init() {
    
//Start timer, enable it's interrupt  
*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
NIOS2_WRITE_STATUS(1); //Enable interrupts
return;
    
}
