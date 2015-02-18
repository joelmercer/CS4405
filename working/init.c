#include "globalvars.h"

void OS_Start() {

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

//Time Quantium setup
int timer = 0x500000; // 1/(50 MHz) × (0x500000) = ~0.1 seconds
*(timeq + 0x2 = (timer & 0xFFFF);
*(timeq + 0x3 = (timer >> 16) & 0xFFFF;

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
